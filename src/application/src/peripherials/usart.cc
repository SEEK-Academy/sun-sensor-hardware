#include "stm32f4xx.h"
#include "peripherials/usart.h"
#include <vector>
#include <cstdint>

namespace peripherals
{

    void Usart2::init(uint32_t baudrate)
    {
        // Enable the clock for GPIOA and USART2
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // Enable GPIOA clock
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // Enable USART2 clock

        // Configure PA2 (USART2_TX) and PA3 (USART2_RX) as alternate functions
        GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3);     // Clear mode
        GPIOA->MODER |= (GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1);  // Set alternate function mode

        GPIOA->AFR[0] |= (0x07 << GPIO_AFRL_AFSEL2_Pos) |
                         (0x07 << GPIO_AFRL_AFSEL3_Pos);  // Set AF7 (USART2) for PA2 and PA3

        // Configure USART2
        USART2->CR1 = 0;                             // Reset control register 1
        USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;  // Enable Transmitter and Receiver
        USART2->CR1 &= ~USART_CR1_OVER8;             // Set 16x oversampling

        USART2->CR2 = 0;                 // Reset control register 2
        USART2->CR2 &= ~USART_CR2_STOP;  // Set 1 stop bit

        USART2->BRR = sysClock / 4 / baudrate;  // Set baud rate (Assume 100 MHz system clock)

        USART2->CR1 |= USART_CR1_UE;  // Enable USART2

        isInitialized = true;
    }

    I_USART::USART_Error_t Usart2::sendData(std::vector<uint8_t> data)
    {
        for (uint8_t byte : data)
        {
            while (!(USART2->SR & USART_SR_TXE))
                ;            
            USART2->DR = byte;  
        }

        return USART_Error_t::OK;
    }

}  // namespace peripherials
