include_directories(${GFt_INCLUDE_DIRS})

# Point.hpp TEST
add_executable(test_Point ${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp)
# Size.hpp TEST
add_executable(test_Size ${CMAKE_CURRENT_SOURCE_DIR}/Size.cpp)