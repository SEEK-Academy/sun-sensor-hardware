#pragma once
#include <cmath>

namespace math{
    struct Vector3 {
    float x, y, z;

    // Constructor
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Magnitude of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vector3 normalize() const {
        float mag = magnitude();
        if (mag == 0) return Vector3(0, 0, 0); // Avoid division by zero
        return Vector3(x / mag, y / mag, z / mag);
    }

    // Dot product
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Add two vectors
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Subtract two vectors
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Scalar division
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

};
}