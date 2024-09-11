cmake_minimum_required(VERSION 3.10)

project(BeforeDDLServer)


#基础的项目设置
include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)


#包含基础的项目文件夹结构
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/proto)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE PROTO_SOURCES "${PROJECT_SOURCE_DIR}/proto/*.cc")

add_library(BeforeDDLServerLib ${SOURCES} ${PROTO_SOURCES})
add_executable(BeforeDDLServer ${SOURCES} ${PROTO_SOURCES})


# 优先链接 /usr/local 中的库
link_directories(/usr/local/lib)


include_directories(/usr/local/include)
include_directories(/usr/local/include/hiredis)

# 链接依赖项
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(hiredis REQUIRED)
find_package(libuv REQUIRED)

if (hiredis_FOUND)
    message(STATUS "hiredis version: ${hiredis_VERSION}")
else ()
    message(FATAL_ERROR "hiredis not found")
endif ()
# 查找 Alibaba Cloud SDK
find_library(ALIBABA_CLOUD_SDK_DYSMSAPI_LIBRARY NAMES alibabacloud-sdk-dysmsapi PATHS /usr/lib/x86_64-linux-gnu)
find_library(ALIBABA_CLOUD_SDK_CORE_LIBRARY NAMES alibabacloud-sdk-core PATHS /usr/lib/x86_64-linux-gnu)


target_link_libraries(BeforeDDLServerLib hiredis)
target_link_libraries(BeforeDDLServerLib libuv::uv)
target_link_libraries(BeforeDDLServerLib nlohmann_json::nlohmann_json)
target_link_libraries(BeforeDDLServerLib gRPC::grpc++ protobuf::libprotobuf gRPC::grpc++_reflection)
target_link_libraries(BeforeDDLServerLib ${ALIBABA_CLOUD_SDK_DYSMSAPI_LIBRARY} ${ALIBABA_CLOUD_SDK_CORE_LIBRARY})


target_link_libraries(BeforeDDLServer BeforeDDLServerLib)


#GTest 自动测试相关引用
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest)
file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")
add_executable(Test ${TEST_SOURCES})
target_link_libraries(Test PRIVATE gtest gtest_main BeforeDDLServerLib)
add_test(NAME Test COMMAND Test)
add_custom_target(RunTests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS Test
)
add_dependencies(BeforeDDLServer RunTests)