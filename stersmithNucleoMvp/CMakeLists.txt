cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

#---------------------------------------------------------------------------------------------------
# Setup compiler settings
#---------------------------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Test_mx)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

#---------------------------------------------------------------------------------------------------
# Generate code
#---------------------------------------------------------------------------------------------------
set(CANGEN_SCRIPT_DIR               ${CMAKE_SOURCE_DIR}/../tools/dbcCodeGen)
file(GLOB CANGEN_SCRIPT_SOURCES     "${CANGEN_SCRIPT_DIR}/*.py")
file(GLOB CANGEN_SCRIPT_TEMPLATES   "${CANGEN_SCRIPT_DIR}/*.jinja")
set(CANGEN_SCRIPT                   ${CANGEN_SCRIPT_DIR}/dbcCodeGen.py)
set(DBC_FILE                        ${CMAKE_SOURCE_DIR}/../tools/network/EIM.dbc)
set(RX_FILE                         ${CMAKE_SOURCE_DIR}/tools/canRxSignals.json)
set(TARGET_DIR_CANGEN               ${CMAKE_SOURCE_DIR}/app/generated)
set(TARGET_SOURCES_CANGEN
    ${TARGET_DIR_CANGEN}/EIM_canReceiver.cpp
    ${TARGET_DIR_CANGEN}/EIM_canTransmitter.cpp
)
add_custom_command(
    OUTPUT ${TARGET_DIR_CANGEN} ${TARGET_SOURCES_CANGEN}
    COMMAND python3 ${CANGEN_SCRIPT} --dbcFile ${DBC_FILE} --rxFile ${RX_FILE}
            --targetDir ${TARGET_DIR_CANGEN} --alias EIM --node EIM
    DEPENDS ${DBC_FILE}
            ${RX_FILE}
            ${CANGEN_SCRIPT_SOURCES}
            ${CANGEN_SCRIPT_TEMPLATES}
    VERBATIM
)

#---------------------------------------------------------------------------------------------------
# Setup build
#---------------------------------------------------------------------------------------------------
# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
set(TARGET_SOURCES
    ${TARGET_SOURCES_CANGEN}
    app/can/canModule.cpp
    app/dataChannel/dataChannel.cpp
    app/halWrappers/halWrappersComponentSpecific.cpp
    app/profiler/profilerComponentSpecific.cpp
    app/rtos/rtos.cpp
    app/rx/rxModule.cpp
    app/tx/txModule.cpp
    ../shared/halWrappers/halWrappers.cpp
    ../shared/kline/klineModule.cpp
    ../shared/profiler/profiler.c
    ../shared/servo/servoModule.cpp
    ../shared/taskBase/taskBase.cpp
)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${TARGET_SOURCES}
)
set_source_files_properties(
    ${TARGET_SOURCES}
    PROPERTIES
    COMPILE_FLAGS "-Wextra"
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${TARGET_DIR_CANGEN}
    app/app
    app/can
    app/dataChannel
    app/halWrappers
    app/profiler
    app/rtos
    app/rx
    app/tx
    ../shared/dataChannel
    ../shared/FreeRTOS
    ../shared/halWrappers
    ../shared/kline
    ../shared/moduleBase
    ../shared/profiler
    ../shared/servo
    ../shared/taskBase
    ../shared/utils
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# Execute post-build to print size, generate hex and bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)
