/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    custom_rng.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-June-2017
  * @brief   mbedtls alternate entropy data function skeleton to be completed by the user.
  *
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

#include "mbedtls_config.h"

#ifdef MBEDTLS_ENTROPY_HARDWARE_ALT

#include "main.h"
#include "string.h"
#include "stm32h7xx_hal.h"
#include "mbedtls/entropy_poll.h"

extern RNG_HandleTypeDef hrng;  // 在 main.c / MX_RNG_Init() 里初始化过

int mbedtls_hardware_poll( void *Data,
                           unsigned char *Output,
                           size_t Len,
                           size_t *oLen )
{
  size_t count = 0;
  uint32_t random_val;

  (void) Data;  // 未使用参数，避免警告

  while (count < Len)
  {
    if (HAL_RNG_GenerateRandomNumber(&hrng, &random_val) == HAL_OK)
    {
      size_t copy_len = (Len - count) < sizeof(random_val) ? (Len - count) : sizeof(random_val);
      memcpy(Output + count, &random_val, copy_len);
      count += copy_len;
    }
    else
    {
      return -1;  // RNG 出错
    }
  }

  *oLen = count;
  return 0; // 成功
}


#endif /*MBEDTLS_ENTROPY_HARDWARE_ALT*/
