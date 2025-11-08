cmake_minimum_required(VERSION 3.20)
project(OpenFlashloader C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/FlashLoader.ld)

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(FlashLoader.elf
    src/FlashPrg.c
    src/FlashDev.c
)

target_compile_options(FlashLoader.elf PRIVATE
    -mcpu=cortex-m33
    -mthumb
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-builtin
)

target_link_options(FlashLoader.elf PRIVATE
    -T${LINKER_SCRIPT}
    -nostartfiles
    -Wl,--gc-sections,--no-warn-rwx-segments
)
