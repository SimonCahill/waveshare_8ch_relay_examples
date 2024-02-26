cmake_minimum_required(VERSION 3.20)

project(waveshare_channel_select LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -ggdb
        -O0
    )
else()
    add_compile_options(
        -O2
    )
endif()

add_compile_options(
    -Werror
    -Wall
    -Wpedantic
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_libgpiod.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/channel_select.in.hpp ${CMAKE_CURRENT_BINARY_DIR}/include/channel_select.hpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/fmt)

add_executable(
    channel_select

    ${CMAKE_CURRENT_SOURCE_DIR}/channel_select.cpp
)

target_include_directories(channel_select PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_link_libraries(
    channel_select

    gpiod
    fmt
)