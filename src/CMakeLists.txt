# src/CMakeLists.txt

include_directories(${GFt_INCLUDE_DIRS})
include_directories(${EGE_INCLUDE_DIRS})

set(GFt_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp 
)

set(LIBRARY_OUTPUT_PATH ${GFt_LIBRARY_DIRS})              # 设置库输出目录
foreach(_src ${GFt_SOURCES})
    message(STATUS "Adding ${_src} to ${GFt_LIBRARY_NAME}")
endforeach(_src ${GFt_SOURCES})

add_library(${GFt_LIBRARY_NAME} STATIC ${GFt_SOURCES})
target_link_directories(${GFt_LIBRARY_NAME} PUBLIC ${EGE_LIBRARY_DIRS})
target_link_libraries(${GFt_LIBRARY_NAME} ${EGE_LIBRARIES})