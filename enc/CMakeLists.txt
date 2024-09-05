# 加密程序
add_executable(xxtea_enc enc.cpp)

# 链接 xxtea 库
target_link_libraries(xxtea_enc PRIVATE xxtea)

# 设置加密程序输出目录
set_target_properties(xxtea_enc PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)