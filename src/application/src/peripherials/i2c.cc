#include "stm32f4xx_hal.h"
#include "peripherials/i2c.h"

namespace peripherals
{
    I2C_HandleTypeDef hi2c1;

    I_I2C::I2C_Error_t I2C_1::readRegister(uint8_t reg, uint8_t& data)
    {
        HAL_StatusTypeDef status =
            HAL_I2C_Mem_Read(&hi2c1, address << 1, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
        return (status == HAL_OK) ? I_I2C::I2C_Error_t::OK : I_I2C::I2C_Error_t::ERROR;
    }

    void I2C_1::init()
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        // Enable peripherals clocks
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_I2C1_CLK_ENABLE();

        // Configure GPIO pins
        GPIO_InitStruct.Pin       = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull      = GPIO_PULLUP;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        // Configure I2C
        hi2c1.Instance             = I2C1;
        hi2c1.Init.ClockSpeed      = 100000;  // 100 KHz
        hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
        hi2c1.Init.OwnAddress1     = 0;
        hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
        hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
        hi2c1.Init.OwnAddress2     = 0;
        hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
        hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

        if (HAL_I2C_Init(&hi2c1) == HAL_OK)
        {
            isInitialized = true;
        }
    }

    I_I2C::I2C_Error_t I2C_1::sendData(std::vector<uint8_t> data)
    {
        if (!data.empty())
        {
            HAL_StatusTypeDef status =
                HAL_I2C_Master_Transmit(&hi2c1, address << 1, data.data(), data.size(), 100);
            return (status == HAL_OK) ? I_I2C::I2C_Error_t::OK : I_I2C::I2C_Error_t::ERROR;
        }
        return I_I2C::I2C_Error_t::ERROR;
    }

    I_I2C::I2C_Error_t I2C_1::readData(std::vector<uint8_t>& data)
    {
        if (!data.empty())
        {
            HAL_StatusTypeDef status =
                HAL_I2C_Master_Receive(&hi2c1, address << 1, data.data(), data.size(), 100);
            return (status == HAL_OK) ? I_I2C::I2C_Error_t::OK : I_I2C::I2C_Error_t::ERROR;
        }
        return I_I2C::I2C_Error_t::ERROR;
    }

    void I2C_1::setAddress(uint8_t newAddress)
    {
        address = newAddress;
    }
}  // namespace peripherals