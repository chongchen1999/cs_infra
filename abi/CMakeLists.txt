# CMakeLists.txt - 用于编译C程序并生成汇编代码

# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(ABI_Example C)

# 设置构建目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 添加可执行文件
add_executable(main main.c)

# 自定义目标，生成汇编代码
add_custom_target(assembly
    COMMAND ${CMAKE_C_COMPILER} -S ${CMAKE_CURRENT_SOURCE_DIR}/main.c -o ${CMAKE_BINARY_DIR}/main.s
    COMMENT "Generating assembly code from main.c"
)

# 构建说明
message(STATUS "Use 'make' to build the executable")
message(STATUS "Use 'make assembly' to generate assembly code")