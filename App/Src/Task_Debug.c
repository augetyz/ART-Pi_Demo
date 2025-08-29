#include "Task_Debug.h"
#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
extern osThreadId_t Debug_TaskHandle;
extern osThreadId_t WiFi_TaskHandle;
void DebugTask(void *argument)
{
    /* Infinite loop */
    for(;;)
    {

        // size_t total_heap_kb = configTOTAL_HEAP_SIZE / 1024;
        // size_t free_heap_kb = xPortGetFreeHeapSize() / 1024;
        // size_t All_heap_kb = get_free_heap_size() / 1024;
        // uint32_t stackFree = osThreadGetStackSpace(WiFi_TaskHandle) / 1024;
        // printf("WiFi_Task  剩余栈空间: %luKB\n", stackFree);
        // stackFree = osThreadGetStackSpace(Debug_TaskHandle) / 1024;
        // printf("Debug_Task 剩余栈空间: %luKB\n", stackFree);
        // printf("FreeRTOS   总堆大小：  %u KB\r\n", (unsigned int)total_heap_kb);
        // printf("FreeRTOS   剩余堆大小: %u KB\r\n", (unsigned int)free_heap_kb);
        // printf("MCU        所有堆大小: %u KB\r\n", (unsigned int)All_heap_kb);

        LED_B_GPIO_Port->ODR ^= LED_B_Pin;
        osDelay(1000);
    }
}
