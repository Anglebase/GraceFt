include_directories(${GFt_INCLUDE_DIRS})

# Point.hpp TEST
add_executable(test_Point ${CMAKE_CURRENT_SOURCE_DIR}/Point.cpp)
# Size.hpp TEST
add_executable(test_Size ${CMAKE_CURRENT_SOURCE_DIR}/Size.cpp)
# Rect.hpp TEST
add_executable(test_Rect ${CMAKE_CURRENT_SOURCE_DIR}/Rect.cpp)
# Circle.hpp TEST
add_executable(test_Circle ${CMAKE_CURRENT_SOURCE_DIR}/Circle.cpp)
# Matrix.hpp TEST
add_executable(test_Matrix ${CMAKE_CURRENT_SOURCE_DIR}/Matrix.cpp)
