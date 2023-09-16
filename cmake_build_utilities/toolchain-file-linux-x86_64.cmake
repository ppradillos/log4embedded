# Specify the target platform and architecture
set(CMAKE_SYSTEM_NAME linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the C compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# You can set additional compiler flags here if needed
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ...")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ...")

# Specify the root directory (sysroot) if cross compiling
# set(CMAKE_SYSROOT "/path/to/your/sysroot")

# if not crosscompiling
# here is the target environment located
#set(CMAKE_FIND_ROOT_PATH
#  /usr
#)

# You can set other variables specific to your project here.
