# sun-sensor-hardware
WIP

# Dependencies

Make, CMake, arm-gcc-none-eabi toolchain

# How to use

Create `build` directory.
Enter it.
Run `cmake ..` and `make -j`.

# Macos

```
cmake -DCMAKE_C_COMPILER=/opt/homebrew/bin/arm-none-eabi-gcc \
      -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/arm-none-eabi-g++ \
      -DCMAKE_ASM_COMPILER=/opt/homebrew/bin/arm-none-eabi-gcc \
      ..
make -j
```

# Flashing

After building, flash the firmware to the STM32 device:

```bash
cd build/src
st-flash write sun-sensor-firmware.bin 0x08000000
```

## Troubleshooting

If you encounter connection errors like "NRST is not connected" or "Failed to enter SWD mode":

### ST-Link detected but target not found (chipid: 0x000)

If `st-info --probe` shows the ST-Link programmer but `chipid: 0x000` and `dev-type: unknown`:

1. **Verify power**: Ensure the target board is powered (3.3V or 5V depending on board)
2. **Check SWD connections**:
   - **SWDIO** (SWD Data I/O) - usually PA13 on STM32F4
   - **SWCLK** (SWD Clock) - usually PA14 on STM32F4
   - **GND** (Ground) - must be connected
   - **3.3V** (optional, if board doesn't have separate power)
   - **NRST** (optional but recommended) - reset pin
3. **Try lower SWD frequency**: `st-flash --freq=100 write sun-sensor-firmware.bin 0x08000000`
4. **Try with reset**: `st-flash --reset write sun-sensor-firmware.bin 0x08000000`
5. **Manual reset sequence**:
   - Hold reset button
   - Run flash command
   - Release reset button when command starts
6. **Check for pin conflicts**: Ensure SWD pins (PA13/PA14) aren't configured as GPIO in firmware
7. **Try JTAG mode**: Some boards may need JTAG instead of SWD
8. **Verify ST-Link firmware**: Update ST-Link firmware if outdated: `st-info --version`

## Development notes

## Useful docs
### STM32 F401 Series
* [STM32G4 REFERENCE MANUAL](https://www.st.com/resource/en/reference_manual/rm0368-stm32f401xbc-and-stm32f401xde-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

