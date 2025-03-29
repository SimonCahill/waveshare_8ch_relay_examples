cmake_minimum_required(VERSION 3.20)

project(waveshare_channel_select LANGUAGES CXX VERSION 1.2.0)
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

if (DEFINED channelselect_RASPI5)
    set(DEFAULT_GPIOCHIP "gpiochip4")
    set(FALLBACK_GPIOCHIP "gpiochip0")
    else()
    set(DEFAULT_GPIOCHIP "gpiochip0")
    set(FALLBACK_GPIOCHIP "gpiochip4")
endif()

add_compile_options(
    -Werror
    -Wall
    -Wpedantic
    -fPIC
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_libgpiod.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/handle_dependencies.cmake)

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

    gpiod::shared
    gpiodcxx::shared
    fmt
    nlohmann_json::nlohmann_json
)

###
# Define install target
# This will install the executable to /usr/local/bin
###
install(
    TARGETS channel_select
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)


###
# With this block, we can include the library in other projects
# By defining channelselect_BUILD_LIBRARY, cmake will generate a new target
# that can be linked to other projects.
#
# If channelselect_BUILD_LIBRARY is defined as a value other than STATIC, a shared
# library will be generated.
# Otherwise, a static library will be generated.
#
# The library will be installed to /usr/local/lib.
# The headers will be installed to /usr/local/include.
# The library will be named libchannelselect.
# Regardless of the type of library, a preprocessor definition will be added to the
# target that will be named channelselect_EXPORT_LIB. This will modify the code, so that
# fields and functions not required by a library are not compiled, and thus not included in the
# final binary.
###
if (DEFINED channelselect_BUILD_LIBRARY)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()