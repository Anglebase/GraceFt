#pragma once

#include <Point.hpp>

namespace GFt {
    /// @addtogroup API接口库
    /// @brief 该模块是API接口库，包含了与底层交互的相关内容
    /// @{
    /// @addtogroup 按键枚举
    /// @brief 这里列举出了绝大部分按键的枚举(美式键盘)
    /// @{

    /// @brief 鼠标按钮枚举
    enum class MouseButton {
        Left,   ///< 鼠标左键
        Right,  ///< 鼠标右键
        Middle, ///< 鼠标中键
        X1,     ///< 鼠标扩展按钮 1
        X2,     ///< 鼠标扩展按钮 2
        Unknown ///< 未知按钮
    };
    /// @brief 鼠标滚轮状态枚举
    enum class MouseWheel {
        Up,     ///< 鼠标滚轮向上
        Down,   ///< 鼠标滚轮向下
        None    ///< 鼠标滚轮未滚动
    };
    /// @brief 键盘按键枚举
    enum class Key {
        A /**< A */, B /**< B */, C /**< C */, D /**< D */, E /**< E */, F /**< F */, G /**< G */, H /**< H */,
        I /**< I */, J /**< J */, K /**< K */, L /**< L */, M /**< M */, N /**< N */, O /**< O */, P /**< P */,
        Q /**< Q */, R /**< R */, S /**< S */, T /**< T */, U /**< U */, V /**< V */, W /**< W */, X /**< X */,
        Y /**< Y */, Z /**< Z */,
        _0 /**< 主按键区数字键 0 */, _1 /**< 主按键区数字键 1 */, _2 /**< 主按键区数字键 2 */, _3 /**< 主按键区数字键 3 */,
        _4 /**< 主按键区数字键 4 */, _5 /**< 主按键区数字键 5 */, _6 /**< 主按键区数字键 6 */, _7 /**< 主按键区数字键 7 */,
        _8 /**< 主按键区数字键 8 */, _9 /**< 主按键区数字键 9 */,
        F1 /**< F1 */, F2 /**< F2 */, F3 /**< F3 */, F4 /**< F4 */, F5 /**< F5 */, F6 /**< F6 */,
        F7 /**< F7 */, F8 /**< F8 */, F9 /**< F9 */, F10 /**< F10 */, F11 /**< F11 */, F12 /**< F12 */,
        Space /**< 空格 */, Enter /**< Enter */, Escape /**< Esc */, Backspace /**< Backspace */, Tab /**< Tab */,
        Left /**< 左箭头 */, Right /**< 右箭头 */, Up /**< 上箭头 */, Down /**< 下箭头 */,
        Insert /**< Insert */, Delete /**< Delete */, Home /**< Home */,
        End /**< End */, PageUp /**< PageUp */, PageDown /**< PageDown */, NumLock /**< NumLock */,
        Numpad0 /**< 小键盘数字键 0 */, Numpad1 /**< 小键盘数字键 1 */, Numpad2 /**< 小键盘数字键 2 */,
        Numpad3 /**< 小键盘数字键 3 */, Numpad4 /**< 小键盘数字键 4 */, Numpad5 /**< 小键盘数字键 5 */,
        Numpad6 /**< 小键盘数字键 6 */, Numpad7 /**< 小键盘数字键 7 */, Numpad8 /**< 小键盘数字键 8 */,
        Numpad9 /**< 小键盘数字键 9 */,
        NumpadDivide /**< 小键盘 / */, NumpadMultiply /**< 小键盘 * */,
        NumpadMinus /**< 小键盘 - */, NumpadPlus /**< 小键盘 + */,
        NumpadEnter /**< 小键盘 Enter */, NumpadDot /**< 小键盘 . */,
        CapsLock /**< CapsLock */, ScrollLock /**< ScrollLock */,
        LeftShift /**< 左Shift */, RightShift /**< 右Shift */,
        LeftControl /**< 左Ctrl */, RightControl /**< 右Ctrl */,
        LeftAlt /**< 左Alt */, RightAlt /**< 右Alt */,
        LeftSuper /**< 左Win */, RightSuper /**< 右Win */,
        Menu /**< Menu */,
        Equal /**< 符号键 = (等号/加号)*/, Minus /**< 符号键 - (减号/下划线)*/,
        LeftBracket /**< 符号键 [ (左中括号/左大括号)*/, RightBracket /**< 符号键 ] (右中括号/右大括号))*/,
        Semicolon /**< 符号键 ; (分号/冒号)*/, Quote /**< 符号键 ' (单引号/双引号)*/,
        Comma /**<符号键 , (逗号/左尖括号)*/, Period /**<符号键 . (句号/右尖括号)*/,
        Slash /**< 符号键 / (斜杠/问号)*/, Backslash /**< 符号键 \ (反斜杠/竖线)*/,
        Tilde /**< 符号键 ` (反引号/波浪号)*/, Unknown /**< 未知按键 */,
    };
    /// @}

    /// @addtogroup 事件系统
    /// @{

    /// @addtogroup 事件对象类型
    /// @brief 这里包含了所有的事件对象类型
    /// @{

    /// @brief 事件基类
    class Event {
        bool stopPropagation_ = false;

    public:
        Event() = default;
        virtual ~Event() = default;
        /// @brief 事件是否已被终止传播
        /// @return 是否已被终止传播
        bool isPropagationStopped() const;
        /// @brief 终止事件传播
        /// @details 调用该函数后，该事件将不会再向父对象传播
        void stopPropagation();
    };
    /// @brief 鼠标事件基类
    class MouseEvent : public Event {
        iPoint position_;

    public:
        MouseEvent(const iPoint& position);
        virtual ~MouseEvent() = default;
        /// @brief 获取鼠标位置
        /// @details 鼠标位置以屏幕坐标为坐标系，窗口左上角为坐标原点
        /// @return 鼠标位置
        const iPoint& position() const;
    };
    /// @brief 键盘事件基类
    class KeyboardEvent : public Event {
        Key key_;

    public:
        KeyboardEvent(Key key);
        virtual ~KeyboardEvent() = default;
        /// @brief 获取键盘按键
        /// @return 键盘按键
        Key key() const;
    };
    /// @brief 文本输入事件
    class TextInputEvent : public Event {
        int character_;

    public:
        TextInputEvent(int character);
        virtual ~TextInputEvent() = default;
        /// @brief 获取输入的字符的原始编码
        /// @return 输入的字符的原始编码
        int character() const;
    };
    /// @brief 鼠标按钮事件基类
    class MouseButtonEvent : public MouseEvent {
        MouseButton button_;

    public:
        MouseButtonEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonEvent() = default;
        /// @brief 获取鼠标按钮
        /// @return 鼠标按钮
        MouseButton button() const;
    };
    /// @brief 鼠标滚轮事件
    class MouseWheelEvent : public MouseEvent {
        MouseWheel wheel_;

    public:
        MouseWheelEvent(const iPoint& position, MouseWheel wheel);
        virtual ~MouseWheelEvent() = default;
        /// @brief 获取鼠标滚轮状态
        /// @return 鼠标滚轮状态
        MouseWheel wheel() const;
    };
    /// @brief 鼠标移动事件
    class MouseMoveEvent : public MouseEvent {
    public:
        MouseMoveEvent(const iPoint& position);
        virtual ~MouseMoveEvent() = default;
    };
    /// @brief 键盘按键按下事件
    class KeyPressEvent : public KeyboardEvent {
    public:
        KeyPressEvent(Key key);
        virtual ~KeyPressEvent() = default;
    };
    /// @brief 键盘按键弹起事件
    class KeyReleaseEvent : public KeyboardEvent {
    public:
        KeyReleaseEvent(Key key);
        virtual ~KeyReleaseEvent() = default;
    };
    /// @brief 鼠标按钮按下事件
    class MouseButtonPressEvent : public MouseButtonEvent {
    public:
        MouseButtonPressEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonPressEvent() = default;
    };
    /// @brief 鼠标按钮弹起事件
    class MouseButtonReleaseEvent : public MouseButtonEvent {
    public:
        MouseButtonReleaseEvent(const iPoint& position, MouseButton button);
        virtual ~MouseButtonReleaseEvent() = default;
    };

    /// @}
    /// @}
    /// @}
}