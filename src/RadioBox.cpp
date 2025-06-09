#include "GraceFt/widget/RadioBox.h"

#include <GraceFt/BlockFocus.h>

namespace GFt {
    namespace Widget {
        using namespace GFt::literals;
        void RadioBox::onDraw(Graphics& g) {
            iRect r{ rect().size() };
            static BrushSet bkbs(0xffffff_rgb);
            g.bindBrushSet(&bkbs);
            g.drawFillRect(r);
            static TextSet ts(0_rgb);
            ts.font() = selectedfont_;
            ts.font().setWeight(FontWeight::Bold);
            g.bindTextSet(&ts);
            auto w = g.textWidth(text_);
            auto h = g.textHeight(text_);
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
            auto ellp = iEllipse{ iRect{tr.position(), iSize{ h, h }} };
            g.drawEllipse(ellp);
            if (isChecked())
                g.drawFillEllipse(ellp);
            iRect tr2{ tr.position() + iPoint{ h + 3, 0 }, iSize{ w, h } };
            g.drawText(text_, tr2, TextAlign::Center | TextAlign::Middle);
        }
        void RadioBox::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (e->button() == MouseButton::Left)
                setChecked(true);
            return Block::onMouseButtonPress(e);
        }
        RadioBox::RadioBox(GFt::RadioManager& manager, const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex), manager_(manager), text_(),
            hoverfont_(L"宋体"), normalfont_(L"宋体"), selectedfont_(L"宋体"),
            hoverbs_(0x999999_rgb), normalbs_(0x999999_rgb), selectedbs_(0x999999_rgb) {}

        RadioBox::~RadioBox() = default;

        void RadioBox::setChecked(bool checked) {
            if (isChecked() == checked) return;
            manager_.setRadioBox(checked ? this : nullptr);
        }

        bool RadioBox::isChecked() const {
            return manager_.getRadioBox() == this;
        }

        std::wstring& RadioBox::text() { return text_; }
        Font& RadioBox::hoverFont() { return hoverfont_; }
        Font& RadioBox::normalFont() { return normalfont_; }
        Font& RadioBox::selectedFont() { return selectedfont_; }
        BrushSet& RadioBox::hoverBrush() { return hoverbs_; }
        BrushSet& RadioBox::normalBrush() { return normalbs_; }
        BrushSet& RadioBox::selectedBrush() { return selectedbs_; }

        const std::wstring& RadioBox::text() const { return text_; }
        const Font& RadioBox::hoverFont() const { return hoverfont_; }
        const Font& RadioBox::normalFont() const { return normalfont_; }
        const Font& RadioBox::selectedFont() const { return selectedfont_; }
        const BrushSet& RadioBox::hoverBrush() const { return hoverbs_; }
        const BrushSet& RadioBox::normalBrush() const { return normalbs_; }
        const BrushSet& RadioBox::selectedBrush() const { return selectedbs_; }
    }
    RadioManager::RadioManager() : radiobox_(nullptr) {}
    RadioManager::~RadioManager() = default;
    void RadioManager::setRadioBox(Widget::RadioBox* radiobox) {
        if (radiobox_ == radiobox) return;
        if (radiobox_) {
            radiobox_->onUnchecked();
            radiobox_->onCheckChanged(false);
        }
        radiobox_ = radiobox;
        if (radiobox_) {
            radiobox_->onChecked();
            radiobox_->onCheckChanged(true);
        }
    }
    Widget::RadioBox* RadioManager::getRadioBox() const {
        return radiobox_;
    }
}