# It's strongly recommended that you specify a toolchain file instead of setting everything in the root CMakeLists.txt

cmake_minimum_required(VERSION 3.22)
project(log4embedded)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

message("-----------------------------------------------------------")
message("Creating makefile of ${CMAKE_PROJECT_NAME} as ${CMAKE_BUILD_TYPE}")

# Check if compiler has been already set via toolchain file or as external argument
if(NOT CMAKE_C_COMPILER)
  # User-defined compiler (default to gcc)
  set(CMAKE_C_COMPILER gcc)
endif()

# Library source and header file
set(SRC_FILE log4embedded.c)
set(HDR_FILE log4embedded.h)

# Output dynamic library name and version
set(LIB_NAME log4embedded.so)
set(LIB_VERSION 1)

# Source and object files directory
set(HDR_DIR include)
set(SRC_DIR src)
set(OBJ_DIR obj)
set(LIB_DIR lib)

# Debug and release compiler flags
set(COMMON_C_FLAGS -Wall -Wextra -Werror -shared -fPIC -fdiagnostics-color -pedantic)
set(DEBUG_CFLAGS ${COMMON_C_FLAGS} -g -O0 -DDEBUG)
set(RELEASE_CFLAGS ${COMMON_C_FLAGS} -s -O3)

include_directories(${HDR_DIR})

# By default, build the release version
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Debug build --> ${CMAKE_C_FLAGS} coming from toolchain files
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CFLAGS ${CMAKE_C_FLAGS} ${DEBUG_CFLAGS})
else()
  set(CFLAGS ${CMAKE_C_FLAGS} ${RELEASE_CFLAGS})
endif()

#Files
set(EXPORTABLE_HEADERS ${HDR_DIR}/${HDR_FILE})
set(SOURCES ${SRC_DIR}/${SRC_FILE})
set(HEADERS ${EXPORTABLE_HEADERS})    

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${HDR_DIR}>
                           INTERFACE $<INSTALL_INTERFACE:${HDR_DIR}>)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${EXPORTABLE_HEADERS}")

# Set up installation folder, if does not exist already
if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/package)
endif()

message("CMake's configuration done. Now navigate to the CMake's build directory you have set up: ${CMAKE_BINARY_DIR}.")
message("Once you navigate to the build directory, now you can:")
message("Run \"make\" to build the library binary in ${CMAKE_BINARY_DIR}, with no further installation nor packaging.")
message("Run \"make install\" to install the files in ${CMAKE_INSTALL_PREFIX}.")
message("Run \"make package\" to pack the installation files in a distribution package, also in ${CMAKE_INSTALL_PREFIX}.")

# Install log4embedded binary and header files in ${CMAKE_INSTALL_PREFIX}
install(TARGETS ${CMAKE_PROJECT_NAME}
                LIBRARY DESTINATION ${LIB_DIR}
                PUBLIC_HEADER DESTINATION ${HDR_DIR})

# Install the license file in ${CMAKE_INSTALL_PREFIX}
install(FILES 
          ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE 
          ${CMAKE_CURRENT_SOURCE_DIR}/README.md 
          DESTINATION .)

target_link_libraries (${PROJECT_NAME} PRIVATE -lc)

#Add examples
if (BUILD_EXAMPLES)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples ${CMAKE_CURRENT_BINARY_DIR}/examples)
endif()

# Configure log4embedded package
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_DESCRIPTION "Fast-performance, colorful log library for embedded systems")
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})

# Finally, include packaging option
include(CPack)