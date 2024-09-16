#include "Button.h"

#include <Graphics.h>

namespace GFt {
    using namespace GFt::literals;
    Button::Button(const std::wstring& text, const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex), text_(text),
        brushSet_(0x99eecf_rgb), textSet_(0_rgb, Font{ L"宋体" }) {
        onStatusChanged.connect([this](bool isPressed) {
            isPressed ? this->onClicked() : this->onReleased();
            });
    }
    Button::~Button() {}
    std::wstring& Button::text() { return text_; }
    const std::wstring& Button::text() const { return text_; }
    BrushSet& Button::brushSet() { return brushSet_; }
    const BrushSet& Button::brushSet() const { return brushSet_; }
    TextSet& Button::textSet() { return textSet_; }
    const TextSet& Button::textSet() const { return textSet_; }

    void Button::onDraw(const iRect& rect) {
        Graphics g;
        g.bindBrushSet(&brushSet_);
        g.bindTextSet(&textSet_);
        iRect btn = iRect{ iPoint{}, rect.size() };
        g.drawFillRect(btn);
        g.drawText(text_, btn, TextAlign::Center | TextAlign::Middle);
    }
    void Button::onMouseButtonPress(MouseButtonPressEvent* event) {
        if (event->button() == MouseButton::Left)
            onStatusChanged(true);
        return Block::onMouseButtonPress(event);
    }
    void Button::onMouseButtonRelease(MouseButtonReleaseEvent* event) {
        if (event->button() == MouseButton::Left)
            onStatusChanged(false);
        return Block::onMouseButtonRelease(event);
    }
}