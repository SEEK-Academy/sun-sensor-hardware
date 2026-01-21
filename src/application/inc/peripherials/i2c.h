#pragma once
#include <vector>
#include <cstdint>
#include "peripherials/peripherals_common.h"  // Include for sysClock

namespace peripherals
{
    class I_I2C
    {
      public:
        enum class I2C_Error_t : uint8_t
        {
            OK         = 0,
            ERROR      = 1,
            MISC_ERROR = (1 << 1)
        };

        bool isInitialized = false;

        virtual void        init()                               = 0;
        virtual I2C_Error_t sendData(std::vector<uint8_t> data)  = 0;
        virtual I2C_Error_t readData(std::vector<uint8_t>& data) = 0;

      protected:
        bool isStarted = false;
    };

    class I2C_1 : I_I2C
    {
      private:
        uint8_t address = 0;

      public:
        void init() override;

        I_I2C::I2C_Error_t readRegister(uint8_t reg, uint8_t& data);

        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        I2C_Error_t readData(std::vector<uint8_t>& data) override;

        void setAddress(uint8_t addr);
    };

    class I2C_2 : I_I2C
    {
      public:
        void        init() override;
        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        I2C_Error_t readData(std::vector<uint8_t>& data) override;
    };

    class I2C_3 : I_I2C
    {
      public:
        void        init() override;
        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        I2C_Error_t readData(std::vector<uint8_t>& data) override;
    };
}  // namespace peripherals