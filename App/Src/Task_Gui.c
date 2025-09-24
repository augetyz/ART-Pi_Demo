#include "Task_Gui.h"
#include "cmsis_os2.h"
#include "main.h"
#include "gt911.h"
#include "ltdc.h"
void GuiTask(void *argument)
{
    Touch_Point stTouchData={0};
    LTDC_Init();
    LTDC_Clear(WHITE);
    Touch_Init();
    uint32_t TimeStamp = DWT->CYCCNT;
    Touch_scan(&stTouchData);
    /* Infinite loop */
    for(;;)
    {
        TimeStamp = DWT->CYCCNT;
        Touch_scan(&stTouchData);
        // printf("TimeStamp:%f\n\n",(float)((DWT->CYCCNT - TimeStamp) / (SystemCoreClock / 1000000)));
        printf("Touch1_X=%d,Touch1_Y=%d\n",stTouchData.Coord_X[0],stTouchData.Coord_Y[0]);
        osDelay(1);
    }
}


