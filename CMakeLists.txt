cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(osc VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target with source files
add_executable(
    osc
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/assembler.cpp
)

# Include directories
target_include_directories(osc PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
