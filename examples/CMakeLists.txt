include_directories(${GFt_INCLUDE_DIRS})

add_executable(exp_BasicFrame ${CMAKE_CURRENT_SOURCE_DIR}/BasicFrame.cpp)
target_link_libraries(exp_BasicFrame ${GFt_LIBRARY_NAME})