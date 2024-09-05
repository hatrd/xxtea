# 解密程序
add_executable(xxtea_dec dec.cpp)

# 链接 xxtea 库
target_link_libraries(xxtea_dec PRIVATE xxtea)

# 设置解密程序输出目录
set_target_properties(xxtea_dec PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
