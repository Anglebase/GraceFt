cmake_minimum_required(VERSION 3.22)

project(GraceFt)

add_definitions(-DUNICODE -D_UNICODE)

if(NOT ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 查找EGE库
set(PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/packages)
set(CMAKE_MODULE_PATH ${PACKAGE_DIR})
find_package(EGE REQUIRED)

set(CMAKE_CXX_STANDARD 20)                                # 设置c++版本
set(GFt_INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GraceFt)          # 设置头文件目录
set(GFt_LIBRARY_NAME GraceFt)                             # 设置库名称
set(GFt_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib)     # 设置库目录

# 添加子目录
add_subdirectory(src)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(tests)
endif()