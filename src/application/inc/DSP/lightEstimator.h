#pragma once
#include <Eigen/Dense>
#include "math_functions/avg.h"

template <typename T, size_t S>
class LightEstimator
{
  public:
    static Eigen::AngleAxisf estimateRotationX(std::array<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitX());
    };
    static Eigen::AngleAxisf estimateRotationY(std::array<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitY());
    };
    static Eigen::AngleAxisf estimateRotationZ(std::array<T, S> measurements) {
        return estimateRotation(measurements, Eigen::Vector3f::UnitZ());
    };

  private:
    static Eigen::AngleAxisf estimateRotation(std::array<T, S> arg, Eigen::Vector3f axis)
    {
        return Eigen::AngleAxisf();
    }
};