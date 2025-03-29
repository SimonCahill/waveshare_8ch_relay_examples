include(ExternalProject)

ExternalProject_Add(
    gpiod_make

    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libgpiod
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libgpiod/autogen.sh --enable-bindings-cxx --prefix ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/

    UPDATE_COMMAND #cd ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libgpiod && autoupdate

    # BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/libgpiod
    BUILD_COMMAND make
)

set(GPIOD_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/include)
file(MAKE_DIRECTORY ${GPIOD_INCLUDE_DIR})

add_library(gpiod_static STATIC IMPORTED)
set_target_properties(gpiod_static PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/lib/libgpiod.a)
set_target_properties(gpiod_static PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GPIOD_INCLUDE_DIR})

add_library(gpiod_shared SHARED IMPORTED)
set_target_properties(gpiod_shared PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/lib/libgpiod.so)
set_target_properties(gpiod_shared PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GPIOD_INCLUDE_DIR})

add_library(gpiodcxx_static STATIC IMPORTED)
set_target_properties(gpiodcxx_static PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/lib/libgpiodcxx.a)
set_target_properties(gpiodcxx_static PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GPIOD_INCLUDE_DIR})

add_library(gpiodcxx_shared SHARED IMPORTED)
set_target_properties(gpiodcxx_shared PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libgpiod/lib/libgpiodcxx.so)
set_target_properties(gpiodcxx_shared PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${GPIOD_INCLUDE_DIR})

add_library(gpiod::static ALIAS gpiod_static)
add_library(gpiod::shared ALIAS gpiod_shared)

add_library(gpiodcxx::static ALIAS gpiodcxx_static)
add_library(gpiodcxx::shared ALIAS gpiodcxx_shared)

