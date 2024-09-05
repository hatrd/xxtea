cmake_minimum_required(VERSION 3.10)
project(XXTEA_Project)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# 添加子目录
add_subdirectory(xxtea)
add_subdirectory(enc)
add_subdirectory(dec)