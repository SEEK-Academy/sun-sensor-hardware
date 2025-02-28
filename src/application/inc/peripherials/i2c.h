#pragma once
#include <vector>
#include <cstdint>

namespace peripherials
{
    constexpr uint32_t sysClock = 100'000'000;

    class I_I2C
    {
      public:
        enum class I2C_Error_t : uint8_t
        {
            OK         = 0,
            MISC_ERROR = (1 << 1)
        };

        bool isInitialized = false;

        virtual void        init()                                                 = 0;
        virtual void        start(uint8_t address, uint8_t direction)              = 0;
        virtual I2C_Error_t sendData(std::vector<uint8_t> data)                    = 0;
        virtual std::pair<std::vector<uint8_t>, I2C_Error_t> recieveData(bool ack) = 0;
        virtual void                                         stop()                = 0;

      protected:
        bool isStarted = false;
    };

    class I2C_1 : I_I2C
    {
      public:
        void        init() override;
        void        start(uint8_t address, uint8_t direction) override;
        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        std::pair<std::vector<uint8_t>, I2C_Error_t> recieveData(bool ack) override;
        void                                         stop() override;
    };

    class I2C_2 : I_I2C
    {
      public:
        void        init() override;
        void        start(uint8_t address, uint8_t direction) override;
        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        std::pair<std::vector<uint8_t>, I2C_Error_t> recieveData(bool ack) override;
        void                                         stop() override;
    };

    class I2C_3 : I_I2C
    {
      public:
        void        init() override;
        void        start(uint8_t address, uint8_t direction) override;
        I2C_Error_t sendData(std::vector<uint8_t> data) override;
        std::pair<std::vector<uint8_t>, I2C_Error_t> recieveData(bool ack) override;
        void                                         stop() override;
    };
}  // namespace peripherials