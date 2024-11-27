#pragma once

#include <span>

#include <Eigen/Dense>
#include "math_functions/avg.h"

class LightEstimator
{
  public:
    template <typename T, size_t S>
    static Eigen::AngleAxisf estimateRotationX(std::span<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitX());
    };

    template <typename T, size_t S>
    static Eigen::AngleAxisf estimateRotationY(std::span<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitY());
    };

    template <typename T, size_t S>
    static Eigen::AngleAxisf estimateRotationZ(std::span<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitZ());
    };

  private:
    template <typename T, size_t S>
    static Eigen::AngleAxisf estimateRotation(std::span<T, S> arg, Eigen::Vector3f axis)
    {
        return Eigen::AngleAxisf();
    }
};