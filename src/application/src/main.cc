#include "main.h"
#include "peripherials/usart.h"
#include "peripherials/i2c.h"
#include "stm32f4xx.h"
#include "usbd_cdc_if_template.h"
#include <cstdint>
#include <vector>
#include "usb.h"
#include <math.h>

#define PLL_Q 4U
#define PLL_M 25U
#define PLL_N 192U
#define PLL_P 2U

volatile uint32_t ticks;

extern "C" void SysTick_Handler()
{
    HAL_IncTick();
    ticks++;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
extern "C" void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

void ClockInit()
{
    HAL_Init();
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM       = 25;
    RCC_OscInitStruct.PLL.PLLN       = 192;
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ       = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;  // GPIO ON
    RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;  // Enable USB OTG FS clock

    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    SysTick_Config(96000);
    __enable_irq();
}

void delay_ms(uint32_t milliseconds)
{
    uint32_t start = ticks;
    uint32_t end   = start + milliseconds;

    if (end < start)  // handle overflow
    {
        while (ticks > start)
        {
            ;
        }  // wait for ticks to wrap around to zero
    }

    while (ticks < end)
    {
        ;
    }
}

USBD_HandleTypeDef             hUsbDeviceFS;
extern USBD_DescriptorsTypeDef CDC_Desc;

uint8_t get_command_byte(int channel)
{
    // Channel mapping for single-ended mode
    // A0 = 0b000, A1 = 0b100, A2 = 0b001, A3 = 0b101, etc.
    uint8_t channel_map[8] = {
        0b000,  // A0
        0b100,  // A1
        0b001,  // A2
        0b101,  // A3
        0b010,  // A4
        0b110,  // A5
        0b011,  // A6
        0b111   // A7
    };

    // Create command byte (Single-ended, channel selection, bit 3=1)
    return (1 << 7) | (channel_map[channel] << 4) | (1 << 3);
}

float weightedMean(float X[], float W[], int n)
{
    float sum = 0.0f, numWeight = 0.0f;

    for (int i = 0; i < n; i++)
    {
        numWeight += X[i] * W[i];
        sum += W[i];
    }

    // Add debug print
    char buffer[64];
    snprintf(
        buffer, sizeof(buffer), "WeightedMean - sum: %.2f, numWeight: %.2f\r\n", sum, numWeight);
    // Note: We can't use USB here directly, so this debug might need to move

    return (sum > 0.0f) ? (numWeight / sum) : 0.0f;
}

float calculateAngle(float xc)
{
    const float xcenter = 15.0f;
    const float height  = 50.0f;

    float angle = atan((xc - xcenter) / height) * (180.0f / M_PI);

    // Add bounds check
    if (isnan(angle))
    {
        return 0.0f;
    }

    return angle;
}

extern "C" int main(void)
{
    ClockInit();

    GPIOC->MODER |= (1 << GPIO_MODER_MODER13_Pos);

    if (USBD_Init(&hUsbDeviceFS, &CDC_Desc, DEVICE_FS) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
    {
        Error_Handler();
    }
    if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
    {
        Error_Handler();
    }

    // Wait for USB enumeration (host needs time to recognize device)
    HAL_Delay(2000);

    peripherals::USB   usb = peripherals::USB();
    peripherals::I2C_1 i2c;

    // Send startup message to confirm USB is working
    const char* startMsg = "Sun Sensor Started\r\n";
    std::vector<char> startData(startMsg, startMsg + strlen(startMsg));
    usb.writeData(startData);

    // Send USB initialization message first
    // char usbMsg[32];
    // snprintf(usbMsg, sizeof(usbMsg), "USB Init Complete!\r\n");
    // std::vector<char> usbData(usbMsg, usbMsg + strlen(usbMsg));
    // usb.writeData(usbData);

    i2c.init();
    i2c.setAddress(0x48);
    uint8_t adcValue = 0;

    // Then send I2C init message
    // char initMsg[32];
    // snprintf(initMsg, sizeof(initMsg), "I2C Init Complete\r\n");
    // std::vector<char> initData(initMsg, initMsg + strlen(initMsg));
    // usb.writeData(initData);

    //  uint8_t resistorName = 7;
    uint8_t resistorName = 0;

    uint8_t controlByte = get_command_byte(resistorName);

    // Initialize arrays with explicit values
    float intensities[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float weights[4]     = {0.0f, 10.0f, 20.0f, 30.0f};  // Make sure these are float literals

    // Calibration variables - OUTSIDE the loop
    float          calibrationMin[4]       = {255.0f, 255.0f, 255.0f, 255.0f};
    float          calibrationMax[4]       = {0.0f, 0.0f, 0.0f, 0.0f};
    bool           isCalibrating           = true;
    uint32_t       calibrationStartTime    = 0;
    const uint32_t CALIBRATION_DURATION_MS = 5000;  // 5 seconds calibration

    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_OD13;

        controlByte = get_command_byte(resistorName);

        i2c.readRegister(controlByte, adcValue);

        if (isCalibrating)
        {
            if (calibrationStartTime == 0)
            {
                calibrationStartTime = HAL_GetTick();
            }

            // Update min/max during calibration
            calibrationMin[resistorName] =
                std::min(calibrationMin[resistorName], static_cast<float>(adcValue));
            calibrationMax[resistorName] =
                std::max(calibrationMax[resistorName], static_cast<float>(adcValue));

            if (HAL_GetTick() - calibrationStartTime > CALIBRATION_DURATION_MS)
            {
                isCalibrating = false;
            }

            // Skip normal processing during calibration
            continue;
        }

        // Replace line 228 with calibrated reading:
        float normalized = (static_cast<float>(adcValue) - calibrationMin[resistorName]) /
                           (calibrationMax[resistorName] - calibrationMin[resistorName]);
        intensities[resistorName] = std::max(0.0f, std::min(1.0f, normalized));

        // if(resistorName == 4) {
        //     resistorName = 7;
        // } else {
        //     resistorName--;
        // }

        // snprintf(buffer, sizeof(buffer), "Storing intensity[%d] = %.1f\r\n",
        //         resistorName, intensities[resistorName]);
        // std::vector<char> debugData(buffer, buffer + strlen(buffer));
        // usb.writeData(debugData);

        HAL_Delay(500);

        if (resistorName == 3)
        {
            resistorName = 0;
            char buffer[64];

            // Print all intensities in one line
            snprintf(buffer,
                     sizeof(buffer),
                     "Intensities: %d | %d | %d | %d\r\n",
                     (int)intensities[0],
                     (int)intensities[1],
                     (int)intensities[2],
                     (int)intensities[3]);
            std::vector<char> debugArray(buffer, buffer + strlen(buffer));
            usb.writeData(debugArray);

            // Calculate weighted mean with integer debug prints
            float numWeight  = 0.0f;
            float sumWeights = 0.0f;
            for (int i = 0; i < 4; i++)
            {
                numWeight += intensities[i] * weights[i];
                sumWeights += weights[i];
            }
            float x = (sumWeights > 0.0f) ? (numWeight / sumWeights) : 0.0f;

            float angle = calculateAngle(x);

            // Final results with integer casting for x
            snprintf(buffer, sizeof(buffer), "Final - X: %d, Angle: %d\r\n", (int)x, (int)angle);
            std::vector<char> resultData(buffer, buffer + strlen(buffer));
            usb.writeData(resultData);
        }
        else
        {
            resistorName++;
        }
    }
}
