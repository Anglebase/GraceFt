#include "Event.h"

namespace GFt {
    bool Event::isPropagationStopped() const { return stopPropagation_; }
    void Event::stopPropagation() { stopPropagation_ = true; }
    MouseEvent::MouseEvent(const iPoint& position) : position_(position) {}
    const iPoint& MouseEvent::position() const { return position_; }
    KeyboardEvent::KeyboardEvent(Key key) : key_(key) {}
    Key KeyboardEvent::key() const { return key_; }
    MouseButtonEvent::MouseButtonEvent(const iPoint& position, MouseButton button)
        : MouseEvent(position), button_(button) {}
    MouseButton MouseButtonEvent::button() const { return button_; }
    MouseWheelEvent::MouseWheelEvent(const iPoint& position, MouseWheel wheel)
        : MouseEvent(position), wheel_(wheel) {}
    MouseWheel MouseWheelEvent::wheel() const { return wheel_; }
    MouseMoveEvent::MouseMoveEvent(const iPoint& position) : MouseEvent(position) {}
    KeyPressEvent::KeyPressEvent(Key key) : KeyboardEvent(key) {}
    KeyReleaseEvent::KeyReleaseEvent(Key key) : KeyboardEvent(key) {}
    MousePressEvent::MousePressEvent(const iPoint& position, MouseButton button)
        : MouseButtonEvent(position, button) {}
    MouseReleaseEvent::MouseReleaseEvent(const iPoint& position, MouseButton button)
        : MouseButtonEvent(position, button) {}
    TextInputEvent::TextInputEvent(int character) : character_(character) {}
    int TextInputEvent::character() const { return character_; }
}