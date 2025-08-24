cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	MBEDTLS_CONFIG_FILE=<mbedtls_config.h> 
	USE_PWR_LDO_SUPPLY 
	USE_HAL_DRIVER 
	STM32H750xx
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/MBEDTLS/App
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/include/mbedtls
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
	${CMAKE_SOURCE_DIR}/Drivers/CMSIS/RTOS2/Include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/inc/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/mqtt/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/include/mbedtls/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/mqtt/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/arpa
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/net
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/posix/sys
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/compat/stdc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/apps
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/priv
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/include/lwip/prot
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_43438/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include/COMPONENT_FREERTOS/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/hal/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/core-lib/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/COMPONENT_43438
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/debug/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack/wiced_include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack/wiced_include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/CMSIS_RTOS_V2/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/include/
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/include
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/portable/GCC/ARM_CM4F
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/firmware/COMPONENT_43438
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/clm/COMPONENT_43438
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/nvram/COMPONENT_43438
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/nvram/COMPONENT_43438/COMPONENT_AW-CU427-P
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/mqtt/include
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/platform/include/
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/source/include/
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/source/interface/
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/backoffAlgorithm/source/include/
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-port/include
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-port/source/include
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_SOURCE_DIR}/MBEDTLS/App/mbedtls.c
    ${CMAKE_SOURCE_DIR}/MBEDTLS/Target/custom_rng.c
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/Core/Src/gpio.c
    ${CMAKE_SOURCE_DIR}/Core/Src/memorymap.c
    ${CMAKE_SOURCE_DIR}/Core/Src/rng.c
    ${CMAKE_SOURCE_DIR}/Core/Src/sdmmc.c
    ${CMAKE_SOURCE_DIR}/Core/Src/usart.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_it.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_hal_msp.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_hal_timebase_tim.c
    ${CMAKE_SOURCE_DIR}/Core/Src/sysmem.c
    ${CMAKE_SOURCE_DIR}/Core/Src/syscalls.c
    ${CMAKE_SOURCE_DIR}/startup_stm32h750xx.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_SOURCE_DIR}/Core/Src/system_stm32h7xx.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rng_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mmc_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
)

# Drivers Midllewares


set(mbedTLS_Src
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/aes.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/aesni.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/arc4.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/asn1parse.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/asn1write.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/base64.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/bignum.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/blowfish.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/camellia.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ccm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/certs.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/chacha20.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/chachapoly.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/cipher.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/cipher_wrap.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ctr_drbg.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/des.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/dhm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ecdh.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ecdsa.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ecp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ecp_curves.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/entropy.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/entropy_poll.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/error.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/gcm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/hkdf.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/hmac_drbg.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/md.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/md5.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/md_wrap.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/memory_buffer_alloc.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/oid.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/padlock.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pem.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pk.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pkcs12.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pkcs5.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pkparse.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pkwrite.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/pk_wrap.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/platform.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/platform_util.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/poly1305.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ripemd160.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/rsa.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/rsa_internal.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/sha1.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/sha256.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/sha512.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/ssl_ciphersuites.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/version.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/version_features.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509write_crt.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509write_csr.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509_create.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509_crl.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509_crt.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/x509_csr.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/mbedTLS/library/xtea.c
)
set(Connectivity_Src
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/freertos/cybt_platform_freertos.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_hci_rx_task.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_hci_tx_task.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_host_stack_platform_interface.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_patchram_download.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_platform_main.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_platform_task.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_platform_trace.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/common/cybt_prm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/debug/cybt_debug_uart.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_helpers.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_rtos_freertos.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/COMPONENT_FREERTOS/cyabs_freertos_common.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/abstraction-rtos/source/cy_worker_thread.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack-integration/COMPONENT_HCI-UART/firmware/COMPONENT_43438/COMPONENT_AW-CU427-P/w_bt_firmware_controller.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/cyhal_system.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/common/Src/wifi_bt_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_gpio.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_lptimer.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_sdio.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_spi.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_trng.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_uart.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/pal/targets/TARGET_STM32/Src/stm32_cyhal_syspm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_lib.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/api_msg.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/err.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/if_api.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netbuf.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netdb.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/netifapi.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/sockets.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/api/tcpip.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_alloc.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/altcp_tcp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/def.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/dns.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/inet_chksum.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/init.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ip.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/autoip.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/dhcp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/etharp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/icmp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/igmp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_addr.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv4/ip4_frag.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/dhcp6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ethip6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/icmp6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/inet6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_addr.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/ip6_frag.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/mld6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/ipv6/nd6.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/mem.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/memp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/netif.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/pbuf.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/raw.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/stats.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/sys.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_in.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/tcp_out.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/timeouts.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/core/udp.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/LwIP/src/netif/ethernet.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/cybsp_wifi.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/whd-bsp-integration/COMPONENT_LWIP/cy_network_buffer_lwip.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aes.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aesni.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/arc4.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/aria.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/asn1parse.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/asn1write.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/base64.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/bignum.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/blowfish.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/camellia.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ccm.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/certs.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/chacha20.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/chachapoly.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cipher.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cipher_wrap.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/cmac.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ctr_drbg.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/debug.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/des.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/dhm.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecdh.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecdsa.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecjpake.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecp.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ecp_curves.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/entropy.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/entropy_poll.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/error.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/gcm.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/havege.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/hkdf.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/hmac_drbg.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md2.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md4.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/md5.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/memory_buffer_alloc.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/net_sockets.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/nist_kw.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/oid.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/padlock.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pem.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pk.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs11.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs12.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkcs5.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkparse.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pkwrite.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/pk_wrap.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/platform.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/platform_util.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/poly1305.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_driver_wrappers.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_se.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_slot_management.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_crypto_storage.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/psa_its_file.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ripemd160.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/rsa.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/rsa_internal.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha1.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha256.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/sha512.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cache.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_ciphersuites.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cli.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_cookie.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_msg.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_srv.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_ticket.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_tls.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/ssl_tls13_keys.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/threading.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/timing.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/version.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/version_features.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509write_crt.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509write_csr.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_create.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_crl.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_crt.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/x509_csr.c
#    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/ARM/mbedtls/library/xtea.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_log/cy_log.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/JSON_parser/cy_json_parser.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/linked_list/cy_linked_list.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/cy_string/cy_string_utils.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/cy_nw_helper_common.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/connectivity-utilities/network/COMPONENT_LWIP/cy_nw_helper.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-connection-manager/source/cy_wcm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_common.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_sdio_protocol.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_spi_protocol.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_emusbh_impl.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/bus_protocols/whd_bus_usb_protocol.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_ap.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_buffer_api.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_cdc_bdc.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_chip.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_chip_constants.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_clm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_debug.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_events.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_logging.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_management.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_network_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_proto.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_resource_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_sdpcm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_thread.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_utils.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi_api.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_wifi_p2p.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_commonring.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_flowring.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/src/whd_ring.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/wifi-host-driver/COMPONENT_WIFI5/resources/resource_imp/whd_resources.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/mqtt/source/cy_mqtt_api.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/cy_tls_weak.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/cy_pkcs_psa_logging.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_LWIP/cy_secure_sockets.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_MBEDTLS/iot_crypto.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/secure-sockets/source/COMPONENT_MBEDTLS/cy_tls.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_ethernetif.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_lwip_dhcp_server.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-network-interface-integration/source/cy_network_mw_core.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/lwip-freertos-integration/arch/sys_arch.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/source/core_mqtt.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/source/core_mqtt_state.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-embedded-C/libraries/standard/coreMQTT/source/core_mqtt_serializer.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-port/source/cy_aws_clock.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-port/source/cy_aws_retry_utils.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/aws-iot-device-sdk-port/source/COMPONENT_SECURE_SOCKETS/cy_aws_tcpip_port_secure_sockets.c
)
set(Middleware_Src
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/list.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/queue.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/tasks.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/croutine.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/event_groups.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/stream_buffer.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/timers.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_RTOS_Middleware/FreeRTOS/Source/portable/MemMang/heap_4.c
)

# Link directories setup
set(MX_LINK_DIRS

    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/Infineon_Wireless_Connectivity/btstack/stack/COMPONENT_WICED_BLE/COMPONENT_CM7/COMPONENT_SOFTFP/TOOLCHAIN_GCC_ARM
)
# Project static libraries
set(MX_LINK_LIBS  
	:libbtstack.a
    STM32_Drivers
    mbedTLS
	Connectivity
	Middleware
	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create mbedTLS static library
add_library(mbedTLS OBJECT)
target_sources(mbedTLS PRIVATE ${mbedTLS_Src})
target_link_libraries(mbedTLS PUBLIC stm32cubemx)

# Create Connectivity static library
add_library(Connectivity OBJECT)
target_sources(Connectivity PRIVATE ${Connectivity_Src})
target_link_libraries(Connectivity PUBLIC stm32cubemx)

# Create Middleware static library
add_library(Middleware OBJECT)
target_sources(Middleware PRIVATE ${Middleware_Src})
target_link_libraries(Middleware PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
