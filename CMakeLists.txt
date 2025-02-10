# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(leds_Display C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(leds_Display 
    leds_Display.c
    bibliotecas/botao.c 
    bibliotecas/leds.c 
    bibliotecas/interrupcoes.c
    bibliotecas/matriz.c
    bibliotecas/animacoes.c
    bibliotecas/ssd1306.c
)

pico_set_program_name(leds_Display "leds_Display")
pico_set_program_version(leds_Display "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(leds_Display 0)
pico_enable_stdio_usb(leds_Display 1)

pico_generate_pio_header(leds_Display ${CMAKE_CURRENT_LIST_DIR}/leds_Display.pio)

# Add the standard library to the build
target_link_libraries(leds_Display PRIVATE
        pico_stdlib
        hardware_pio
        hardware_adc
        pico_bootrom
        hardware_i2c
        hardware_clocks
        hardware_uart)

# Add the standard include files to the build
target_include_directories(leds_Display PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/bibliotecas
)

# Add any user requested libraries
target_link_libraries(leds_Display 
        
        )

pico_add_extra_outputs(leds_Display)
