#pragma once

#include <vector>

namespace peripherals
{
    /// @brief USB-CDC singleton
    class USB
    {
      public:
        USB();
        void writeData(const std::vector<char>& data);
    };
}  // namespace peripherals