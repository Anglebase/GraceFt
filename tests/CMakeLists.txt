# tests/CMakeLists.txt

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
# Signal.hpp TEST
add_executable(test_Signal ${CMAKE_CURRENT_SOURCE_DIR}/Signal.cpp)
# LMath.hpp TEST
add_executable(test_LMath ${CMAKE_CURRENT_SOURCE_DIR}/LMath.cpp)
# Line.hpp TEST
add_executable(test_Line ${CMAKE_CURRENT_SOURCE_DIR}/Line.cpp)
# Color.h TEST
add_executable(test_Color ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp)
target_link_libraries(test_Color ${GFt_LIBRARY_NAME})
# Font.h TEST
add_executable(test_Font ${CMAKE_CURRENT_SOURCE_DIR}/Font.cpp)
target_link_libraries(test_Font ${GFt_LIBRARY_NAME})
# BrushSet.h TEST
add_executable(test_BrushSet ${CMAKE_CURRENT_SOURCE_DIR}/BrushSet.cpp)
target_link_libraries(test_BrushSet ${GFt_LIBRARY_NAME})
# TextSet.h TEST
add_executable(test_TextSet ${CMAKE_CURRENT_SOURCE_DIR}/TextSet.cpp)
target_link_libraries(test_TextSet ${GFt_LIBRARY_NAME})