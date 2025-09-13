#include "Task_Debug.h"
#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
extern osThreadId_t Debug_TaskHandle;


void DebugTask(void *argument)
{
    size_t total_heap_kb = 0;
    size_t free_heap_kb = 0;
    uint32_t stackFree = 0;
    uint8_t SDStatus=0;
    /* Infinite loop */
    for(;;)
    {
        total_heap_kb = configTOTAL_HEAP_SIZE / 1024;
        free_heap_kb = xPortGetFreeHeapSize() / 1024;
        stackFree = osThreadGetStackSpace(Debug_TaskHandle) / 1024;
        SDStatus = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5);
        printf("Debug_Task 剩余栈空间: %luKB\n", stackFree);
        printf("FreeRTOS   总堆大小：  %u KB\r\n", (unsigned int)total_heap_kb);
        printf("FreeRTOS   剩余堆大小: %u KB\r\n", (unsigned int)free_heap_kb);
        printf("SD卡检测状态: %s\r\n", SDStatus == GPIO_PIN_SET ? "未插入" : "已插入");

        LED_B_GPIO_Port->ODR ^= LED_B_Pin;
        osDelay(1000);
    }
}
