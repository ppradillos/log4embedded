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

if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_build/_install)
endif()

message("Run \"make install\" to install the library binary and the header file in ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${CMAKE_PROJECT_NAME}
                LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_DIR}
                PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${HDR_DIR})

target_link_libraries (${PROJECT_NAME} PRIVATE -lc)