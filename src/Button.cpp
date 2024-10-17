#include "widget/Button.h"

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
            HoverOn.connect([this](Block*) {
                if (this->isDisabled()) return;
                this->brushSet_.setFillStyle(this->hoverColor_);
                });
            HoverOff.connect([this](Block*) {
                if (this->isDisabled()) return;
                this->brushSet_.setFillStyle(this->backgroundColor_);
                });
        }
        Button::Button(const iRect& rect, Block* parent, int zIndex)
            : Button(L"", rect, parent, zIndex) {}
        Button::~Button() {}

        std::wstring& Button::text() { return text_; }
        Color& Button::textColor() { return textColor_; }
        Color& Button::backgroundColor() { return backgroundColor_; }
        Color& Button::hoverColor() { return hoverColor_; }
        Color& Button::pressedColor() { return pressedColor_; }
        Color& Button::disabledColor() { return disabledColor_; }
        BrushSet& Button::brushSet() { return brushSet_; }
        TextSet& Button::textSet() { return textSet_; }

        const std::wstring& Button::text() const { return text_; }
        const Color& Button::textColor() const { return textColor_; }
        const Color& Button::backgroundColor() const { return backgroundColor_; }
        const Color& Button::hoverColor() const { return hoverColor_; }
        const Color& Button::pressedColor() const { return pressedColor_; }
        const Color& Button::disabledColor() const { return disabledColor_; }
        const BrushSet& Button::brushSet() const { return brushSet_; }
        const TextSet& Button::textSet() const { return textSet_; }

        void Button::setEnable(bool disabled) {
            disabled_ = !disabled;
            if (disabled_) {
                this->brushSet_.setFillStyle(disabledColor_);
                this->textSet_.setColor(0x707070_rgb);
            }
            else {
                this->brushSet_.setFillStyle(backgroundColor_);
                this->textSet_.setColor(textColor_);
            }
        }
        bool Button::isDisabled() const { return disabled_; }

        void Button::onDraw(Graphics& g) {
            g.bindBrushSet(&brushSet_);
            g.bindTextSet(&textSet_);
            iRect btn = iRect{ iPoint{}, rect().size() };
            g.drawFillRect(btn);
            g.drawText(text_, btn, TextAlign::Center | TextAlign::Middle);
            return Block::onDraw(g);
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