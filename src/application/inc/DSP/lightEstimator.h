#pragma once

#include <span>

#include "math_functions/avg.h"
#include "datatypes.h"

class LightEstimator
{
  public:
    template <typename T, size_t S>
    static math::Vector3 estimateRotationX(std::span<T, S> measurements)
    {
        return estimateRotation(measurements, math::Vector3(1.0, 0.0, 0.0));
    };

    template <typename T, size_t S>
    static math::Vector3 estimateRotationY(std::span<T, S> measurements)
    {
        return estimateRotation(measurements, math::Vector3(0.0, 1.0, 0.0));
    };

    template <typename T, size_t S>
    static math::Vector3 estimateRotationZ(std::span<T, S> measurements)
    {
        return estimateRotation(measurements, math::Vector3(0.0, 0.0, 1.0));
    };

  private:
    template <typename T, size_t S>
    static math::Vector3 estimateRotation(std::span<T, S> arg, math::Vector3 axis)
    {
        return math::Vector3(0.0f, 0.0f, 0.0f);
    }
};