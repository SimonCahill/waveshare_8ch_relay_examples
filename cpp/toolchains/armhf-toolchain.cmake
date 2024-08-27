# Set the CMake cross-compiling toolchain
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the path to the arm-linux-gnueabihf toolchain
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Set the target architecture
set(CMAKE_LIBRARY_ARCHITECTURE arm-linux-gnueabihf)

# Set other necessary flags and options
set(CMAKE_C_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard")

# Specify the linker
set(CMAKE_LINKER arm-linux-gnueabihf-ld)

# Specify the necessary libraries and include directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)