cmake_minimum_required(VERSION 3.10)

project(BeforeDDLServer)

include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/proto)

# 查找 src 目录中的所有源文件
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 查找 proto 目录中的所有源文件
file(GLOB_RECURSE PROTO_SOURCES "${PROJECT_SOURCE_DIR}/proto/*.cc")

# 创建 BeforeDDLServer 库
add_library(BeforeDDLServerLib ${SOURCES} ${PROTO_SOURCES})

# 创建 BeforeDDLServer 可执行文件
add_executable(BeforeDDLServer ${SOURCES} ${PROTO_SOURCES})

# 链接 gRPC 和 Protobuf 库
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

target_link_libraries(BeforeDDLServerLib gRPC::grpc++ protobuf::libprotobuf)
target_link_libraries(BeforeDDLServer BeforeDDLServerLib)

# 添加 Google Test
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找 test 目录中的所有测试文件
file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")

# 添加测试可执行文件
add_executable(Test ${TEST_SOURCES})

# 链接 gtest 和 gtest_main 库
target_link_libraries(Test PRIVATE gtest gtest_main BeforeDDLServerLib)

# 增加测试
add_test(NAME Test COMMAND Test)

# 添加自定义目标以运行测试
add_custom_target(RunTests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS Test
)

# 在构建之前运行测试
add_dependencies(BeforeDDLServer RunTests)