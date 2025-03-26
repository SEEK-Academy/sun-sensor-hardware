#include "usb.h"
#include "usbd_cdc_if_template.h"

// USBD_HandleTypeDef             hUsbDeviceFS;
// extern USBD_DescriptorsTypeDef CDC_Desc;

namespace peripherals
{
    USB::USB()
    {
        // USBD_Init(&hUsbDeviceFS, &CDC_Desc, DEVICE_FS);
        // USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);
        // USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
        // USBD_Start(&hUsbDeviceFS);
    }

    void USB::writeData(const std::vector<char>& data)
    {
        if (!data.empty())
        {
            CDC_Transmit_FS((uint8_t*)data.data(), data.size());
        }
    }
}  // namespace peripherals