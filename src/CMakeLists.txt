# src/CMakeLists.txt

include_directories(${GFt_INCLUDE_DIRS})
include_directories(${EGE_INCLUDE_DIRS})

set(GFt_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BlockFocus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BrushSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ColumnLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Font.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Graphics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GridLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Label.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Layout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/Path.cpp"
    ${CMAKE_CURRENT_SOURCE_DIR}/PenSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PixelMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RowLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/UI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
)

set(LIBRARY_OUTPUT_PATH ${GFt_LIBRARY_DIRS})              # 设置库输出目录
foreach(_src ${GFt_SOURCES})
    message(STATUS "Adding ${_src} to ${GFt_LIBRARY_NAME}")
endforeach(_src ${GFt_SOURCES})

add_library(${GFt_LIBRARY_NAME} STATIC ${GFt_SOURCES})
target_link_directories(${GFt_LIBRARY_NAME} PUBLIC ${EGE_LIBRARY_DIRS})
target_link_libraries(${GFt_LIBRARY_NAME} ${EGE_LIBRARIES})