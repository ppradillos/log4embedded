# This is a CMake toolchain file for cross-compiling to ARM Linux

# Set the CMake system name and processor
set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#Paths for the cross compiler. I have set the default ones for the cross compiler you download straight from Ubuntu's repos
set(CMAKE_C_COMPILER "/usr/bin/arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-linux-gnueabihf-cpp")
set(CMAKE_FIND_ROOT_PATH "/usr/arm-linux-gnueabihf")
#set(CMAKE_SYSROOT "${CMAKE_FIND_ROOT_PATH}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${CMAKE_SYSROOT}/lib/arm-linux-gnueabihf")

# Set the CMake flags for the cross-compiler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard")

# Specify the include directories for the cross-compiler 
if(NOT CMAKE_SYSROOT)
    set(CMAKE_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
    set(CMAKE_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")
else()
    set(CMAKE_INCLUDE_PATH "${CMAKE_SYSROOT}/usr/include")
    set(CMAKE_LIBRARY_PATH "${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf")
endif()

# Force CMake not to run compiler test. It usually fails with cross compilers.
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Include the default toolchain file
#include(CMakeForceCompiler)

# You can add any additional settings or variables specific to your project here.

