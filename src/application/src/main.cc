#include "main.h"
#include "stm32f401xc.h"
#include "peripherials/usart.h"
#include <cstdint>
#include <vector>

#define PLL_Q 4U
#define PLL_M 12U
#define PLL_N 192U
#define PLL_P 4U

volatile uint32_t ticks;

extern "C" void SysTick_Handler()
{
    ticks++;
}

void ClockInit()
{
    // BlackPill has 25Mhz HSE clock

    RCC->CR |= RCC_CR_HSEON;
    // RCC->CR |= RCC_CR_HSEON;  // Turn on HSE
    while (!(RCC->CR & RCC_CR_HSERDY))
    {
        // wait for stable clock
    }

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
    FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_3WS;

    RCC->PLLCFGR |= (PLL_Q << RCC_PLLCFGR_PLLQ_Pos) | (PLL_P << RCC_PLLCFGR_PLLP_Pos) |
                    (PLL_N << RCC_PLLCFGR_PLLN_Pos) | (PLL_M << RCC_PLLCFGR_PLLM_Pos) |
                    RCC_PLLCFGR_PLLSRC_HSE;
    RCC->CR |= RCC_CR_PLLON;

    while (!(RCC->CR & RCC_CR_PLLRDY))
    {
        // wait for stable PLL
    }

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;   // AHB Prescaler: No division (100 MHz)
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;  // APB1 Prescaler: Divide by 4 (100 MHz / 4 = 25 MHz)
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;  // APB2 Prescaler: Divide by 2 (100 MHz / 2 = 50 MHz)

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
    {
        // Wait until PLL is used as the system clock source
    }
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;  // GPIO ON

    SysTick_Config(100000);
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


peripherials::Usart2 usart2;

extern "C" int main(void)
{
    ClockInit();

    GPIOC->MODER |= (1 << GPIO_MODER_MODER13_Pos);

    std::vector<uint8_t> example_data = {'d','a','t','a','\n'};

    constexpr uint32_t baudrate = 115200U;
    usart2.init(baudrate);

    while (1)
    {
        GPIOC->ODR ^= GPIO_ODR_OD13;
        usart2.sendData(example_data);
        delay_ms(500);
    }
}
