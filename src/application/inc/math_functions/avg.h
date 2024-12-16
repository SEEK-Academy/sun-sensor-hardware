#include <cmath>
#include <span>

namespace math
{
    template <typename T, size_t S>
    T rootMeanSquare(const std::span<T, S> data)
    {
        int divider   = 0;
        T   aggregate = 0;

        for (auto elem : data)
        {
            aggregate += elem * elem;
            divider++;
        }
        if (divider != 0)
            aggregate /= divider;
        return std::sqrt(aggregate);
    }

    template <typename T, size_t S>
    T weightedRange(const std::span<T, S> data, const std::span<T, S> weights)
    {
        int divider   = 0;
        T   aggregate = 0;

        for (auto elem : data)
        {
            aggregate += elem * elem;
            divider++;
        }
        if (divider != 0)
            aggregate /= divider;
        return std::sqrt(aggregate);
    }

}  // namespace math