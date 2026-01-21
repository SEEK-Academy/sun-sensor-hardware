#ifndef PERIPHERALS_COMMON_H
#define PERIPHERALS_COMMON_H

#include <cstdint>

namespace peripherals
{
    constexpr uint32_t sysClock = 96'000'000;  // 25MHz HSE * 192 / 25 / 2 = 96MHz
}

#endif  // PERIPHERALS_COMMON_H