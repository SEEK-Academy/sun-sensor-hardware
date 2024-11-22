cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project (sun-sensor-firmware LANGUAGES C CXX ASM)

if(NOT TEST)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-arm-none-eabi.cmake)
endif()


add_subdirectory(third_party)
add_subdirectory(src)

