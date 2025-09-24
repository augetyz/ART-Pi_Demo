#include "gt911.h"
#include "i2c.h"
#include "main.h"

#define GT911_READ_XY_REG				0x814E /* 坐标寄存器 */
#define GT911_CLEARBUF_REG				0x814E /* 清除坐标寄存器 */
#define GT911_CONFIG_REG				0x8047 /* 配置参数寄存器 */
#define GT911_COMMAND_REG				0x8040 /* 实时命令 */
#define GT911_PRODUCT_ID_REG			0x8140 /* 芯片ID */
#define GT911_VENDOR_ID_REG				0x814A /* 当前模组选项信息 */
#define GT911_CONFIG_VERSION_REG		0x8047 /* 配置文件版本号 */
#define GT911_CONFIG_CHECKSUM_REG		0x80FF /* 配置文件校验码 */
#define GT911_FIRMWARE_VERSION_REG		0x8144 /* 固件版本号 */

#define GT911_ADDR						0X5D

#define GT_GSTID_REG 					0X814E  /* GT9147当前检测到的触摸情况 */
#define GT_TP1_REG 						0X8150  /* 第一个触摸点数据地址 */
#define GT_TP2_REG 						0X8158	/* 第二个触摸点数据地址 */
#define GT_TP3_REG 						0X8160  /* 第三个触摸点数据地址 */
#define GT_TP4_REG 						0X8168  /* 第四个触摸点数据地址  */
#define GT_TP5_REG 						0X8170	/* 第五个触摸点数据地址   */

#define TS_RST_0 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_RESET) // 根据实际引脚修改
#define TS_RST_1 HAL_GPIO_WritePin(TS_RST_GPIO_Port, TS_RST_Pin, GPIO_PIN_SET)   // 根据实际引脚修改

static void Touch_Read_Reg(uint16_t reg_address, uint8_t *pdate, uint16_t size);
static void Touch_Write_Reg(uint16_t reg_address, uint8_t *pdate, uint16_t size);
static uint8_t TouchAddr = GT911_ADDR;

void TouchReset()
{
    TS_RST_0;
    HAL_Delay(20);
    TS_RST_1;
    HAL_Delay(20);
}

void Touch_Read_Reg(uint16_t reg_address, uint8_t *pdate, uint16_t size)
{
    HAL_I2C_Mem_Read(&hi2c1,TouchAddr << 1, reg_address,I2C_MEMADD_SIZE_16BIT, pdate, size, 0XFF);
}

void Touch_Write_Reg(uint16_t reg_address, uint8_t *pdate, uint16_t size)
{
    HAL_I2C_Mem_Write(&hi2c1,TouchAddr << 1, reg_address,I2C_MEMADD_SIZE_16BIT, pdate, size, 0XFF);
}

void Touch_Init(void)
{
    uint8_t  mode      = 0x00;
    uint8_t  buffer[8] = {0};
	TS_INT_GPIO_Port->ODR |= TS_INT_Pin;
	TouchReset();
	// INT 改成输入模式，给 GT911 用来产生中断
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = TS_INT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(TS_INT_GPIO_Port, &GPIO_InitStruct);
	/*检测I2C设备地址是否有回应*/
    if (HAL_I2C_IsDeviceReady(&hi2c1, 0x5D << 1, 2, 100) == HAL_OK)
    {
        TouchAddr = 0x5D;
        printf("GT911 found at 0x5D\r\n");
    }
	else if (HAL_I2C_IsDeviceReady(&hi2c1, 0x14 << 1, 2, 100) == HAL_OK)
    {
	    TouchAddr = 0x14;
    	printf("GT911 found at 0x14\r\n");
    }
    else
    {
        printf("GT911 not found!\r\n");
    }
    Touch_Read_Reg(GT911_PRODUCT_ID_REG, buffer, 6);
    buffer[6] = buffer[4];
    buffer[4] = 0;
    // printf("Touch screen Version:%s\r\n", buffer);
    // printf("Default Ver:%#x\r\n", ((buffer[5] << 8) | buffer[6])); /* 打印固件版本 */

    if (buffer[0] != 0x31)
    {
        Touch_Read_Reg(0x804D, buffer, 1);
        buffer[0] &= 0x3; /* 获取中断模式 */
        //        printf("buffer[0] != 0x31\r\n");
    }
    else
    {
        Touch_Read_Reg(0x8056, buffer, 1);
        buffer[0] &= 0x3; /* 获取中断模式 */
    }
    // switch (buffer[0])
    // {
    // case 0x0:
    //     printf("InterruptMode:IntRisingEdge\r\n");
    //     break;
    // case 0x1:
    //     printf("InterruptMode:IntFallingEdge\r\n");
    //     break;
    // case 0x2:
    //     printf("InterruptMode:IntLowLevel\r\n");
    //     break;
    // case 0x3:
    //     printf("InterruptMode:IntHighLevel\r\n");
    //     break;
    // default:
    //     printf("InterruptMode: Error\r\n");
    //     break;
    // }
    mode = 0;
    Touch_Write_Reg(GT911_CLEARBUF_REG, &mode, 1); //清标志
    HAL_Delay(5);
}

void Touch_ReadMaxXY(uint16_t *X, uint16_t *Y)
{
    uint8_t buf[4];
    Touch_Read_Reg(GT911_ADDR, buf, 4);
    *X = buf[0] + buf[1] * 256;
    *Y = buf[2] + buf[3] * 256;
}

void Touch_scan(Touch_Point *Touch_use)
{
    static uint16_t a = 0, b = 0;
    uint8_t  num_fingers = 0;
    uint8_t  buffer[8]   = {0};
    uint16_t coord_X, coord_Y;
    uint8_t  i;

    // 读取触摸状态
    Touch_Read_Reg(GT_GSTID_REG, &num_fingers, 1);
    Touch_Write_Reg(GT_GSTID_REG, &(uint8_t){0}, 1); // 清标志

    Touch_use->Press_Status = (num_fingers & 0x10) >> 4;
    num_fingers &= 0x0F; // 取低4位触点数

    if (num_fingers == 0)
    {
        b++;
        if (b <= 1) // 防抖阈值
        {
            if (a > 0)
            {
                Touch_use->Touch_num = 1; // 仍然认为有触摸
                return;
            }
            else
            {
                Touch_use->Touch_num = 0;
                return;
            }
        }
        else
        {
            a = b = 0;
            Touch_use->Touch_num = 0;
            return;
        }
    }

    // 有触点，重置无触摸计数
    a++;
    b = 0;
    Touch_use->Touch_num = num_fingers;

    // 读取每个触点信息
    for (i = 0; i < num_fingers; i++)
    {
        Touch_Read_Reg(GT_TP1_REG + i * 8, buffer, 8);

        coord_X = ((uint16_t)buffer[1] << 8) | buffer[0];
        coord_Y = ((uint16_t)buffer[3] << 8) | buffer[2];

        Touch_use->Coord_X[i]  = coord_X;
        Touch_use->Coord_Y[i]  = coord_Y;
        Touch_use->Point_ID[i] = buffer[4]; // 使用 GT911 实际触点 ID
    }
}

