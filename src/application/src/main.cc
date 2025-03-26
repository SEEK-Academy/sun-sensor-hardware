#include "main.h"
#include "peripherials/usart.h"
#include "stm32f4xx.h"
#include "usbd_cdc_if_template.h"
#include <cstdint>
#include <vector>

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

peripherials::Usart2           usart2;
USBD_HandleTypeDef             hUsbDeviceFS;
extern USBD_DescriptorsTypeDef CDC_Desc;

extern "C" int main(void)
{
    // __HAL_DBGMCU_FREEZE_IWDG();
    // __HAL_DBGMCU_FREEZE_WWDG();
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

    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_OD13;
        HAL_Delay(500);
    }
}
