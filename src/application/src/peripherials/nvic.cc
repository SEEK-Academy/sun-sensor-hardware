#include "nvic.h"
#include "stm32f4xx_hal.h"

extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

extern "C" void OTG_FS_IRQHandler(void) {
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS); // For USB Device Mode
}

