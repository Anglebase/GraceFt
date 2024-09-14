#pragma once

#include <Point.hpp>

namespace GFt {
    /// @defgroup 枚举
    /// @ingroup API接口库

    /// @defgroup 按键枚举
    /// @brief 这里列举出了绝大部分按键的枚举(美式键盘)
    /// @ingroup 枚举

    /// @brief 鼠标按钮枚举
    /// @ingroup 枚举
    enum class MouseButton {
        Left,   ///< 鼠标左键
        Right,  ///< 鼠标右键
        Middle, ///< 鼠标中键
        X1,     ///< 鼠标扩展按钮 1
        X2,     ///< 鼠标扩展按钮 2
        Unknown ///< 未知按钮
    };
    /// @brief 鼠标滚轮状态枚举
    /// @ingroup 枚举
    enum class MouseWheel {
        Up,     ///< 鼠标滚轮向上
        Down,   ///< 鼠标滚轮向下
        None    ///< 鼠标滚轮未滚动
    };
    /// @brief 键盘按键枚举
    /// @ingroup 枚举
    enum class Key {
        LeftMouse = 0x01,    ///< 鼠标左键
        RightMouse = 0x02,   ///< 鼠标右键
        MiddleMouse = 0x04,  ///< 鼠标中键
        Backspace = 0x08,    ///< Backspace 键
        Tab = 0x09,          ///< Tab 键
        Enter = 0x0d,        ///< Enter 键
        Shift = 0x10,        ///< Shift 键
        Control = 0x11,      ///< Control 键
        Menu = 0x12,         ///< Menu 键
        Pause = 0x13,        ///< Pause 键
        Capslock = 0x14,     ///< Capslock 键 (大写锁定键)
        Esc = 0x1b,          ///< Esc 键
        Space = 0x20,        ///< 空格键

        Pageup = 0x21,       ///< Pageup 键
        Pagedown = 0x22,     ///< Pagedown 键
        End = 0x23,          ///< End 键
        Home = 0x24,         ///< Home 键

        Left = 0x25,         ///< 左方向键
        Up = 0x26,           ///< 上方向键
        Right = 0x27,        ///< 右方向键
        Down = 0x28,         ///< 下方向键

        Print = 0x2a,        ///< Print 键
        Snapshot = 0x2c,     ///< Snapshot 键
        Insert = 0x2d,       ///< Insert 键
        Delete = 0x2e,       ///< Delete 键

        _0 = 0x30,           ///< 主键盘 0 键
        _1 = 0x31,           ///< 主键盘 1 键
        _2 = 0x32,           ///< 主键盘 2 键
        _3 = 0x33,           ///< 主键盘 3 键
        _4 = 0x34,           ///< 主键盘 4 键
        _5 = 0x35,           ///< 主键盘 5 键
        _6 = 0x36,           ///< 主键盘 6 键
        _7 = 0x37,           ///< 主键盘 7 键
        _8 = 0x38,           ///< 主键盘 8 键
        _9 = 0x39,           ///< 主键盘 9 键

        A = 0x41,            ///< A 键
        B = 0x42,            ///< B 键
        C = 0x43,            ///< C 键
        D = 0x44,            ///< D 键
        E = 0x45,            ///< E 键
        F = 0x46,            ///< F 键
        G = 0x47,            ///< G 键
        H = 0x48,            ///< H 键
        I = 0x49,            ///< I 键
        J = 0x4a,            ///< J 键
        K = 0x4b,            ///< K 键
        L = 0x4c,            ///< L 键
        M = 0x4d,            ///< M 键
        N = 0x4e,            ///< N 键
        O = 0x4f,            ///< O 键
        P = 0x50,            ///< P 键
        Q = 0x51,            ///< Q 键
        R = 0x52,            ///< R 键
        S = 0x53,            ///< S 键
        T = 0x54,            ///< T 键
        U = 0x55,            ///< U 键
        V = 0x56,            ///< V 键
        W = 0x57,            ///< W 键
        X = 0x58,            ///< X 键
        Y = 0x59,            ///< Y 键
        Z = 0x5a,            ///< Z 键
        LeftWin = 0x5b,      ///< 左 Windows 键
        RightWin = 0x5c,     ///< 右 Windows 键

        Sleep = 0x5f,        ///< Sleep 键

        Num0 = 0x60,         ///< 小键盘 0 键
        Num1 = 0x61,         ///< 小键盘 1 键
        Num2 = 0x62,         ///< 小键盘 2 键
        Num3 = 0x63,         ///< 小键盘 3 键
        Num4 = 0x64,         ///< 小键盘 4 键
        Num5 = 0x65,         ///< 小键盘 5 键
        Num6 = 0x66,         ///< 小键盘 6 键
        Num7 = 0x67,         ///< 小键盘 7 键
        Num8 = 0x68,         ///< 小键盘 8 键
        Num9 = 0x69,         ///< 小键盘 9 键

        Multiply = 0x6a,     ///< 小键盘 * 键
        Add = 0x6b,          ///< 小键盘 + 键
        Separator = 0x6c,    ///< 小键盘 , 键
        Subtract = 0x6d,     ///< 小键盘 - 键
        Decimal = 0x6e,      ///< 小键盘 . 键
        Divide = 0x6f,       ///< 小键盘 / 键

        F1 = 0x70,           ///< F1 键
        F2 = 0x71,           ///< F2 键
        F3 = 0x72,           ///< F3 键
        F4 = 0x73,           ///< F4 键
        F5 = 0x74,           ///< F5 键
        F6 = 0x75,           ///< F6 键
        F7 = 0x76,           ///< F7 键
        F8 = 0x77,           ///< F8 键
        F9 = 0x78,           ///< F9 键
        F10 = 0x79,          ///< F10 键
        F11 = 0x7a,          ///< F11 键
        F12 = 0x7b,          ///< F12 键

        Numlock = 0x90,      ///< Numlock 键
        Scrolllock = 0x91,   ///< Scrolllock 键

        LeftShift = 0xa0,    ///< 左 Shift 键
        RightShift = 0xa1,   ///< 右 Shift 键
        LeftControl = 0xa2,  ///< 左 Control 键
        RightControl = 0xa3, ///< 右 Control 键
        LeftMenu = 0xa4,     ///< 左 Menu 键
        RightMenu = 0xa5,    ///< 右 Menu 键

        Semicolon = 0xba,    ///< ;: 键
        Plus = 0xbb,         ///< =+ 键
        Comma = 0xbc,        ///< ,< 键
        Minus = 0xbd,        ///< -_ 键
        Period = 0xbe,       ///< .> 键
        Slash = 0xbf,        ///< /? 键
        Tilde = 0xc0,        ///< `~ 键
        Lbrace = 0xdb,       ///< [{ 键
        Backslash = 0xdc,    ///< \| 键
        Rbrace = 0xdd,       ///< ]} 键
        Quote = 0xde,        ///< '" 键

        ImeProcess = 0xe5    ///< IME 处理键
    };

    /// @defgroup 事件对象类型
    /// @brief 这里包含了所有的事件对象类型
    /// @ingroup 事件系统

    /// @brief 事件基类
    /// @ingroup 事件对象类型
    class Event {
        bool stopPropagation_ = false;

    public:
        /// @cond IGNORE
        Event() = default;
        virtual ~Event() = default;
        /// @endcond
        /// @brief 事件是否已被终止传播
        /// @return 是否已被终止传播
        bool isPropagationStopped() const;
        /// @brief 终止事件传播
        /// @details 调用该函数后，该事件将不会再向父对象传播(阻止事件冒泡)
        void stopPropagation();
        /// @brief 接受事件
        /// @details 调用该函数后，该事件将不会再向父对象传播(阻止事件冒泡)
        ///          效果上等同于调用 stopPropagation() 函数
        /// @see stopPropagation()
        void accept();
        /// @brief 事件是否已被接受
        /// @return 是否已被接受
        /// @brief 效果上等同于调用 isPropagationStopped() 函数
        /// @see isPropagationStopped()
        bool isAccepted() const;
    };
    /// @brief 鼠标事件基类
    /// @ingroup 事件对象类型
    class MouseEvent : public Event {
        iPoint position_;
        iPoint absolutePosition_;

    public:
        /// @cond IGNORE
        MouseEvent(const iPoint& position);
        virtual ~MouseEvent() = default;
        /// @endcond
        /// @brief 获取鼠标位置
        /// @details 鼠标位置以屏幕坐标为坐标系，窗口左上角为坐标原点
        /// @return 鼠标位置
        const iPoint& position() const;
        /// @brief 获取鼠标在屏幕上的绝对位置
        /// @details 鼠标位置以屏幕坐标为坐标系，窗口左上角为坐标原点
        /// @return 鼠标在屏幕上的绝对位置
        const iPoint& absolutePosition() const;
    };
    /// @brief 键盘事件基类
    /// @ingroup 事件对象类型
    class KeyboardEvent : public Event {
        Key key_;
        bool shift_ = false;
        bool ctrl_ = false;

    public:
        /// @cond IGNORE
        KeyboardEvent(Key key, bool shift, bool control);
        virtual ~KeyboardEvent() = default;
        /// @endcond
        /// @brief 获取键盘按键
        /// @return 键盘按键
        Key key() const;
    };
    /// @brief 文本输入事件
    /// @ingroup 事件对象类型
    class TextInputEvent : public Event {
        int character_;

    public:
        /// @cond IGNORE
        TextInputEvent(int character);
        virtual ~TextInputEvent() = default;
        /// @endcond
        /// @brief 获取输入的字符的原始编码
        /// @return 输入的字符的原始编码
        int character() const;
    };
    /// @brief 鼠标按钮事件基类
    /// @ingroup 事件对象类型
    class MouseButtonEvent : public MouseEvent {
        MouseButton button_;

    public:
        /// @cond IGNORE
        MouseButtonEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonEvent() = default;
        /// @endcond
        /// @brief 获取鼠标按钮
        /// @return 鼠标按钮
        MouseButton button() const;
    };
    /// @brief 鼠标滚轮事件
    /// @ingroup 事件对象类型
    class MouseWheelEvent : public MouseEvent {
        MouseWheel wheel_;

    public:
        /// @cond IGNORE
        MouseWheelEvent(const iPoint& position, MouseWheel wheel);
        virtual ~MouseWheelEvent() = default;
        /// @endcond
        /// @brief 获取鼠标滚轮状态
        /// @return 鼠标滚轮状态
        MouseWheel wheel() const;
    };
    /// @brief 鼠标移动事件
    /// @ingroup 事件对象类型
    class MouseMoveEvent : public MouseEvent {
    public:
        /// @cond IGNORE
        MouseMoveEvent(const iPoint& position);
        virtual ~MouseMoveEvent() = default;
        /// @endcond
    };
    /// @brief 键盘按键按下事件
    /// @ingroup 事件对象类型
    class KeyPressEvent : public KeyboardEvent {
    public:
        /// @cond IGNORE
        KeyPressEvent(Key key, bool shift, bool control);
        virtual ~KeyPressEvent() = default;
        /// @endcond
    };
    /// @brief 键盘按键弹起事件
    /// @ingroup 事件对象类型
    class KeyReleaseEvent : public KeyboardEvent {
    public:
        /// @cond IGNORE
        KeyReleaseEvent(Key key, bool shift, bool control);
        virtual ~KeyReleaseEvent() = default;
        /// @endcond
    };
    /// @brief 鼠标按钮按下事件
    /// @ingroup 事件对象类型
    class MouseButtonPressEvent : public MouseButtonEvent {
    public:
        /// @cond IGNORE
        MouseButtonPressEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonPressEvent() = default;
        /// @endcond
    };
    /// @brief 鼠标按钮弹起事件
    /// @ingroup 事件对象类型
    class MouseButtonReleaseEvent : public MouseButtonEvent {
    public:
        /// @cond IGNORE
        MouseButtonReleaseEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonReleaseEvent() = default;
        /// @endcond
    };
}