cmake_minimum_required(VERSION 3.22)
project(examples)

# log4embeeded is also built in this project, so we will look for it in the build folder
set(BUILD_ENVIRONMENT ../_build)

# link the directory where the pre-built library is
link_directories(${BUILD_ENVIRONMENT})

# Set our library name, log4embedded
set(LIBRARY_NAME log4embedded)

# Create an executable for each example
add_executable(default_behaviour default_behaviour/main.c)
add_executable(set_log_file set_log_file/main.c)
add_executable(set_log_level set_log_level/main.c)

# Link the executables with log4embedded library
target_link_libraries(default_behaviour PRIVATE ${LIBRARY_NAME}.so)
target_link_libraries(set_log_file PRIVATE ${LIBRARY_NAME}.so)
target_link_libraries(set_log_level PRIVATE ${LIBRARY_NAME}.so)

install(TARGETS default_behaviour set_log_file set_log_level
        DESTINATION ${CMAKE_INSTALL_PREFIX}/examples)
