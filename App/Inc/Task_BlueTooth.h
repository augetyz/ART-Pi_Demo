#ifndef TASK_BLUETOOTH_H
#define TASK_BLUETOOTH_H

#include "cybt_platform_config.h"

/* Default Baud rates */
#ifndef CYBT_BAUD_RATE_FOR_FW_DOWNLOAD
    #define CYBT_BAUD_RATE_FOR_FW_DOWNLOAD    (115200)
#endif
#ifndef CYBT_BAUD_RATE_FOR_FEATURE
    #define CYBT_BAUD_RATE_FOR_FEATURE        (115200)
#endif

extern const cybt_platform_config_t bt_platform_cfg_settings;

void BLE_App_Start(void);

#endif //TASK_BLUETOOTH_H
