#pragma once

#include <GraceFt/Block.h>
#include <GraceFt/Signal.hpp>
#include <GraceFt/PenSet.h>
#include <GraceFt/BrushSet.h>
#include <GraceFt/TextSet.h>

namespace GFt {
    class Button : public Block {
        std::wstring text_;
        BrushSet brushSet_;
        TextSet textSet_;

    protected:
        void onDraw(const iRect& rect) override;
        void onMouseButtonPress(MouseButtonPressEvent* event) override;
        void onMouseButtonRelease(MouseButtonReleaseEvent* event) override;

    public:
        Button(const std::wstring& text, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        virtual ~Button();
        std::wstring& text();
        const std::wstring& text() const;
        BrushSet& brushSet();
        const BrushSet& brushSet() const;
        TextSet& textSet();
        const TextSet& textSet() const;
    
    public:
        Signal<bool> onStatusChanged;
        Signal<void> onClicked;
        Signal<void> onReleased;
    };
}