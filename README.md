# 移植英飞凌WHD驱动到FreeRtos (适配STM32H750+CYW43438)
## 介绍
本项目旨在将Infinite的WHD驱动移植到FreeRTOS操作系统上

适配STM32H750微控制器和CYW43438无线模块即AP6212。

WHD（Wireless Host Driver）是英飞凌提供的用于其无线芯片的WiFi蓝牙驱动.

项目使用CubeMX初始化,移植过程中很多代码已由Infinite适配,仅修改部分参数和bug以驱动CYW43438.

wifi和蓝牙功能均可正常使用,但蓝牙可以识别，无法连接，是我代码拉了，后续会继续调试。

## BugList

### 1. **MX_SDMMC2_MMC_Init()函数**
WHD驱动中会初始化用户传入的SDMMC外设,但是不会初始化IO引脚,因此需要开始初始化SDMMC外设. 
而CubeMX生成的SDMMC初始化代码会使用SDIO总线发送命令给设备,但CYW43438设备不符合常规的SDIO协议,不会有回应,会导致HAL的SDMMC外设初始化失败,因此需要修改初始化函数以适应CYW43438的要求.
 
```c++
/* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
    HAL_MMC_MspInit(hmmc);
    #endif /* USE_HAL_MMC_REGISTER_CALLBACKS */
    }
    return HAL_OK;//直接返回,初始化时钟和IO即可
    hmmc->State = HAL_MMC_STATE_BUSY;

    /* Initialize the Card parameters */
    if (HAL_MMC_InitCard(hmmc) == HAL_ERROR)
    {
    return HAL_ERROR;
    }
```
### 2. **主机唤醒中断优先级过高**  
WHD驱动中传入GPIO后,会自动初始化IO中断,并配置回调函数指针;
但是默认优先级为0,会导致中断中执行的WHD回调的Rtos函数无法正常运行,在vPortValidateInterruptPriority函数中断言失败,进入死循环.

```c++
/* Enable/Disable IRQ */
 if (en_irq)
 {
     /* Use the priority, configured by STM32CubeMx if CYHAL_GPIO_USE_HAL_IRQ_PRIOPITY
      * has not been defined */
     #if defined(CYHAL_GPIO_USE_HAL_IRQ_PRIOPITY)
     HAL_NVIC_SetPriority(IRQn, priority, 0);//默认不启用,导致优先级设置为0
     #endif /* defined(CYHAL_GPIO_USE_HAL_IRQ_PRIOPITY) */
     HAL_NVIC_SetPriority(IRQn, 5, 0);
     HAL_NVIC_EnableIRQ(IRQn);
 }
```
### 3. **WHD蓝牙驱动程序优先级过高**
WHD蓝牙程序中调用的串口、外部中断，同样存在优先级过高的问题，导致在中断中调用RTOS函数时出现问题。
需要将这些外设的中断优先级设置为较低的值（如5），以确保它们不会干扰RTOS的正常运行。
```c++
if (enable)
{
    /* Use the priority, configured by STM32CubeMx if CYHAL_UART_USE_HAL_IRQ_PRIOPITY
     * has not been defined */
    #if defined(CYHAL_UART_USE_HAL_IRQ_PRIOPITY)
    HAL_NVIC_SetPriority(IRQn, priority, 0);
    #endif /* defined(CYHAL_UART_USE_HAL_IRQ_PRIOPITY) */
    HAL_NVIC_SetPriority(IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(IRQn);
}
```


