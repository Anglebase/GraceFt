#include "GraceFt/widget/CheckBox.h"

#include <GraceFt/BlockFocus.h>

namespace GFt {
    namespace Widget {
        using namespace GFt::literals;
        void CheckBox::onDraw(Graphics& g) {
            iRect r{ rect().size() };
            static BrushSet bkbs(0xffffff_rgb);
            g.bindBrushSet(&bkbs);
            g.drawFillRect(r);
            static TextSet ts(0_rgb);
            ts.font().setWeight(FontWeight::Bold);
            g.bindTextSet(&ts);
            auto w = g.textWidth(text_);
            auto h = g.textHeight(text_);
            ts.font().setWeight(FontWeight::Default);
            if (BlockHoverManager::getHoverOn() == this) {
                g.bindBrushSet(&hoverbs_);
                ts.font() = hoverfont_;
                ts.font().setWeight(isChecked() ? FontWeight::Bold : FontWeight::Normal);
                ts.font().setUnderline(true);
                g.bindTextSet(&ts);
            }
            else if (isChecked()) {
                g.bindBrushSet(&selectedbs_);
                ts.font() = selectedfont_;
                ts.font().setWeight(FontWeight::Bold);
                g.bindTextSet(&ts);
            }
            else {
                g.bindBrushSet(&normalbs_);
                ts.font() = normalfont_;
                g.bindTextSet(&ts);
            }
            iRect tr = r.centerby(iSize{ w + h, h });
            auto rect = iRect{ tr.position(), iSize{ h, h } };
            g.drawRect(rect);
            if (isChecked())
                g.drawFillRect(rect);
            iRect tr2{ tr.position() + iPoint{ h + 3, 0 }, iSize{ w, h } };
            g.drawText(text_, tr2, TextAlign::Center | TextAlign::Middle);
        }
        void CheckBox::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (e->button() == MouseButton::Left)
                setChecked(!isChecked());
            return Block::onMouseButtonPress(e);
        }
        CheckBox::CheckBox(const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex), text_(), checked_(false),
            hoverfont_(L"宋体"), normalfont_(L"宋体"), selectedfont_(L"宋体"),
            hoverbs_(0x999999_rgb), normalbs_(0x999999_rgb), selectedbs_(0x999999_rgb) {}

        CheckBox::~CheckBox() = default;

        void CheckBox::setChecked(bool checked) {
            if (isChecked() == checked) return;
            checked_ = checked;
            onCheckChanged(checked_);
            checked_ ? onChecked() : onUnchecked();
        }

        bool CheckBox::isChecked() const {
            return checked_;
        }

        std::wstring& CheckBox::text() { return text_; }
        Font& CheckBox::hoverFont() { return hoverfont_; }
        Font& CheckBox::normalFont() { return normalfont_; }
        Font& CheckBox::selectedFont() { return selectedfont_; }
        BrushSet& CheckBox::hoverBrush() { return hoverbs_; }
        BrushSet& CheckBox::normalBrush() { return normalbs_; }
        BrushSet& CheckBox::selectedBrush() { return selectedbs_; }

        const std::wstring& CheckBox::text() const { return text_; }
        const Font& CheckBox::hoverFont() const { return hoverfont_; }
        const Font& CheckBox::normalFont() const { return normalfont_; }
        const Font& CheckBox::selectedFont() const { return selectedfont_; }
        const BrushSet& CheckBox::hoverBrush() const { return hoverbs_; }
        const BrushSet& CheckBox::normalBrush() const { return normalbs_; }
        const BrushSet& CheckBox::selectedBrush() const { return selectedbs_; }
    }
}