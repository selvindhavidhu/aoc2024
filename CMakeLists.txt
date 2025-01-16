cmake_minimum_required (VERSION 3.20)

set(PROJECT_NAME "aoc2024")
project ("${PROJECT_NAME}" VERSION 1.0.0 LANGUAGES CXX)

# Set the C++ standard to C++17
set (CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB all_SRCS 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/day_1/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/day_1/*.h")

include(compiler_flags.cmake)

add_executable(${PROJECT_NAME} ${all_SRCS} "src/day_1/day_1_header.h" "src/day_1/day_1_imp.cpp" "src/stdheaders.h")

# Copy the files in the resources directory to the output directory.
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)