/***************************************************************************************************
 * File Name: ble_comm.c
 *
 * 简化版蓝牙通信程序，专注于实现蓝牙连接和字符串通信功能
 **************************************************************************************************/

#include <string.h>
#include "wiced_bt_dev.h"
#include "wiced_bt_trace.h"
#include "wiced_bt_ble.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_cfg.h"
#include "wiced_bt_uuid.h"
#include "wiced_result.h"
#include "wiced_bt_stack.h"
#include "wiced_memory.h"
#include "wiced_timer.h"
#include "Task_BlueTooth.h"

#include <cyabs_rtos.h>
#include <tim.h>
#include <usart.h>
#include <wifi_bt_if.h>

#include "wiced_bt_types.h"
#include "cybt_platform_trace.h"


/* 重定向日志输出 */
#undef WICED_BT_TRACE
#define WICED_BT_TRACE printf

/***************************************************************************************************
 *                                常量定义
 **************************************************************************************************/
#define BLE_COMM_MAX_CONN             1
#define APP_BUFFER_HEAP                0x1000
#define MAX_STRING_LENGTH              20

/* 自定义服务UUID */
#define UUID_COMM_SERVICE              0x66, 0x9a, 0x0c, 0x20, 0x00, 0x08, 0x96, 0x9e, 0xe2, 0x11, 0x9e, 0xb1, 0x18, 0x11, 0xec, 0xdb
#define UUID_COMM_CHARACTERISTIC       0x66, 0x9a, 0x0c, 0x20, 0x00, 0x08, 0x96, 0x9e, 0xe2, 0x11, 0x9e, 0xb1, 0xc8, 0x22, 0xec, 0xdb

/* GATT数据库句柄 */
#define HANDLE_COMM_SERVICE            0x0001
#define HANDLE_COMM_CHARACTERISTIC     0x0002
#define HANDLE_COMM_CHAR_VALUE         0x0003
#define HANDLE_COMM_CHAR_CFG_DESC      0x0004

/***************************************************************************************************
 *                                结构体定义
 **************************************************************************************************/
typedef struct
{
    uint16_t conn_id;                /* 连接ID */
    uint8_t remote_addr[6];          /* 远程设备地址 */
    uint8_t is_connected;            /* 连接状态标志 */
    uint16_t client_config;          /* 客户端配置(通知/指示) */
    char received_string[MAX_STRING_LENGTH + 1]; /* 接收到的字符串 */
    char send_string[MAX_STRING_LENGTH + 1];     /* 待发送的字符串 */
} ble_comm_state_t;

/***************************************************************************************************
 *                                全局变量
 **************************************************************************************************/
/* GATT数据库 */
const uint8_t ble_comm_gatt_database[] =
{
    /* 声明自定义通信服务 */
    PRIMARY_SERVICE_UUID128(HANDLE_COMM_SERVICE, UUID_COMM_SERVICE),

    /* 声明通信特征 - 支持读、写、通知和指示 */
    CHARACTERISTIC_UUID128(HANDLE_COMM_CHARACTERISTIC,
                          HANDLE_COMM_CHAR_VALUE,
                          UUID_COMM_CHARACTERISTIC,
                          GATTDB_CHAR_PROP_READ | GATTDB_CHAR_PROP_WRITE |
                          GATTDB_CHAR_PROP_NOTIFY | GATTDB_CHAR_PROP_INDICATE,
                          GATTDB_PERM_READABLE | GATTDB_PERM_WRITABLE),

    /* 客户端特征配置描述符 */
    CHAR_DESCRIPTOR_UUID16_WRITABLE(HANDLE_COMM_CHAR_CFG_DESC,
                                   UUID_DESCRIPTOR_CLIENT_CHARACTERISTIC_CONFIGURATION,
                                   GATTDB_PERM_READABLE | GATTDB_PERM_WRITABLE),
};

/* 应用程序状态 */
ble_comm_state_t ble_comm_state;

/* 特征值数据 */
char comm_char_value[MAX_STRING_LENGTH + 1] = "Hello BLE";

const cybt_platform_config_t bt_platform_cfg_settings =
{
    .hci_config =
    {
        .hci_transport = CYBT_HCI_UART,

        .hci =
        {
            .hci_uart =
            {
                .uart_tx_pin  = CYBSP_BT_UART_TX,
                .uart_rx_pin  = CYBSP_BT_UART_RX,
                .uart_rts_pin = CYBSP_BT_UART_RTS,
                .uart_cts_pin = CYBSP_BT_UART_CTS,

                .baud_rate_for_fw_download = CYBT_BAUD_RATE_FOR_FW_DOWNLOAD,
                .baud_rate_for_feature     = CYBT_BAUD_RATE_FOR_FEATURE,

                .data_bits    = 8,
                .stop_bits    = 1,
                .parity       = CYHAL_UART_PARITY_NONE,
                .flow_control = WICED_TRUE
            }
        }
    },

    .controller_config =
    {
        .bt_power_pin = CYBSP_BT_POWER,
        .sleep_mode   =
        {
#if (bt_0_power_0_ENABLED == 1)
#if (CYCFG_BT_LP_ENABLED == 1)
            .sleep_mode_enabled   = CYCFG_BT_LP_ENABLED,
            .device_wakeup_pin    = CYCFG_BT_DEV_WAKE_GPIO,
            .host_wakeup_pin      = CYCFG_BT_HOST_WAKE_GPIO,
            .device_wake_polarity = CYCFG_BT_DEV_WAKE_POLARITY,
            .host_wake_polarity   = CYCFG_BT_HOST_WAKE_IRQ_EVENT

            #else
            .sleep_mode_enabled   = WICED_FALSE
            #endif
        #else // if (bt_0_power_0_ENABLED == 1)
        .sleep_mode_enabled   = WICED_TRUE,
        .device_wakeup_pin    = CYBSP_BT_DEVICE_WAKE,
        .host_wakeup_pin      = CYBSP_BT_HOST_WAKE,
        .device_wake_polarity = CYBT_WAKE_ACTIVE_LOW,
        .host_wake_polarity   = CYBT_WAKE_ACTIVE_LOW
        #endif // if (bt_0_power_0_ENABLED == 1)
    }
    },

    .task_mem_pool_size = 2048
};
wiced_bt_cfg_ble_scan_settings_t hello_sensor_cfg_scan_settings =
{
    /**< BLE scan mode (BTM_BLE_SCAN_MODE_PASSIVE, BTM_BLE_SCAN_MODE_ACTIVE, or
         BTM_BLE_SCAN_MODE_NONE ) */
    .scan_mode                    = BTM_BLE_SCAN_MODE_ACTIVE,


    /* Advertisement scan configuration */

    /**< High duty scan interval */
    .high_duty_scan_interval      = WICED_BT_CFG_DEFAULT_HIGH_DUTY_SCAN_INTERVAL,

    /**< High duty scan window */
    .high_duty_scan_window        = WICED_BT_CFG_DEFAULT_HIGH_DUTY_SCAN_WINDOW,

    /**< High duty scan duration in seconds ( 0 for infinite ) */
    .high_duty_scan_duration      = 5,

    /**< Low duty scan interval  */
    .low_duty_scan_interval       = WICED_BT_CFG_DEFAULT_LOW_DUTY_SCAN_INTERVAL,

    /**< Low duty scan window */
    .low_duty_scan_window         = WICED_BT_CFG_DEFAULT_LOW_DUTY_SCAN_WINDOW,

    /**< Low duty scan duration in seconds ( 0 for infinite ) */
    .low_duty_scan_duration       = 5,


    /* Connection scan configuration */

    /**< High duty cycle connection scan interval */
    .high_duty_conn_scan_interval = WICED_BT_CFG_DEFAULT_HIGH_DUTY_CONN_SCAN_INTERVAL,

    /**< High duty cycle connection scan window */
    .high_duty_conn_scan_window   = WICED_BT_CFG_DEFAULT_HIGH_DUTY_CONN_SCAN_WINDOW,

    /**< High duty cycle connection duration in seconds ( 0 for infinite ) */
    .high_duty_conn_duration      = 30,

    /**< Low duty cycle connection scan interval */
    .low_duty_conn_scan_interval  = WICED_BT_CFG_DEFAULT_LOW_DUTY_CONN_SCAN_INTERVAL,

    /**< Low duty cycle connection scan window */
    .low_duty_conn_scan_window    = WICED_BT_CFG_DEFAULT_LOW_DUTY_CONN_SCAN_WINDOW,

    /**< Low duty cycle connection duration in seconds ( 0 for infinite ) */
    .low_duty_conn_duration       = 30,


    /* Connection configuration */

    /**< Minimum connection interval */
    .conn_min_interval            = WICED_BT_CFG_DEFAULT_CONN_MIN_INTERVAL,

    /**< Maximum connection interval */
    .conn_max_interval            = WICED_BT_CFG_DEFAULT_CONN_MAX_INTERVAL,

    /**< Connection latency */
    .conn_latency                 = WICED_BT_CFG_DEFAULT_CONN_LATENCY,

    /**< Connection link supervision timeout */
    .conn_supervision_timeout     = WICED_BT_CFG_DEFAULT_CONN_SUPERVISION_TIMEOUT
};


const wiced_bt_cfg_ble_advert_settings_t hello_sensor_cfg_adv_settings =
{
    /**< Advertising channel map ( mask of BTM_BLE_ADVERT_CHNL_37, BTM_BLE_ADVERT_CHNL_38,
         BTM_BLE_ADVERT_CHNL_39 ) */
    .channel_map                     = BTM_BLE_ADVERT_CHNL_37 |
                                       BTM_BLE_ADVERT_CHNL_38 |
                                       BTM_BLE_ADVERT_CHNL_39,

    /**< High duty undirected connectable minimum advertising interval */
    .high_duty_min_interval          = WICED_BT_CFG_DEFAULT_HIGH_DUTY_ADV_MIN_INTERVAL,

    /**< High duty undirected connectable maximum advertising interval */
    .high_duty_max_interval          = WICED_BT_CFG_DEFAULT_HIGH_DUTY_ADV_MAX_INTERVAL,

    /**< High duty undirected connectable advertising duration in seconds ( 0 for infinite ) */
    .high_duty_duration              = 30,

    /**< Low duty undirected connectable minimum advertising interval */
    .low_duty_min_interval           = 1024,

    /**< Low duty undirected connectable maximum advertising interval */
    .low_duty_max_interval           = 1024,

    /**< Low duty undirected connectable advertising duration in seconds ( 0 for infinite ) */
    .low_duty_duration               = 60,

    /**< High duty directed connectable minimum advertising interval */
    .high_duty_directed_min_interval = WICED_BT_CFG_DEFAULT_HIGH_DUTY_DIRECTED_ADV_MIN_INTERVAL,

    /**< High duty directed connectable maximum advertising interval */
    .high_duty_directed_max_interval = WICED_BT_CFG_DEFAULT_HIGH_DUTY_DIRECTED_ADV_MAX_INTERVAL,

    /**< Low duty directed connectable minimum advertising interval */
    .low_duty_directed_min_interval  = WICED_BT_CFG_DEFAULT_LOW_DUTY_DIRECTED_ADV_MIN_INTERVAL,

    /**< Low duty directed connectable maximum advertising interval */
    .low_duty_directed_max_interval  = WICED_BT_CFG_DEFAULT_LOW_DUTY_DIRECTED_ADV_MAX_INTERVAL,

    /**< Low duty directed connectable advertising duration in seconds ( 0 for infinite) */
    .low_duty_directed_duration      = 30,

    /**< High duty non-connectable minimum advertising interval */
    .high_duty_nonconn_min_interval  = WICED_BT_CFG_DEFAULT_HIGH_DUTY_NONCONN_ADV_MIN_INTERVAL,

    /**< High duty non-connectable maximum advertising interval */
    .high_duty_nonconn_max_interval  = WICED_BT_CFG_DEFAULT_HIGH_DUTY_NONCONN_ADV_MAX_INTERVAL,

    /**< High duty non-connectable advertising duration in seconds ( 0 for infinite) */
    .high_duty_nonconn_duration      = 30,

    /**< Low duty non-connectable minimum advertising interval */
    .low_duty_nonconn_min_interval   = WICED_BT_CFG_DEFAULT_LOW_DUTY_NONCONN_ADV_MIN_INTERVAL,

    /**< Low duty non-connectable maximum advertising interval */
    .low_duty_nonconn_max_interval   = WICED_BT_CFG_DEFAULT_LOW_DUTY_NONCONN_ADV_MAX_INTERVAL,

    /**< Low duty non-connectable advertising duration in seconds ( 0 for infinite) */
    .low_duty_nonconn_duration       = 0
};
wiced_bt_cfg_ble_t hello_sensor_cfg_ble =
{
    .ble_max_simultaneous_links   = 1,
    .ble_max_rx_pdu_size          = 65,

    .p_ble_scan_cfg               = &hello_sensor_cfg_scan_settings, /**< */
    .p_ble_advert_cfg             = &hello_sensor_cfg_adv_settings,
    .appearance                   = APPEARANCE_GENERIC_TAG, /**< GATT appearance (see
                                                               gatt_appearance_e) */

    /**< LE Address Resolution DB settings - effective only for pre 4.2 controller*/
    .host_addr_resolution_db_size = 5,

    /**< Interval of  random address refreshing - secs */
    .rpa_refresh_timeout          = WICED_BT_CFG_DEFAULT_RANDOM_ADDRESS_NEVER_CHANGE
};

wiced_bt_cfg_gatt_t hello_sensor_cfg_gatt =
{
    .max_db_service_modules = 0,   /**< Maximum number of service modules in the DB*/
    .max_eatt_bearers       = 0,   /**< Maximum number of allowed gatt bearers */
};
wiced_bt_cfg_settings_t wiced_bt_cfg_settings =
{
    .device_name = (uint8_t*)"hello",     /**< Local device name ( NULL terminated ) */
    .p_ble_cfg   = &hello_sensor_cfg_ble,
    .p_gatt_cfg  = &hello_sensor_cfg_gatt,
};

/***************************************************************************************************
 *                                函数声明
 **************************************************************************************************/
static wiced_result_t ble_comm_management_cback(wiced_bt_management_evt_t event,
                                               wiced_bt_management_evt_data_t* p_event_data);
static wiced_bt_gatt_status_t ble_comm_gatts_callback(wiced_bt_gatt_evt_t event,
                                                     wiced_bt_gatt_event_data_t* p_data);
static void ble_comm_set_advertisement_data(void);
static void ble_comm_send_string(void);
static void ble_comm_application_init(void);

/***************************************************************************************************
 *                                工具函数
 **************************************************************************************************/
void print_bd_address(uint8_t *bd_addr)
{
    printf("%02X:%02X:%02X:%02X:%02X:%02X",
           bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);
}

/***************************************************************************************************
 * 应用程序入口点
 **************************************************************************************************/
void BLE_App_Start(void)
{
    stm32_cypal_bt_init(&huart3, &hlptim1);
    /* configure BLE Platform */
    cybt_platform_config_init(&bt_platform_cfg_settings);
    /* Start BLE Communication */
    WICED_BT_TRACE("BLE Communication Start\n");

    /* 初始化状态 */
    memset(&ble_comm_state, 0, sizeof(ble_comm_state_t));

    /* 注册管理回调并初始化蓝牙栈 */
    wiced_bt_stack_init(ble_comm_management_cback, &wiced_bt_cfg_settings);

    /* 创建缓冲区堆 */
    wiced_bt_create_heap("app", NULL, APP_BUFFER_HEAP, NULL, WICED_TRUE);
}

/***************************************************************************************************
 * 蓝牙管理回调
 **************************************************************************************************/
wiced_result_t ble_comm_management_cback(wiced_bt_management_evt_t event,
                                        wiced_bt_management_evt_data_t* p_event_data)
{
    wiced_result_t result = WICED_BT_SUCCESS;

    switch (event)
    {
        /* 蓝牙栈已启用 */
        case BTM_ENABLED_EVT:
            ble_comm_application_init();
            break;

        /* 连接状态变化 */
        case BTM_BLE_CONNECTION_PARAM_UPDATE:
            WICED_BT_TRACE("Connection parameters updated\n");
            break;

        /* 广告状态变化 */
        case BTM_BLE_ADVERT_STATE_CHANGED_EVT:
            if (p_event_data->ble_advert_state_changed == BTM_BLE_ADVERT_OFF)
            {
                WICED_BT_TRACE("Advertisement stopped\n");
            }
            break;

        default:
            break;
    }

    return result;
}

/***************************************************************************************************
 * 应用程序初始化
 **************************************************************************************************/
void ble_comm_application_init(void)
{
    wiced_bt_gatt_status_t gatt_status;
    wiced_result_t result;
    uint8_t bda[6] = {0};

    WICED_BT_TRACE("Initializing BLE Communication Application\n");

    /* 注册GATT回调 */
    gatt_status = wiced_bt_gatt_register(ble_comm_gatts_callback);
    WICED_BT_TRACE("GATT register status: %d\n", gatt_status);

    /* 初始化GATT数据库 */
    gatt_status = wiced_bt_gatt_db_init(ble_comm_gatt_database,
                                       sizeof(ble_comm_gatt_database), NULL);
    WICED_BT_TRACE("GATT DB init status: %d\n", gatt_status);

    /* 设置广告数据并开始广告 */
    ble_comm_set_advertisement_data();
    result = wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL);
    WICED_BT_TRACE("Start advertisements: %d\n", result);

    /* 读取并打印本地蓝牙地址 */
    wiced_bt_dev_read_local_addr(bda);
    printf("Local Bluetooth Address: ");
    print_bd_address(bda);
    printf("\n");
}

/***************************************************************************************************
 * 设置广告数据
 **************************************************************************************************/
void ble_comm_set_advertisement_data(void)
{
    wiced_bt_ble_advert_elem_t adv_elem[3];
    uint8_t num_elem = 0;
    uint8_t flag = BTM_BLE_GENERAL_DISCOVERABLE_FLAG | BTM_BLE_BREDR_NOT_SUPPORTED;

    /* 服务UUID */
    uint8_t comm_service_uuid[16] = {UUID_COMM_SERVICE};

    /* 广告标志 */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_FLAG;
    adv_elem[num_elem].len = sizeof(uint8_t);
    adv_elem[num_elem].p_data = &flag;
    num_elem++;

    /* 服务UUID */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE;
    adv_elem[num_elem].len = 16;
    adv_elem[num_elem].p_data = comm_service_uuid;
    num_elem++;

    /* 设备名称 */
    adv_elem[num_elem].advert_type = BTM_BLE_ADVERT_TYPE_NAME_COMPLETE;
    adv_elem[num_elem].len = (uint8_t)strlen("BLE Comm");
    adv_elem[num_elem].p_data = (uint8_t*)"BLE Comm";
    num_elem++;

    /* 设置广告数据 */
    wiced_bt_ble_set_raw_advertisement_data(num_elem, adv_elem);
}

/***************************************************************************************************
 * 发送字符串数据
 **************************************************************************************************/
void ble_comm_send_string(void)
{
    /* 检查客户端是否已启用通知或指示 */
    if (ble_comm_state.client_config == 0)
    {
        WICED_BT_TRACE("Client has not enabled notifications/indications\n");
        return;
    }

    /* 检查是否已连接 */
    if (!ble_comm_state.is_connected)
    {
        WICED_BT_TRACE("Not connected, cannot send data\n");
        return;
    }

    WICED_BT_TRACE("Sending: %s\n", ble_comm_state.send_string);

    /* 发送通知 */
    if (ble_comm_state.client_config & GATT_CLIENT_CONFIG_NOTIFICATION)
    {
        wiced_bt_gatt_server_send_notification(ble_comm_state.conn_id,
                                              HANDLE_COMM_CHAR_VALUE,
                                              strlen(ble_comm_state.send_string),
                                              (uint8_t*)ble_comm_state.send_string,
                                              NULL);
    }
    /* 发送指示（需要确认） */
    else if (ble_comm_state.client_config & GATT_CLIENT_CONFIG_INDICATION)
    {
        wiced_bt_gatt_server_send_indication(ble_comm_state.conn_id,
                                            HANDLE_COMM_CHAR_VALUE,
                                            strlen(ble_comm_state.send_string),
                                            (uint8_t*)ble_comm_state.send_string,
                                            NULL);
    }
}

/***************************************************************************************************
 * 设置要发送的字符串
 **************************************************************************************************/
void ble_comm_set_send_string(const char* str)
{
    strncpy(ble_comm_state.send_string, str, MAX_STRING_LENGTH);
    ble_comm_state.send_string[MAX_STRING_LENGTH] = '\0'; // 确保字符串终止
}

/***************************************************************************************************
 * 获取接收到的字符串
 **************************************************************************************************/
const char* ble_comm_get_received_string(void)
{
    return ble_comm_state.received_string;
}

/***************************************************************************************************
 * GATT回调函数
 **************************************************************************************************/
wiced_bt_gatt_status_t ble_comm_gatts_callback(wiced_bt_gatt_evt_t event,
                                              wiced_bt_gatt_event_data_t* p_data)
{
    wiced_bt_gatt_status_t result = WICED_BT_GATT_SUCCESS;

    switch (event)
    {
        /* 连接状态事件 */
        case GATT_CONNECTION_STATUS_EVT:
        {
            wiced_bt_gatt_connection_status_t* p_conn = &p_data->connection_status;

            if (p_conn->connected)
            {
                /* 连接建立 */
                WICED_BT_TRACE("Connected to: ");
                print_bd_address(p_conn->bd_addr);
                printf("\n");

                ble_comm_state.conn_id = p_conn->conn_id;
                memcpy(ble_comm_state.remote_addr, p_conn->bd_addr, 6);
                ble_comm_state.is_connected = 1;

                /* 停止广告 */
                wiced_bt_start_advertisements(BTM_BLE_ADVERT_OFF, 0, NULL);
            }
            else
            {
                /* 连接断开 */
                WICED_BT_TRACE("Disconnected, reason: %d\n", p_conn->reason);

                memset(&ble_comm_state, 0, sizeof(ble_comm_state_t));

                /* 重新开始广告 */
                wiced_bt_start_advertisements(BTM_BLE_ADVERT_UNDIRECTED_HIGH, 0, NULL);
            }
            break;
        }

        /* 属性请求事件 */
        case GATT_ATTRIBUTE_REQUEST_EVT:
        {
            wiced_bt_gatt_attribute_request_t* p_req = &p_data->attribute_request;

            switch (p_req->opcode)
            {
                /* 读取请求 */
                case GATT_REQ_READ:
                {
                    if (p_req->data.read_req.handle == HANDLE_COMM_CHAR_VALUE)
                    {
                        /* 返回特征值 */
                        wiced_bt_gatt_server_send_read_handle_rsp(
                            p_req->conn_id,
                            p_req->opcode,
                            strlen(comm_char_value),
                            (uint8_t*)comm_char_value,
                            NULL);
                    }
                    break;
                }

                /* 写入请求 */
                case GATT_REQ_WRITE:
                case GATT_CMD_WRITE:
                {
                    if (p_req->data.write_req.handle == HANDLE_COMM_CHAR_VALUE)
                    {
                        /* 处理特征值写入 */
                        uint16_t len = p_req->data.write_req.val_len;
                        if (len > MAX_STRING_LENGTH) len = MAX_STRING_LENGTH;

                        memcpy(ble_comm_state.received_string,
                               p_req->data.write_req.p_val,
                               len);
                        ble_comm_state.received_string[len] = '\0';

                        WICED_BT_TRACE("Received: %s\n", ble_comm_state.received_string);

                        /* 发送响应（仅对需要响应的写入） */
                        if (p_req->opcode == GATT_REQ_WRITE)
                        {
                            wiced_bt_gatt_server_send_write_rsp(
                                p_req->conn_id,
                                p_req->opcode,
                                p_req->data.write_req.handle);
                        }
                    }
                    else if (p_req->data.write_req.handle == HANDLE_COMM_CHAR_CFG_DESC)
                    {
                        /* 处理客户端配置描述符写入 */
                        if (p_req->data.write_req.val_len == 2)
                        {
                            ble_comm_state.client_config =
                                p_req->data.write_req.p_val[0] |
                                (p_req->data.write_req.p_val[1] << 8);

                            WICED_BT_TRACE("Client config set to: 0x%04X\n",
                                          ble_comm_state.client_config);
                        }

                        /* 发送响应 */
                        wiced_bt_gatt_server_send_write_rsp(
                            p_req->conn_id,
                            p_req->opcode,
                            p_req->data.write_req.handle);
                    }
                    break;
                }

                default:
                    break;
            }
            break;
        }

        /* 指示确认 */
        case GATT_HANDLE_VALUE_CONF:
            WICED_BT_TRACE("Indication confirmed\n");
            break;

        default:
            break;
    }

    return result;
}

/***************************************************************************************************
 * 主循环示例（在实际应用中可能需要实现）
 **************************************************************************************************/
void application_main_loop(void)
{
    /* 在实际应用中，这里会有主循环处理 */
    /* 例如：定期发送数据或响应外部事件 */

    /* 示例：每5秒发送一次数据 */
    static uint32_t last_send_time = 0;
    uint32_t current_time = xTaskGetTickCount() / 1000;

    if (current_time - last_send_time >= 5)
    {
        last_send_time = current_time;

        if (ble_comm_state.is_connected)
        {
            /* 准备要发送的字符串 */
            static uint8_t counter = 0;
            char message[20];
            snprintf(message, sizeof(message), "Message %d", counter++);

            /* 设置并发送字符串 */
            ble_comm_set_send_string(message);
            ble_comm_send_string();
        }
    }

    /* 处理接收到的数据 */
    if (strlen(ble_comm_get_received_string()) > 0)
    {
        WICED_BT_TRACE("Processing received: %s\n", ble_comm_get_received_string());

        /* 清空接收缓冲区 */
        ble_comm_state.received_string[0] = '\0';
    }
}

