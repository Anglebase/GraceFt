include_directories(${GFt_INCLUDE_DIRS})

# 基础示例
add_executable(exp_BasicFrame ${CMAKE_CURRENT_SOURCE_DIR}/BasicFrame.cpp)
target_link_libraries(exp_BasicFrame ${GFt_LIBRARY_NAME})

# 自定义窗口示例
add_executable(exp_MyWindow ${CMAKE_CURRENT_SOURCE_DIR}/MyWindow.cpp)
target_link_libraries(exp_MyWindow ${GFt_LIBRARY_NAME})