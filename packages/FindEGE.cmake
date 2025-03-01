cmake_minimum_required(VERSION 3.15)

set(EGE_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)

# 设置静态库搜索路径
if (MSVC)
    # 设置 MSVC 编译选项, 当版本大于 vs2019 时, 使用 c++17 标准.
    set(CMAKE_CXX_STANDARD 17)

    if (MSVC_VERSION GREATER_EQUAL 1930)
        # vs2022 以上, 静态库是兼容的.
        if (CMAKE_CL_64)
            set(osLibDir "vs2022/x64")
        else ()
            set(osLibDir "vs2022/x86")
        endif ()
    elseif (MSVC_VERSION GREATER_EQUAL 1920)
        # vs2019 以上, 静态库是兼容的.
        if (CMAKE_CL_64)
            set(osLibDir "vs2019/x64")
        else ()
            set(osLibDir "vs2019/x86")
        endif ()
    elseif (MSVC_VERSION GREATER_EQUAL 1910)
        # vs2017
        if (CMAKE_CL_64)
            set(osLibDir "vs2017/x64")
        else ()
            set(osLibDir "vs2017/x86")
        endif ()
        # 设置 MSVC 编译选项, 当版本为 vs2017 时, 使用 c++14 标准.
        set(CMAKE_CXX_STANDARD 14)
    elseif (MSVC_VERSION GREATER_EQUAL 1900)
        # vs2015
        if (CMAKE_CL_64)
            set(osLibDir "vs2015/amd64")
        else ()
            set(osLibDir "vs2015")
        endif ()
        # 设置 MSVC 编译选项, 当版本为 vs2015 时, 使用 c++14 标准.
        set(CMAKE_CXX_STANDARD 14)
    elseif (MSVC_VERSION GREATER_EQUAL 1600)

        if (MSVC_VERSION GREATER_EQUAL 1700)
            message(WARNING "You are using vs2012/vs2013, which is not tested, please use vs2010, vs2015 or later version of MSVC compiler.")
        endif ()

        # vs2010
        if (CMAKE_CL_64)
            set(osLibDir "vs2010/amd64")
        else ()
            set(osLibDir "vs2010")
        endif ()

    else ()
        message(FATAL_ERROR "你的 MSVC 版本太老了, 请使用 vs2015 或更新版本的 MSVC 编译器. 与时俱进吧, 不要一直使用十年前的编译器.")
    endif ()
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if (CMAKE_HOST_APPLE)
        set(osLibDir "macOS")
    else ()
        set(osLibDir "mingw-w64-debian")
    endif ()
endif ()

if (DEFINED osLibDir)
    message(STATUS "ege library dir: ${CMAKE_CURRENT_SOURCE_DIR}/lib/${osLibDir}")
    set(EGE_LIBRARY_DIRS ${PROJECT_SOURCE_DIR}/packages/lib/${osLibDir})
    message(STATUS "ege library dirs: ${EGE_LIBRARY_DIRS}")
endif ()

set(EGE_LIBRARIES graphics;gdiplus;gdi32;imm32;msimg32;ole32;oleaut32;winmm;uuid)

mark_as_advanced(EGE_INCLUDE_DIRS EGE_LIBRARY_DIRS EGE_LIBRARIES)