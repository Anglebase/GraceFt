#include "Button.h"

#include <Graphics.h>

namespace GFt {
    namespace Widget {
        using namespace GFt::literals;
        Button::Button(const std::wstring& text, const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex), text_(text),
            brushSet_(0xeeeeee_rgb), textSet_(0_rgb, Font{ L"宋体" }) {
            onStatusChanged.connect([this](bool isPressed) {
                isPressed ? this->onClicked() : this->onReleased();
                });
            HoverOn.connect([this](Block*){ this->brushSet_.setFillStyle(this->hoverColor_); });
            HoverOff.connect([this](Block*){ this->brushSet_.setFillStyle(this->backgroundColor_); });
        }
        Button::~Button() {}

        std::wstring& Button::text() { return text_; }
        Color& Button::textColor() { return textColor_; }
        Color& Button::backgroundColor() { return backgroundColor_; }
        Color& Button::hoverColor() { return hoverColor_; }
        Color& Button::pressedColor() { return pressedColor_; }
        Color& Button::disabledColor() { return disabledColor_; }

        const std::wstring& Button::text() const { return text_; }
        const Color& Button::textColor() const { return textColor_; }
        const Color& Button::backgroundColor() const { return backgroundColor_; }
        const Color& Button::hoverColor() const { return hoverColor_; }
        const Color& Button::pressedColor() const { return pressedColor_; }
        const Color& Button::disabledColor() const { return disabledColor_; }

        void Button::setEnable(bool disabled) { disabled_ = !disabled; }
        bool Button::isDisabled() const { return disabled_; }

        void Button::onDraw(const iRect& rect) {
            Graphics g;
            if (disabled_) 
                brushSet_.setFillStyle(disabledColor_);
            g.bindBrushSet(&brushSet_);
            g.bindTextSet(&textSet_);
            iRect btn = iRect{ iPoint{}, rect.size() };
            g.drawFillRect(btn);
            g.drawText(text_, btn, TextAlign::Center | TextAlign::Middle);
        }
        void Button::onMouseButtonPress(MouseButtonPressEvent* event) {
            if (disabled_) return;
            this->brushSet_.setFillStyle(this->pressedColor_);
            if (event->button() == MouseButton::Left)
                onStatusChanged(true);
            return Block::onMouseButtonPress(event);
        }
        void Button::onMouseButtonRelease(MouseButtonReleaseEvent* event) {
            if (disabled_) return;
            this->brushSet_.setFillStyle(this->hoverColor_);
            if (event->button() == MouseButton::Left)
                onStatusChanged(false);
            return Block::onMouseButtonRelease(event);
        }
    }
}