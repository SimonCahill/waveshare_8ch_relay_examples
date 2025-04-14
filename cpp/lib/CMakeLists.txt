project(wave8channelselect LANGUAGES CXX VERSION 1.2.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (channelselect_BUILD_LIBRARY STREQUAL "STATIC")
    add_library(
        ${PROJECT_NAME} STATIC

        ${CMAKE_CURRENT_SOURCE_DIR}/src/wave8ch.cpp
    )
else()
    add_library(
        ${PROJECT_NAME} SHARED

        ${CMAKE_CURRENT_SOURCE_DIR}/src/wave8ch.cpp
    )
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/wave8ch/wave8ch.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/wave8ch/wave8ch.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}

    gpiod::shared
    gpiodcxx::shared
    fmt
    nlohmann_json::nlohmann_json
)

target_compile_definitions(${PROJECT_NAME} PRIVATE channelselect_EXPORT_LIB)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/include/channel_select.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

###
# Define test app target (no unit tests)
###
add_executable(
    ${PROJECT_NAME}_test
    ${CMAKE_CURRENT_SOURCE_DIR}/test/libtestmain.cpp
)

target_link_libraries(
    ${PROJECT_NAME}_test
    ${PROJECT_NAME}
)