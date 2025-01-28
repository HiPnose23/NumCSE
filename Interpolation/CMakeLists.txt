
# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Interpolation VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define directories for headers and sources
include_directories(include)
include_directories(/usr/local/include/eigen3)
file(GLOB SOURCES src/*.cpp)

# Add the executable target
add_executable(Interpolation ${SOURCES})

# Optional: Display compile commands for debugging
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional: Additional warnings or flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Interpolation PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Define the graphs directory for storing plots
set(GRAPHS_DIR ${CMAKE_SOURCE_DIR}/graphs)

# Ensure the graphs directory exists
add_custom_target(create_graphs_dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GRAPHS_DIR}
    COMMENT "Creating graphs directory"
)

# Add a custom target to run the C++ executable to generate the CSV
add_custom_target(run_cpp
    COMMAND Interpolation
    DEPENDS Interpolation create_graphs_dir
    COMMENT "Running C++ program to generate CSV file"
)

# Add a custom target to run the Python script for plotting
add_custom_target(plot
    COMMAND python3 ${CMAKE_SOURCE_DIR}/src/plot.py ${GRAPHS_DIR}/output.png
    DEPENDS run_cpp
    COMMENT "Running Python script to plot data and save the graph"
)


