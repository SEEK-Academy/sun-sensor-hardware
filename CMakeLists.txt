cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project (sun-sensor-firmware LANGUAGES C CXX ASM)
set(CMAKE_CXX_STANDARD 20)

if(NOT TEST)
    set(MEMORY_LEAK_DETECTION OFF)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-arm-none-eabi.cmake)
endif()


add_subdirectory(third_party)

find_package(Eigen3 REQUIRED)

add_subdirectory(src)

