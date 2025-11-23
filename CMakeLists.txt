cmake_minimum_required(VERSION 3.20)
project(OpenFlashloader C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# -----------------------------
# Parse project.config
# -----------------------------
set(PROJECT_CONFIG_FILE ${CMAKE_SOURCE_DIR}/project.config)
set(CONFIG_HEADER ${CMAKE_BINARY_DIR}/config.h)

file(WRITE ${CONFIG_HEADER} "// Auto-generated from project.config\n\n")

set(CONFIG_DEFINES "")
set(CHIP_NAME "")
set(FLASH_SIZE "")

if(EXISTS ${PROJECT_CONFIG_FILE})
    message(STATUS "Using config: ${PROJECT_CONFIG_FILE}")
    file(STRINGS ${PROJECT_CONFIG_FILE} CONFIG_LINES)

    foreach(line ${CONFIG_LINES})
        if(line MATCHES "^CONFIG_([A-Za-z0-9_]+)=(.*)")
            string(TOUPPER "${CMAKE_MATCH_1}" KEY)
            set(VALUE "${CMAKE_MATCH_2}")

            if(VALUE STREQUAL "y")
                set(VALUE 1)
            endif()

            # Add to header
            file(APPEND ${CONFIG_HEADER} "#define ${KEY} ${VALUE}\n")
            
            # Collect defines for compiler & linker
            list(APPEND CONFIG_DEFINES "${KEY}=${VALUE}")

            message(STATUS "Config: ${KEY}=${VALUE}")

            # Extract CHIP_NAME
            if(KEY STREQUAL "AMEBAGREEN2")
                set(CHIP_NAME "AMEBAGREEN2")
            elseif(KEY STREQUAL "AMEBADPLUS")
                set(CHIP_NAME "AMEBADPLUS")
            elseif(KEY STREQUAL "AMEBASMART")
                set(CHIP_NAME "AMEBASMART")
            endif()

            if(KEY STREQUAL "FLASH_SIZE_4MB")
                set(FLASH_SIZE "4MB")
            elseif(KEY STREQUAL "FLASH_SIZE_16MB")
                set(FLASH_SIZE "16MB")
            elseif(KEY STREQUAL "FLASH_SIZE_32MB")
                set(FLASH_SIZE "32MB")
            endif()

        endif()
    endforeach()
else()
    message(FATAL_ERROR "project.config not found")
endif()

if(NOT CHIP_NAME)
    message(FATAL_ERROR "No CHIP_NAME detected from project.config")
endif()

if(NOT FLASH_SIZE)
    message(FATAL_ERROR "No FLASH_SIZE detected from project.config")
endif()

set(TARGET_NAME "${CHIP_NAME}_${FLASH_SIZE}.elf")
message(STATUS "Target name: ${TARGET_NAME}")

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/vendor
)

add_executable(${TARGET_NAME}
    src/FlashPrg.c
    src/FlashDev.c
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR})

target_compile_options(${TARGET_NAME} PRIVATE
    -mcpu=cortex-m33
    -mthumb
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-builtin
)

set(PREPROCESS_DEFS "")
foreach(def ${CONFIG_DEFINES})
    list(APPEND PREPROCESS_DEFS "-D${def}")
endforeach()

# -----------------------------
# Preprocess linker script
# -----------------------------
set(LINKER_SCRIPT_SRC ${CMAKE_SOURCE_DIR}/FlashLoader.ld.S)
set(LINKER_SCRIPT_PP ${CMAKE_BINARY_DIR}/FlashLoader.pp.ld)

add_custom_command(
    OUTPUT ${LINKER_SCRIPT_PP}
    COMMAND ${CMAKE_C_COMPILER} -E -P
        ${PREPROCESS_DEFS}
        ${LINKER_SCRIPT_SRC}
        -o ${LINKER_SCRIPT_PP}
    DEPENDS ${LINKER_SCRIPT_SRC} ${PROJECT_CONFIG_FILE}
    COMMENT "Preprocessing linker script: ${LINKER_SCRIPT_SRC}"
)

add_custom_target(PreprocessLinker ALL DEPENDS ${LINKER_SCRIPT_PP})
add_dependencies(${TARGET_NAME} PreprocessLinker)

# -----------------------------
# Link using preprocessed script
# -----------------------------
target_link_options(${TARGET_NAME} PRIVATE
    -Wl,-T${LINKER_SCRIPT_PP}
    -nostartfiles
    -Wl,--gc-sections
    -Wl,--no-warn-rwx-segments
)

# -----------------------------
# Pass macros to compiler and linker
# -----------------------------
foreach(def ${CONFIG_DEFINES})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${def})
endforeach()
