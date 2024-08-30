cmake_minimum_required(VERSION 3.10)

project(BeforeDDLServerTests)

# 添加 Google Test
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest)

# 包含必要的目录
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/proto)

# 查找 test 目录中的所有测试文件
file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

# 添加测试可执行文件
add_executable(Test ${TEST_SOURCES})

# 链接 gtest 和 gtest_main 库
target_link_libraries(Test PRIVATE gtest gtest_main BeforeDDLServerLib)

# 增加测试
add_test(NAME Test COMMAND Test)