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

            message(STATUS "Config: ${KEY} = ${VALUE}")

            # Extract CHIP_NAME
            if(KEY STREQUAL "AMEBAGREEN2")
                set(CHIP_NAME "AMEBAGREEN2")
                message(STATUS "Detected CHIP_NAME: ${CHIP_NAME}")
            elseif(KEY STREQUAL "AMEBADPLUS")
                set(CHIP_NAME "AMEBADPLUS")
                message(STATUS "Detected CHIP_NAME: ${CHIP_NAME}")
            else()
                set(CHIP_NAME "UNKNOWN")
            endif()
            set(TARGET_NAME "${CHIP_NAME}.elf")

        endif()
    endforeach()
else()
    message(WARNING "No project.config found")
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/vendor
)

# Executable
add_executable(${TARGET_NAME}
    src/FlashPrg.c
    src/FlashDev.c
)

# Compiler options
target_compile_options(${TARGET_NAME} PRIVATE
    -mcpu=cortex-m33
    -mthumb
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-builtin
)

# Include generated header
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR})

# -----------------------------
# Preprocess linker script
# -----------------------------
set(LINKER_SCRIPT_SRC ${CMAKE_SOURCE_DIR}/FlashLoader.ld.S)
set(LINKER_SCRIPT_PP ${CMAKE_BINARY_DIR}/FlashLoader.pp.ld)

add_custom_command(
    OUTPUT ${LINKER_SCRIPT_PP}
    COMMAND ${CMAKE_C_COMPILER} -E -P
        $<$<BOOL:${CONFIG_DEFINES}>:-D${CONFIG_DEFINES}>
        ${LINKER_SCRIPT_SRC}
        -o ${LINKER_SCRIPT_PP}
    DEPENDS ${LINKER_SCRIPT_SRC} ${PROJECT_CONFIG_FILE}
    COMMENT "Preprocessing linker script ${LINKER_SCRIPT_SRC}"
)

add_custom_target(PreprocessLinker ALL DEPENDS ${LINKER_SCRIPT_PP})
add_dependencies(${TARGET_NAME} PreprocessLinker)

# -----------------------------
# Link using preprocessed script
# -----------------------------
target_link_options(${TARGET_NAME} PRIVATE
    -Wl,-T${LINKER_SCRIPT_PP}
    -nostartfiles
    -Wl,--gc-sections,--no-warn-rwx-segments
)

# -----------------------------
# Pass macros to compiler and linker
# -----------------------------
foreach(def ${CONFIG_DEFINES})
    target_compile_definitions(${TARGET_NAME} PRIVATE ${def})
    target_link_options(${TARGET_NAME} PRIVATE "-Wl,-defsym,${def}")
endforeach()
