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
# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(comunicacap-tcp C CXX ASM)

pico_sdk_init()

# Adiciona o executável
add_executable(comunicacap-tcp comunicacap-tcp.c
)

pico_set_program_name(comunicacap-tcp "comunicacap-tcp")
pico_set_program_version(comunicacap-tcp "0.1")

pico_enable_stdio_uart(comunicacap-tcp 0)
pico_enable_stdio_usb(comunicacap-tcp 1)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/pico-ssd1306")

# Adiciona as bibliotecas necessárias
target_link_libraries(comunicacap-tcp
    pico_stdlib
    hardware_i2c
    pico-ssd1306
    pico_cyw43_arch_lwip_threadsafe_background
)

# Add include directories
target_include_directories(comunicacap-tcp PRIVATE 
${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/pico-ssd1306
)

pico_add_extra_outputs(comunicacap-tcp)
