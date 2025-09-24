/* Includes ------------------------------------------------------------------*/
#include "ltdc.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "dma2d.h"
// LCD帧缓冲区首地址，定义在SDRAM中

// 定义满足大屏分辨率时，LCD使用的帧缓存数组大小
ExtSRAM uint16_t LTDC_Buffer[PIXELS_W*PIXELS_H];

/* USER CODE END 0 */

// LTDC句柄结构体定义
LTDC_HandleTypeDef hltdc;

/* LTDC初始化函数 */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  // 定义图层配置结构体
  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  // 配置LTDC实例
  hltdc.Instance = LTDC;
  // 配置水平同步极性为高电平有效
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  // 配置垂直同步极性为高电平有效
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  // 配置数据使能极性为高电平有效
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  // 配置像素时钟极性为数据在时钟下降沿有效
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  // 配置水平同步宽度为19个时钟周期
  hltdc.Init.HorizontalSync = 19;
  // 配置垂直同步宽度为2行
  hltdc.Init.VerticalSync = 2;
  // 配置水平后沿为159个时钟周期
  hltdc.Init.AccumulatedHBP = 159;
  // 配置垂直后沿为22行
  hltdc.Init.AccumulatedVBP = 22;
  // 配置水平有效区域宽度为1183个时钟周期
  hltdc.Init.AccumulatedActiveW = 1183;
  // 配置垂直有效区域高度为622行
  hltdc.Init.AccumulatedActiveH = 622;
  // 配置总宽度为1343个时钟周期
  hltdc.Init.TotalWidth = 1343;
  // 配置总高度为634行
  hltdc.Init.TotalHeigh = 634;
  // 配置背景色为黑色
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  // 初始化LTDC，如果失败则进入错误处理
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  // 配置图层0窗口起始坐标为(0,0)
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowY0 = 0;
  // 配置图层0窗口结束坐标为(1024,600)
  pLayerCfg.WindowX1 = 1024;
  pLayerCfg.WindowY1 = 600;
  // 配置像素格式为RGB565
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  // 配置图层透明度为255（完全不透明）
  pLayerCfg.Alpha = 255;
  // 配置透明颜色为0
  pLayerCfg.Alpha0 = 0;
  // 配置混合因子
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  // 配置帧缓冲区起始地址
  pLayerCfg.FBStartAdress = (uint32_t)LTDC_Buffer;
  // 配置图像宽度为1024像素
  pLayerCfg.ImageWidth = 1024;
  // 配置图像高度为600像素
  pLayerCfg.ImageHeight = 600;
  // 配置图层背景色为白色
  pLayerCfg.Backcolor.Blue = 255;
  pLayerCfg.Backcolor.Green = 255;
  pLayerCfg.Backcolor.Red = 255;
  // 配置LTDC图层，如果失败则进入错误处理
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
//    LTDC->LIPCR = 623-1; // 配置行中断的行数为最后一行
//    LTDC->IER |= LTDC_IER_LIE; // 使能LTDC行中断
//    LTDC->SRCR |= (1<<1);
    // 配置行事件中断，在第623行触发
    HAL_LTDC_ProgramLineEvent(&hltdc,623);
  /* USER CODE END LTDC_Init 2 */

}

/* LTDC MSP初始化函数 - 配置底层硬件资源 */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** 初始化外设时钟
  */
    // 选择LTDC外设时钟
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    // 配置PLL3参数
    PeriphClkInitStruct.PLL3.PLL3M = 1;     // 输入分频因子
    PeriphClkInitStruct.PLL3.PLL3N = 12;    // VCO乘法因子
    PeriphClkInitStruct.PLL3.PLL3P = 2;     // P输出分频因子
    PeriphClkInitStruct.PLL3.PLL3Q = 2;     // Q输出分频因子
    PeriphClkInitStruct.PLL3.PLL3R = 5;     // R输出分频因子
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_3;  // 参考频率范围
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;  // VCO频率范围选择宽频
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0; // 小数部分
    // 配置外设时钟，如果失败则进入错误处理
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* 使能LTDC时钟 */
    __HAL_RCC_LTDC_CLK_ENABLE();

    /* 使能相关GPIO时钟 */
    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**LTDC GPIO配置
    PK5     ------> LTDC_B6    // 蓝色通道第6位
    PK4     ------> LTDC_B5    // 蓝色通道第5位
    PJ15    ------> LTDC_B3    // 蓝色通道第3位
    PK6     ------> LTDC_B7    // 蓝色通道第7位
    PK3     ------> LTDC_B4    // 蓝色通道第4位
    PK7     ------> LTDC_DE    // 数据使能信号
    PJ14    ------> LTDC_B2    // 蓝色通道第2位
    PJ12    ------> LTDC_B0    // 蓝色通道第0位
    PJ13    ------> LTDC_B1    // 蓝色通道第1位
    PI12    ------> LTDC_HSYNC // 水平同步信号
    PI13    ------> LTDC_VSYNC // 垂直同步信号
    PI14    ------> LTDC_CLK   // 像素时钟
    PK2     ------> LTDC_G7    // 绿色通道第7位
    PK0     ------> LTDC_G5    // 绿色通道第5位
    PK1     ------> LTDC_G6    // 绿色通道第6位
    PJ11    ------> LTDC_G4    // 绿色通道第4位
    PJ10    ------> LTDC_G3    // 绿色通道第3位
    PJ9     ------> LTDC_G2    // 绿色通道第2位
    PJ0     ------> LTDC_R1    // 红色通道第1位
    PJ8     ------> LTDC_G1    // 绿色通道第1位
    PJ7     ------> LTDC_G0    // 绿色通道第0位
    PJ6     ------> LTDC_R7    // 红色通道第7位
    PI15    ------> LTDC_R0    // 红色通道第0位
    PJ1     ------> LTDC_R2    // 红色通道第2位
    PJ5     ------> LTDC_R6    // 红色通道第6位
    PJ2     ------> LTDC_R3    // 红色通道第3位
    PJ3     ------> LTDC_R4    // 红色通道第4位
    PJ4     ------> LTDC_R5    // 红色通道第5位
    */
    // 配置GPIOK引脚
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;      // 复用推挽输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // 不上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 超高速
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;  // 复用为LTDC功能
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    // 配置GPIOJ引脚
    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_0
                          |GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1
                          |GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    // 配置GPIOI引脚
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* 配置LTDC中断 */
    HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);  // 设置中断优先级
    HAL_NVIC_EnableIRQ(LTDC_IRQn);          // 使能中断
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

/* LTDC MSP反初始化函数 - 释放底层硬件资源 */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* 禁用LTDC时钟 */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO配置
    PK5     ------> LTDC_B6
    PK4     ------> LTDC_B5
    PJ15    ------> LTDC_B3
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PK7     ------> LTDC_DE
    PJ14    ------> LTDC_B2
    PJ12    ------> LTDC_B0
    PJ13    ------> LTDC_B1
    PI12    ------> LTDC_HSYNC
    PI13    ------> LTDC_VSYNC
    PI14    ------> LTDC_CLK
    PK2     ------> LTDC_G7
    PK0     ------> LTDC_G5
    PK1     ------> LTDC_G6
    PJ11    ------> LTDC_G4
    PJ10    ------> LTDC_G3
    PJ9     ------> LTDC_G2
    PJ0     ------> LTDC_R1
    PJ8     ------> LTDC_G1
    PJ7     ------> LTDC_G0
    PJ6     ------> LTDC_R7
    PI15    ------> LTDC_R0
    PJ1     ------> LTDC_R2
    PJ5     ------> LTDC_R6
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    PJ4     ------> LTDC_R5
    */
    // 反初始化GPIOK引脚
    HAL_GPIO_DeInit(GPIOK, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1);

    // 反初始化GPIOJ引脚
    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_0
                          |GPIO_PIN_8|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_1
                          |GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);

    // 反初始化GPIOI引脚
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    /* 禁用LTDC中断 */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/**
 * @brief  LTDC矩形填充函数，使用DMA2D进行填充
 * @param  sx: 起始X坐标
 * @param  sy: 起始Y坐标
 * @param  ex: 结束X坐标
 * @param  ey: 结束Y坐标
 * @param  color: 要填充的颜色值
 * @note   为了速度，填充函数采用寄存器直接操作版本
 */
void LTDC_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{
    uint32_t psx,psy,pex,pey;    // 以LCD面板为基准的坐标，不随横竖屏变化而变化
    uint32_t timeout=0;          // 超时计数器
    uint16_t offline;            // 行偏移量
    uint32_t addr;               // 写入地址

    // 坐标系转换
    if(PIXELS_DIR)    // 横屏模式
    {
        psx=sx;psy=sy;
        pex=ex;pey=ey;
    }
    else            // 竖屏模式
    {
        psx=sy;psy=PIXELS_H-ex-1;
        pex=ey;pey=PIXELS_H-sx-1;
    }
    // 计算行偏移量
    offline=PIXELS_W-(pex-psx+1);
    // 计算起始地址
    addr=((uint32_t)&LTDC_Buffer[0]+2*(PIXELS_W*psy+psx));

    __HAL_RCC_DMA2D_CLK_ENABLE();  // 使能DMA2D时钟
    DMA2D->CR&=~(DMA2D_CR_START);  // 先停止DMA2D
    DMA2D->CR=DMA2D_R2M;           // 设置为寄存器到存储器模式
    DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;  // 设置颜色格式为RGB565
    DMA2D->OOR=offline;            // 设置行偏移

    DMA2D->OMAR=addr;              // 设置输出存储器地址
    // 设置行数和像素数
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);
    DMA2D->OCOLR=color;            // 设置输出颜色寄存器
    DMA2D->CR|=DMA2D_CR_START;     // 启动DMA2D传输
    // 等待传输完成
    while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)
    {
        timeout++;                 // 超时计数
        if(timeout>0XFFFFFF)break; // 超时退出
    }
    DMA2D->IFCR|=DMA2D_FLAG_TC;    // 清除传输完成标志
}

/**
 * @brief  LTDC图像传输函数
 * @param  sx: 起始X坐标
 * @param  sy: 起始Y坐标
 * @param  ex: 结束X坐标
 * @param  ey: 结束Y坐标
 * @param  color: 图像数据数组指针
 */
void LTDC_Transmit(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t* color)
{
    uint32_t psx,psy,pex,pey;    // 以LCD面板为基准的坐标，不随横竖屏变化而变化
    uint32_t timeout=0;          // 超时计数器
    uint16_t offline;            // 行偏移量
    uint32_t addr;               // 写入地址

    // 坐标系转换
    if(PIXELS_DIR)    // 横屏模式
    {
        psx=sx;psy=sy;
        pex=ex;pey=ey;
    }
    else            // 竖屏模式
    {
        psx=sy;psy=PIXELS_H-ex-1;
        pex=ey;pey=PIXELS_H-sx-1;
    }
    // 计算行偏移量
    offline=PIXELS_W-(pex-psx+1);
    // 计算起始地址
    addr=((uint32_t)&LTDC_Buffer[0]+2*(PIXELS_W*psy+psx));

    // 停止DMA2D
    DMA2D->CR&=~(DMA2D_CR_START);
    // 设置为存储器到存储器模式
    DMA2D->CR=DMA2D_M2M;
    // 设置颜色格式为RGB565
    DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;
    // 设置行偏移
    DMA2D->OOR=offline;

    // 设置输出存储器地址
    DMA2D->OMAR=addr;
    // 设置行数和像素数
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);
    // 设置前景图像地址
    DMA2D->FGMAR=(uint32_t)color;

//    DMA2D->CR |= DMA2D_IT_TC|DMA2D_IT_TE|DMA2D_IT_CE;  // 使能中断
    DMA2D->CR|=DMA2D_CR_START;  // 启动DMA2D

    // 等待传输完成
    while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)
    {
        timeout++;               // 超时计数
        if(timeout>0XFFFFFF)break; // 超时退出
    }
    DMA2D->IFCR|=DMA2D_FLAG_TC;  // 清除传输完成标志
}

/**
 * @brief  清屏函数
 * @param  color: 清屏颜色
 */
void LTDC_Clear(uint32_t color)
{
    LTDC_Fill(0,0,PIXELS_W-1,PIXELS_H-1,color);
}

/**
 * @brief  LCD背光打开函数
 */
void LTDC_ON(void)
{
    HAL_GPIO_WritePin(LCD_BL_GPIO_Port,LCD_BL_Pin,1);
}

/**
 * @brief  LCD背光关闭函数
 */
void LTDC_OFF(void)
{
    HAL_GPIO_WritePin(LCD_BL_GPIO_Port,LCD_BL_Pin,0);
}

/**
 * @brief  LTDC显示初始化函数
 */
void LTDC_Init(void)
{
    // 设置窗口位置
    HAL_LTDC_SetWindowPosition(&hltdc,0,0,0);
    // 设置窗口大小
    HAL_LTDC_SetWindowSize(&hltdc,PIXELS_W,PIXELS_H,0);
    // 使能DMA2D时钟
    __HAL_RCC_DMA2D_CLK_ENABLE();
    // 打开LCD背光
    LTDC_ON();
    // 清屏为白色
    LTDC_Clear(0XFFFFFFFF);
    return;
}

/* 测试代码（已注释）
uint16_t Buffer_test[500*500] __attribute__((section(".malloc")));
void LTDC_test()
{
    uint32_t i=0;
    for(i=0;i<500*500;i++)
    {
        Buffer_test[i]=BRED;
    }
    LTDC_Transmit(0,0,400,500,Buffer_test);
}
*/

/* USER CODE END 1 */
