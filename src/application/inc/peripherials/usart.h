#pragma once
#include <vector>
#include <cstdint>

namespace peripherals
{
    constexpr uint32_t sysClock = 100'000'000;

    class I_USART
    {
      public:
        enum class USART_Error_t : uint8_t
        {
            OK         = 0,
            MISC_ERROR = (1 << 1)
        };

        bool isInitialized = false;

        virtual void          init(uint32_t baudrate)             = 0;
        virtual USART_Error_t sendData(std::vector<uint8_t> data) = 0;
    };

    class Usart2 : I_USART
    {
      public:
        void          init(uint32_t baudrate) override;
        USART_Error_t sendData(std::vector<uint8_t> data) override;
    };
}  // namespace peripherals