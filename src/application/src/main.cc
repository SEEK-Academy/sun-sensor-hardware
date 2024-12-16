#include "main.h"
#include "stm32f401xc.h"

#define LED_PIN 5

uint32_t ticks;

void systick_handler()
{
    ticks++;
}

void ClockInit()
{
    RCC->CR |= RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk;
    while (!(RCC->CR & RCC_CR_HSERDY_Msk))
        ;
    RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;
    volatile uint32_t dummy;
    dummy = RCC->APB1ENR;
    dummy = RCC->APB1ENR;
    PWR->CR |= (0b11 << PWR_CR_VOS_Pos);
    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
    // Clear PLLM, PLLN and PLLP bits
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk);

    // Set PLLM, PLLN and PLLP, and select HSE as PLL source
    RCC->PLLCFGR |= ((4 << RCC_PLLCFGR_PLLM_Pos) | (200 << RCC_PLLCFGR_PLLN_Pos) |
                     (1 << RCC_PLLCFGR_PLLP_Pos) | (1 << RCC_PLLCFGR_PLLSRC_Pos));

    // Set APB1 prescaler to 2
    RCC->CFGR |= (0b100 << RCC_CFGR_PPRE1_Pos);

    // Enable PLL and wait for ready
    RCC->CR |= RCC_CR_PLLON_Msk;
    while (!(RCC->CR & RCC_CR_PLLRDY_Msk))
        ;

    // Select PLL output as system clock
    RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
        ;

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
            ;  // wait for ticks to wrap around to zero
    }

    while (ticks < end)
        ;
}

int main(void)
{
    ClockInit();

    GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos);

    while (1)
    {
        GPIOA->ODR ^= (1 << LED_PIN);
        delay_ms(500);
    }
}