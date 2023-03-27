cmake_minimum_required(VERSION 3.14)
project(HELLO VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)


# 添加头文件目录
include_directories(include)


# 添加源文件目录
add_subdirectory(src)