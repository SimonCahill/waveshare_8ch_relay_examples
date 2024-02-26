include(ExternalProject)

ExternalProject_Add(
    gpiod_make

    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libgpiod
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libgpiod/autogen.sh --enable-bindings-cxx

    # BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libgpiod
    BUILD_COMMAND make
    BUILD_IN_SOURCE 1
)

