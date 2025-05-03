# SunSensor

Open-source project for determing the spatial orientation relative to a light source (e.g., the Sun) and is housed in a 3D-printed CubeSat format (U1 standard).

## Project Structure

The SunSensor project is organized into two GitHub repositories, each responsible for specific functional modules:

* sun-sensor-hardware:

  * **Mechanics** – Design and 3D printing of the CubeSat structure.
  * **Electronics** – Selection and integration of electronic components.
  * **Firmware** – Low-level software responsible for hardware communication and orientation calculations based on light-source input.

* [`sun-sensor-software`](https://github.com/SEEK-Academy/sun-sensor-software):

  * **Software** – A real-time 3D simulation of the SunSensor device and the light source.

## sun-sensor-hardware

This repository includes 3D models, schematics, and firmware for the SunSensor device. It focuses on integrating hardware and performing onboard orientation calculations using sensor data.

### Key Features

* **Mechanical Prototyping**: Includes complete 3D models of CubeSat components developed through iterative prototyping. See [3D Models Documentation](/doc/3D_models/README.md).
* **Electronic Integration**: Provides circuit diagram and  reading of sensor data from onboard components. See [circuit diagram](/doc/components/sch-sunsensor-v2.pdf).
* **Onboard Calculation**: Uses sensor input and embedded algorithms to calculate the CubeSat’s spatial orientation in real time.
* **USB Communication**: Transmits computed orientation data to external system.

### Technology Stack

- **Build System**: CMake
- **Compiler Toolchain**: ARM GCC (arm-gcc-none-eabi)
- **Development Tools**: Make

## How to use

Create `build` directory.
Enter it.
Run `cmake ..` and `make -j`.

### Useful docs

#### STM32 F401 Series

* [STM32G4 REFERENCE MANUAL](https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

