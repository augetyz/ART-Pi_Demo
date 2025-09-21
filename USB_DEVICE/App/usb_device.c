/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
#include <string.h> // 包含字符串处理函数声明
#include <stdarg.h> // 包含可变参数函数处理宏声明

//myprintf相关
#define DMA_MODE 0
#define USB_DEBUG 1
#define UART_HANDLER huart3
#define BUFFER_SIZE 1024 // 定义缓冲区大小为100字节

DMA_DATA static uint8_t debug_buffer[BUFFER_SIZE];

void my_printf(const char *fmt, ...)
{
    va_list args; // 定义一个变量参数列表
    int     len;  // 用于存储格式化后的字符串长度

    // 初始化变量参数列表，使其指向fmt后面的参数
    va_start(args, fmt);

    // 使用vsnprintf函数将格式化的字符串写入debug_buffer，BUFFER_SIZE作为最大长度限制以防止溢出
    len = vsnprintf((char *) debug_buffer, BUFFER_SIZE, fmt, args);

    // 检查是否发生缓冲区溢出
    if (len >= BUFFER_SIZE)
    {
        // 处理潜在的缓冲区溢出错误，这里可以选择记录警告信息
        len = BUFFER_SIZE - 1; // 确保字符串被正确终止
    }

    // 确保字符串以空字符终止
    debug_buffer[len] = '\0';

    // 通过CDC接口发送格式化后的数据，len为实际发送的字节数（不包括末尾的'\0'）
#if USB_DEBUG
    CDC_Transmit_FS(debug_buffer, len);
#elif DMA_MODE
  HAL_UART_Transmit_DMA(&UART_HANDLER,debug_buffer,len);
#else
  HAL_UART_Transmit(&UART_HANDLER,debug_buffer,len,HAL_MAX_DELAY);
#endif

    // 清理变量参数列表，释放相关资源
    va_end(args);
}

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_DEVICE_Init(void)
{
    /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */

    /* USER CODE END USB_DEVICE_Init_PreTreatment */

    /* Init Device Library, add supported class and start the library. */
    if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */
    HAL_PWREx_EnableUSBVoltageDetector();

    /* USER CODE END USB_DEVICE_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */
