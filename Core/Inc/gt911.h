/*
*********************************************************************************************************
*
*	模块名称 : GT911电容触摸芯片驱动程序
*	文件名称 : bsp_GT911.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2017-2025, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_GT911_H
#define _BSP_GT911_H

#include "main.h"

#define GT911_I2C_ADDR1	0xBA

typedef struct
{
    uint8_t Enable;
    uint8_t TimerCount;
    uint8_t i2c_addr;

    uint8_t TouchpointFlag;
    uint8_t Touchkeystate;

    uint16_t X0;
    uint16_t Y0;
    uint16_t P0;

    uint16_t X1;
    uint16_t Y1;
    uint16_t P1;

    uint16_t X2;
    uint16_t Y2;
    uint16_t P2;

    uint16_t X3;
    uint16_t Y3;
    uint16_t P3;

    uint16_t X4;
    uint16_t Y4;
    uint16_t P4;
}GT911_T;

typedef struct {
    uint8_t Point_ID[5];
    uint8_t Touch_num;
    uint8_t Press_Status;
    uint16_t Coord_X[5];
    uint16_t Coord_Y[5];
}Touch_Point;

void Int_GPIO_Output();
void Int_GPIO_Input();

void TouchReset();
void touch_test();
void Touch_Init(void);
void Touch_ReadMaxXY(uint16_t *X,uint16_t *Y);
void Touch_scan(Touch_Point* Touch_use);
void Touch_SoftRst();

#endif
