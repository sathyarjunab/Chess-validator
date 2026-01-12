cmake_minimum_required(VERSION 3.20)

project(chess_validator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp files inside src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Create the executable from those source files
add_executable(chess_validator ${SRC_FILES})

# Tell the compiler where header files are
target_include_directories(chess_validator PRIVATE include)
