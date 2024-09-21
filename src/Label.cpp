#include "Label.h"

namespace GFt {
    namespace Widget {
        using namespace GFt::literals;
        void Label::onDraw(const iRect& rect) {
            Graphics g;
            g.bindBrushSet(&brushSet_);
            g.bindTextSet(&textSet_);
            iRect r = iRect{
                iPoint{leftPadding_, topPadding_},
                iSize{rect.size().width() - leftPadding_ - rightPadding_,
                      rect.size().height() - topPadding_ - bottomPadding_} };
            g.drawFillRect(r);
            g.drawText(text_, r, textAlignment_);
        }

        void Label::onMouseButtonPress(MouseButtonPressEvent* event) {}

        Label::Label(const std::wstring& text, const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex), text_(text), brushSet_(0x0_rgba), textSet_(0x0_rgb) {}

        Label::Label(const iRect& rect, Block* parent, int zIndex) 
            : Label(L"", rect, parent, zIndex) {}

        std::wstring& Label::text() { return text_; }
        BrushSet& Label::brushSet() { return brushSet_; }
        TextSet& Label::textSet() { return textSet_; }
        int& Label::leftPadding() { return leftPadding_; }
        int& Label::topPadding() { return topPadding_; }
        int& Label::rightPadding() { return rightPadding_; }
        int& Label::bottomPadding() { return bottomPadding_; }
        int& Label::textAlignment() { return textAlignment_; }

        const std::wstring& Label::text() const { return text_; }
        const BrushSet& Label::brushSet() const { return brushSet_; }
        const TextSet& Label::textSet() const { return textSet_; }
        int Label::leftPadding() const { return leftPadding_; }
        int Label::topPadding() const { return topPadding_; }
        int Label::rightPadding() const { return rightPadding_; }
        int Label::bottomPadding() const { return bottomPadding_; }
        int Label::textAlignment() const { return textAlignment_; }

        void Label::setPadding(int padding) {
            leftPadding_ = padding;
            topPadding_ = padding;
            rightPadding_ = padding;
            bottomPadding_ = padding;
        }
        void Label::setPadding(int leftRight, int topBottom) {
            leftPadding_ = leftRight;
            topPadding_ = topBottom;
            rightPadding_ = leftRight;
            bottomPadding_ = topBottom;
        }
        void Label::setPadding(int left, int right, int top, int bottom) {
            leftPadding_ = left;
            topPadding_ = top;
            rightPadding_ = right;
            bottomPadding_ = bottom;
        }
    }
}