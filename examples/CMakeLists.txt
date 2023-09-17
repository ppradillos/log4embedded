cmake_minimum_required(VERSION 3.22)
project(examples)

# link the directory where the pre-built library is
link_directories(${CMAKE_BINARY_DIR})

# Set our library name, log4embedded
set(LIBRARY_NAME log4embedded)

# Create an executable for each example
add_executable(default_behaviour default_behaviour/default_behaviour.c)
add_executable(set_log_file set_log_file/set_log_file.c)
add_executable(set_log_level set_log_level/set_log_level.c)

# Link the executables with log4embedded library
target_link_libraries(default_behaviour PRIVATE ${LIBRARY_NAME}.so)
target_link_libraries(set_log_file PRIVATE ${LIBRARY_NAME}.so)
target_link_libraries(set_log_level PRIVATE ${LIBRARY_NAME}.so)

install(TARGETS default_behaviour set_log_file set_log_level
        DESTINATION examples/bin)

install(FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/default_behaviour/default_behaviour.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/set_log_file/set_log_file.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/set_log_level/set_log_level.c
        DESTINATION examples/src)
