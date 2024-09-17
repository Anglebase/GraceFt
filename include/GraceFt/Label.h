#pragma once

#include <Block.h>
#include <Graphics.h>

namespace GFt {
    namespace Widget {
        class Label : public Block {
            std::wstring text_;

            BrushSet brushSet_;
            TextSet textSet_;

            int leftPadding_{ 3 };
            int rightPadding_{ 3 };
            int topPadding_{ 3 };
            int bottomPadding_{ 3 };
            int textAlignment_{ TextAlign::Left | TextAlign::Middle };

        protected:
            void onDraw(const iRect& rect) override;
            void onMouseButtonPress(MouseButtonPressEvent* event) override;

        public:
            Label(const std::wstring& text, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~Label() override = default;

            std::wstring& text();
            BrushSet& brushSet();
            TextSet& textSet();
            int& leftPadding();
            int& rightPadding();
            int& topPadding();
            int& bottomPadding();
            int& textAlignment();

            const std::wstring& text() const;
            const BrushSet& brushSet() const;
            const TextSet& textSet() const;
            int leftPadding() const;
            int rightPadding() const;
            int topPadding() const;
            int bottomPadding() const;
            int textAlignment() const;

            void setPadding(int padding);
            void setPadding(int leftRight, int topBottom);
            void setPadding(int left, int right, int top, int bottom);
        };
    }
}