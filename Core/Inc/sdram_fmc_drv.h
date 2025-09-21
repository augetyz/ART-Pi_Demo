
#ifndef STM32H750XBH6_7_CACHE_TEST_SDRAM_FMC_DRV_H
#define STM32H750XBH6_7_CACHE_TEST_SDRAM_FMC_DRV_H

/**
 *@file    sdram_fmc_drv.h
 *@brief   使用 FMC 操作 SDRAM
 *@author  mculover666
 *@date    2020-08-27
 *@note    此驱动测试 W9825G6KH SDRAM芯片通过
*/


#include "fmc.h"

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

//宏定义SDRAM的映射地址以及SDRAM的大小
#define EXT_SDRAM_ADDR  	((uint32_t)0xC0000000)
#define EXT_SDRAM_SIZE		(32 * 1024 * 1024)

void SDRAM_Init(void);
uint32_t bsp_TestExtSDRAM(void);


#endif //STM32H750XBH6_7_CACHE_TEST_SDRAM_FMC_DRV_H
