cmake_minimum_required(VERSION 3.22)

project(GraceFt)

set(CMAKE_CXX_STANDARD 20)

set(GFt_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)