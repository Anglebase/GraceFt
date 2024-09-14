#pragma once

#include <Event.h>

namespace GFt {
    /// @addtogroup API接口库
    /// @{
    /// @addtogroup 事件系统
    /// @{
    /// @addtogroup 事件监视器
    /// @brief 通过继承这些类, 可以监视并处理事件
    /// @details 由于它们全部都是抽象类, 所以必须在派生类中实现它们的虚函数
    /// @{

    /// @brief 鼠标按钮按下事件监视器接口类
    class MouseButtonPressEventMonitor {
    public:
        /// @cond IGNORE
        MouseButtonPressEventMonitor() = default;
        virtual ~MouseButtonPressEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 鼠标按钮按下事件处理函数
        /// @param event 鼠标按钮按下事件
        virtual void onMouseButtonPress(MouseButtonPressEvent* event) = 0;
    };
    /// @brief 鼠标按钮释放事件监视器接口类
    class MouseButtonReleaseEventMonitor {
    public:
        /// @cond IGNORE
        MouseButtonReleaseEventMonitor() = default;
        virtual ~MouseButtonReleaseEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 鼠标按钮释放事件处理函数
        /// @param event 鼠标按钮释放事件
        virtual void onMouseButtonRelease(MouseButtonReleaseEvent* event) = 0;
    };
    /// @brief 键盘按下事件监视器接口类
    class KeyPressEventMonitor {
    public:
        /// @cond IGNORE
        KeyPressEventMonitor() = default;
        virtual ~KeyPressEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 键盘按下事件处理函数
        /// @param event 键盘按下事件
        virtual void onKeyPress(KeyPressEvent* event) = 0;
    };
    /// @brief 键盘释放事件监视器接口类
    class KeyReleaseEventMonitor {
    public:
        /// @cond IGNORE
        KeyReleaseEventMonitor() = default;
        virtual ~KeyReleaseEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 键盘释放事件处理函数
        /// @param event 键盘释放事件
        virtual void onKeyRelease(KeyReleaseEvent* event) = 0;
    };
    /// @brief 鼠标按钮事件监视器接口类
    class MouseButtonEventMonitor :
        public MouseButtonPressEventMonitor,
        public MouseButtonReleaseEventMonitor {
    public:
        /// @cond IGNORE
        MouseButtonEventMonitor() = default;
        virtual ~MouseButtonEventMonitor() = default;
        /// @endcond
    };
    /// @brief 鼠标移动事件监视器接口类
    class MouseMoveEventMonitor {
    public:
        /// @cond IGNORE
        MouseMoveEventMonitor() = default;
        virtual ~MouseMoveEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 鼠标移动事件处理函数
        /// @param event 鼠标移动事件
        virtual void onMouseMove(MouseMoveEvent* event) = 0;
    };
    /// @brief 鼠标滚轮事件监视器接口类
    class MouseWheelEventMonitor {
    public:
        /// @cond IGNORE
        MouseWheelEventMonitor() = default;
        virtual ~MouseWheelEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 鼠标滚轮事件处理函数
        /// @param event 鼠标滚轮事件
        virtual void onMouseWheel(MouseWheelEvent* event) = 0;
    };
    /// @brief 鼠标和键盘事件监视器接口类
    class MouseEventMonitor :
        public MouseButtonEventMonitor,
        public MouseMoveEventMonitor,
        public MouseWheelEventMonitor {
    public:
        /// @cond IGNORE
        MouseEventMonitor() = default;
        virtual ~MouseEventMonitor() = default;
        /// @endcond
    };
    /// @brief 键盘事件监视器接口类
    class KeyboardEventMonitor :
        public KeyPressEventMonitor,
        public KeyReleaseEventMonitor {
    public:
        /// @cond IGNORE
        KeyboardEventMonitor() = default;
        virtual ~KeyboardEventMonitor() = default;
        /// @endcond
    };
    /// @brief 文本输入事件监视器接口类
    class TextInputEventMonitor {
    public:
        /// @cond IGNORE
        TextInputEventMonitor() = default;
        virtual ~TextInputEventMonitor() = default;
        /// @endcond
    protected:
        /// @brief 文本输入事件处理函数
        /// @param event 文本输入事件
        virtual void onTextInput(TextInputEvent* event) = 0;
    };
    /// @brief 事件监视器接口类
    class EventMonitor :
        public MouseEventMonitor,
        public KeyboardEventMonitor,
        public TextInputEventMonitor {
    public:
        /// @cond IGNORE
        EventMonitor() = default;
        virtual ~EventMonitor() = default;
        /// @endcond
    };
}