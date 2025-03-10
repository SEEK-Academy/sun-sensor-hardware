

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/application)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/src/application/test)


set(TEST_SOURCES ${TESTS_DIR}/main.cc
                 ${TESTS_DIR}/lightEstimatorTest.cc
                 ${TESTS_DIR}/mathTest.cc
                 )

if(TEST)
    add_executable(run_tests ${TEST_SOURCES})
    target_link_libraries(run_tests PUBLIC GTest::gtest_main)
    target_include_directories(run_tests PUBLIC ${SOURCES_DIR}/inc)
else()

    set(MCU_FAMILY STM32F4xE)
    set(MCU_MODEL STM32F411xE)
    set(CPU_PARAMETERS
        -march=armv7e-m
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard)

    set(STARTUP ${CMAKE_SOURCE_DIR}/src/drivers/cmsis-device-f4/Source/Templates/gcc/startup_stm32f411xe.s 
                ${CMAKE_SOURCE_DIR}/src/drivers/cmsis-device-f4/Source/Templates/system_stm32f4xx.c)
    set(CUBE_F401XC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/drivers/cmsis-device-f4/Include)
    set(CMSIS_CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/drivers/cmsis-6/CMSIS/Core/Include)

    set(SUN_SENSOR_SOURCES  ${STARTUP}
                            ${SOURCES_DIR}/src/peripherials/i2c.cc
                            ${SOURCES_DIR}/src/main.cc
                            ${SOURCES_DIR}/src/peripherials/usart.cc
                            ${SOURCES_DIR}/src/peripherials/nvic.cc )

    set(SUN_SENSOR_MAIN_INCLUDES ${SOURCES_DIR}/inc)

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/src/drivers/STM32F411CE_FLASH.ld)

    add_executable(sun-sensor-firmware ${SUN_SENSOR_SOURCES})
    target_include_directories(sun-sensor-firmware PUBLIC ${CUBE_F401XC_INCLUDE_DIR} ${CMSIS_CORE_INCLUDE_DIR} ${SUN_SENSOR_MAIN_INCLUDES})

    target_compile_definitions(sun-sensor-firmware PRIVATE ${MCU_MODEL})
    target_compile_options(sun-sensor-firmware PRIVATE ${CPU_PARAMETERS}
                                                        -Wall
                                                        -Wextra
                                                        -Wpedantic
                                                        -Wno-unused-parameter
                                                        -Wno-missing-field-initializers)

    target_link_options(sun-sensor-firmware PRIVATE
                                    -T${LINKER_SCRIPT}
                                    ${CPU_PARAMETERS}
                                    -Wl,--print-memory-usage)
    set_target_properties(sun-sensor-firmware PROPERTIES SUFFIX ".elf")

    add_custom_command(TARGET sun-sensor-firmware
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        COMMENT "Generating sun-sensor-firmware.bin from sun-sensor-firmware.elf"
        )
endif()

