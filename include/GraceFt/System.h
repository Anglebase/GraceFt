#pragma once

#include <GraceFt/Event.h>
#include <GraceFt/Point.hpp>
#include <optional>

namespace GFt {
    /// @brief 系统调用接口函数
    /// @details 系统调用接口相关的函数，它们几乎等同于 Windows API 中的函数原型，但对部分函数添加了 C++ 风格封装
    /// @ingroup API接口库
    namespace Sys {
        /// @brief 获取键盘按键状态(基于消息队列读取)
        /// @param key 要获取的按键
        /// @return 按键状态
        ///         - 若高序位`(x & 0x8000)` 为 1，则表示按键当前处于按下状态；
        ///         - 若低序位`(x & 0x0001)` 为 1，则表示该按键在上次调用此函数后至少被按下了一次
        unsigned short getKeyState(Key key);
        /// @brief 获取键盘按键状态(直接读取物理设备)
        /// @param key 要获取的按键
        /// @return 按键状态
        ///         - 若高序位`(x & 0x8000)` 为 1，则表示按键当前处于按下状态；
        ///         - 若低序位`(x & 0x0001)` 为 1，则表示该按键在上次调用此函数后至少被按下了一次
        unsigned short getAsyncKeyState(Key key);
        /// @brief 获取鼠标的绝对位置
        /// @return 鼠标位置的坐标
        /// @see Application::getAbsoluteMousePosition()
        iPoint getCursorPosition();
        /// @brief 设置鼠标的绝对位置
        /// @param pos 要设置的鼠标位置的坐标
        void setCursorPosition(iPoint pos);
        /// @brief 从剪贴板获取文本
        /// @return 剪贴板文本
        std::wstring getCilpBoardText();
        /// @brief 向剪贴板设置文本
        /// @param text 要设置的剪贴板文本
        void setCilpBoardText(std::wstring text);
        /// @brief 获取环境变量的值
        /// @param name 环境变量名
        /// @return 环境变量的值，若环境变量不存在，则返回空值
        std::optional<std::string> getEnv(const std::string& name);
    }
}