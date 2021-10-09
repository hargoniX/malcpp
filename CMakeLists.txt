cmake_minimum_required(VERSION 3.10)
project(mal)
add_executable(mal src/mal.cpp)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror)


target_include_directories(mal PRIVATE include)
target_sources(mal PRIVATE src/mal.cpp src/reader.cpp src/values.cpp)
