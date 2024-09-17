#pragma once

#include <GraceFt/Block.h>
#include <GraceFt/Signal.hpp>
#include <GraceFt/PenSet.h>
#include <GraceFt/BrushSet.h>
#include <GraceFt/TextSet.h>

namespace GFt {
    namespace Widget {
        class Button : public Block {
            std::wstring text_;
            bool disabled_{ false };

            BrushSet brushSet_;
            TextSet textSet_;

            Color textColor_{ 0x00, 0x00, 0x00, 0xFF };
            Color backgroundColor_{ 0xE5, 0xE5, 0xE5, 0xFF };
            Color hoverColor_{ 0xC6, 0xC6, 0xC6, 0xFF };
            Color pressedColor_{ 0xB7, 0xB7, 0xB7, 0xFF };
            Color disabledColor_{ 0x99, 0x99, 0x99, 0xFF };

        protected:
            void onDraw(const iRect& rect) override;
            void onMouseButtonPress(MouseButtonPressEvent* event) override;
            void onMouseButtonRelease(MouseButtonReleaseEvent* event) override;

        public:
            Button(const std::wstring& text, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            virtual ~Button();
            std::wstring& text();
            Color& textColor();
            Color& backgroundColor();
            Color& hoverColor();
            Color& pressedColor();
            Color& disabledColor();

            const std::wstring& text() const;
            const Color& textColor() const;
            const Color& backgroundColor() const;
            const Color& hoverColor() const;
            const Color& pressedColor() const;
            const Color& disabledColor() const;

            void setEnable(bool disabled);
            bool isDisabled() const;

        public:
            Signal<bool> onStatusChanged;
            Signal<void> onClicked;
            Signal<void> onReleased;
        };
    }
}