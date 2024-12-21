#include "stm32f411xe.h"
#include "peripherials/i2c.h"

namespace peripherials
{

    void I2C_1::init()
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;   // Enable I2C1 clock
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;  // Enable GPIOB clock

        // Configure PB6 (SCL) and PB7 (SDA) as alternate function open-drain
        GPIOB->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);     // Clear mode
        GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);  // Alternate function
        GPIOB->OTYPER |= (GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);       // Open-drain
        GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos) | (4 << GPIO_AFRL_AFSEL7_Pos);  // AF4 (I2C1)

        // Configure I2C1
        I2C1->CR1   = 0;          // Reset control register 1
        I2C1->CR2   = 50;         // Set peripheral clock frequency to 16 MHz
        I2C1->CCR   = 80;         // Set clock control register for 100 kHz (Standard Mode)
        I2C1->TRISE = 17;         // Maximum rise time
        I2C1->CR1 |= I2C_CR1_PE;  // Enable I2C1
        isInitialized = true;
    }

    void I2C_1::start(uint8_t address, uint8_t direction)
    {
        // Generate a START condition
        I2C1->CR1 |= I2C_CR1_START;
        while (!(I2C1->SR1 & I2C_SR1_SB))
            ;  // Wait for START condition generated

        // Send slave address with R/W bit
        I2C1->DR = address | direction;
        while (!(I2C1->SR1 & I2C_SR1_ADDR))
            ;             // Wait for address sent
        (void)I2C1->SR2;  // Clear ADDR flag by reading SR2
    }

    void I2C_1::stop()
    {
        // Generate a STOP condition
        I2C1->CR1 |= I2C_CR1_STOP;
    }

    I_I2C::I2C_Error_t I2C_1::sendData(std::vector<uint8_t> data){
            
    }

}  // namespace peripherials