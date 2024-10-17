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
# Window.h TEST
add_executable(test_Window ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp)
target_link_libraries(test_Window ${GFt_LIBRARY_NAME})
# Application.h TEST
add_executable(test_Application ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp)
target_link_libraries(test_Application ${GFt_LIBRARY_NAME})
# Graphics.h TEST
add_executable(test_Graphics ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp)
target_link_libraries(test_Graphics ${GFt_LIBRARY_NAME})
# Button.h TEST
add_executable(test_Button ${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp)
target_link_libraries(test_Button ${GFt_LIBRARY_NAME})
# UI.h TEST
add_executable(test_UI ${CMAKE_CURRENT_SOURCE_DIR}/UI.cpp)
target_link_libraries(test_UI ${GFt_LIBRARY_NAME})
# RowLayout.h TEST
add_executable(test_RowLayout ${CMAKE_CURRENT_SOURCE_DIR}/RowLayout.cpp)
target_link_libraries(test_RowLayout ${GFt_LIBRARY_NAME})
# ColumnLayout.h TEST
add_executable(test_ColumnLayout ${CMAKE_CURRENT_SOURCE_DIR}/ColumnLayout.cpp)
target_link_libraries(test_ColumnLayout ${GFt_LIBRARY_NAME})
# GridLayout.h TEST
add_executable(test_GridLayout ${CMAKE_CURRENT_SOURCE_DIR}/GridLayout.cpp)
target_link_libraries(test_GridLayout ${GFt_LIBRARY_NAME})
# Path.h TEST
add_executable(test_Path "${CMAKE_CURRENT_SOURCE_DIR}/Path.cpp")
target_link_libraries(test_Path ${GFt_LIBRARY_NAME})
# Channel.hpp TEST
add_executable(test_Channel ${CMAKE_CURRENT_SOURCE_DIR}/Channel.cpp)
target_link_libraries(test_Channel ${GFt_LIBRARY_NAME})
# MainWindow.h TEST
add_executable(test_MainWindow ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp)
target_link_libraries(test_MainWindow ${GFt_LIBRARY_NAME})
# Union TEST
add_executable(test_Union ${CMAKE_CURRENT_SOURCE_DIR}/Union.cpp)
target_link_libraries(test_Union ${GFt_LIBRARY_NAME})
# Radio.h TEST
add_executable(test_Radio ${CMAKE_CURRENT_SOURCE_DIR}/Radio.cpp)
target_link_libraries(test_Radio ${GFt_LIBRARY_NAME})
# UIRadio TEST
add_executable(test_UIRadio ${CMAKE_CURRENT_SOURCE_DIR}/UIRadio.cpp)
target_link_libraries(test_UIRadio ${GFt_LIBRARY_NAME})
# Check.h TEST
add_executable(test_Check ${CMAKE_CURRENT_SOURCE_DIR}/Check.cpp)
target_link_libraries(test_Check ${GFt_LIBRARY_NAME})
# UICheck TEST
add_executable(test_UICheck ${CMAKE_CURRENT_SOURCE_DIR}/UICheck.cpp)
target_link_libraries(test_UICheck ${GFt_LIBRARY_NAME})
# Animation.hpp TEST
add_executable(test_Animation ${CMAKE_CURRENT_SOURCE_DIR}/Animation.cpp)
target_link_libraries(test_Animation ${GFt_LIBRARY_NAME})
# json.hpp TEST
add_executable(test_json ${CMAKE_CURRENT_SOURCE_DIR}/json.cpp)
target_link_libraries(test_json ${GFt_LIBRARY_NAME})
# Slider.h TEST
add_executable(test_Slider ${CMAKE_CURRENT_SOURCE_DIR}/Slider.cpp)
target_link_libraries(test_Slider ${GFt_LIBRARY_NAME})