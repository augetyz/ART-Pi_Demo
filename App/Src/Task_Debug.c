#include "Task_Debug.h"
#include "main.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "usb_device.h"
extern osThreadId_t Debug_TaskHandle;


void DebugTask(void *argument)
{

    MX_USB_DEVICE_Init();
    /* Infinite loop */
    for(;;)
    {
        size_t total_heap_kb = configTOTAL_HEAP_SIZE / 1024;
        size_t free_heap_kb = xPortGetFreeHeapSize() / 1024;
        uint32_t stackFree = osThreadGetStackSpace(Debug_TaskHandle) / 1024;
        my_printf("Debug_Task 剩余栈空间: %luKB\n", stackFree);
        osDelay(1);
        my_printf("FreeRTOS   总堆大小：  %u KB\r\n", (unsigned int)total_heap_kb);
        osDelay(1);
        my_printf("FreeRTOS   剩余堆大小: %u KB\r\n", (unsigned int)free_heap_kb);

        LED_B_GPIO_Port->ODR ^= LED_B_Pin;
        osDelay(1000);
    }
}
