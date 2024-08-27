# Set the CMake cross-compiling toolchain
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the path to the aarch64-linux-gnu toolchain
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Set the target architecture
set(CMAKE_LIBRARY_ARCHITECTURE aarch64-linux-gnu)

# Specify the linker
set(CMAKE_LINKER aarch64-linux-gnu-ld)

# Specify the necessary libraries and include directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)