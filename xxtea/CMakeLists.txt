# 创建 xxtea 静态库
add_library(xxtea STATIC xxtea.c)

# 包含头文件
target_include_directories(xxtea INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})