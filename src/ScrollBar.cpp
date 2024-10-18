#include "widget/ScrollBar.h"
#include <Geometry.hpp>
#include <Application.h>
#include <System.h>

namespace GFt {
    namespace Widget {
        void VScrollBar::onDraw(Graphics& g) {
            brushSet_.setFillStyle(backgroundColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillRect({ rect().size() });
            brushSet_.setFillStyle(barColor_);
            g.bindBrushSet(&brushSet_);
            auto k = rect().size().height() / completeSize_;
            auto t = currentPos_ * k;
            auto h = visibleSize_ * k;
            auto r = fRect{ 0, t, (float)rect().size().width(), h };
            g.drawFillRect(r);
            penSet_.setColor(barBorderColor_);
            g.bindPenSet(&penSet_);
            g.drawRect(r);
        }

        void VScrollBar::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (!e || e->button() != MouseButton::Left)
                return Block::onMouseButtonPress(e);
            auto k = rect().size().height() / completeSize_;
            auto t = currentPos_ * k;
            auto h = visibleSize_ * k;
            auto r = fRect{ 0, t, (float)rect().size().width(), h };
            r.position() += this->absolutePosition();
            bPos_ = e->absolutePosition();
            y_ = currentPos_;
            if (contains(r, (fPoint)bPos_)) {
                ssid = Application::onEventCall.connect([&, k] {
                    auto y = Sys::getCursorPosition().y() - bPos_.y();
                    setPosition(y_ + y / k);
                    if (!(Sys::getAsyncKeyState(Key::LeftMouse) & 0x8000))
                        Application::onEventCall.disconnect(ssid);
                    });
            }
            else {
                auto by = e->absolutePosition().y() - this->absolutePosition().y()
                    - 0.5f * r.size().height();
                setPosition(by / k);
            }
            return Block::onMouseButtonPress(e);
        }
        void VScrollBar::onMouseWheel(MouseWheelEvent* e) {
            if (!e || e->wheel() == MouseWheel::None)
                return Block::onMouseWheel(e);
            switch (e->wheel()) {
            case MouseWheel::Up:
                setPosition(currentPos_ - step_);
                break;
            case MouseWheel::Down:
                setPosition(currentPos_ + step_);
                break;
            }
            return Block::onMouseWheel(e);
        }

        VScrollBar::VScrollBar(const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex) {
            completeSize_ = rect.size().height();
            visibleSize_ = rect.size().height();
            currentPos_ = 0.0f;
        }
        void VScrollBar::setPosition(float pos) {
            if (pos < 0.0f)
                pos = 0.0f;
            if (pos > completeSize_ - visibleSize_)
                pos = completeSize_ - visibleSize_;
            if (pos == currentPos_)
                return;
            currentPos_ = pos;
            onCurrentPosChanged(currentPos_);
        }
        float VScrollBar::getPosition() const {
            return currentPos_;
        }
        void VScrollBar::setCompleteSize(float size) {
            if (size < visibleSize_)
                size = visibleSize_;
            if (size == completeSize_)
                return;
            completeSize_ = size;
        }
        float VScrollBar::getCompleteSize() const {
            return completeSize_;
        }
        void VScrollBar::setVisibleSize(float size) {
            if (size > completeSize_)
                size = completeSize_;
            if (size == visibleSize_)
                return;
            visibleSize_ = size;
        }
        float VScrollBar::getVisibleSize() const {
            return visibleSize_;
        }
        void VScrollBar::setStep(float step) { step_ = step; }
        float VScrollBar::getStep() const { return step_; }
        Color& VScrollBar::backgroundColor() { return backgroundColor_; }
        Color& VScrollBar::barColor() { return barColor_; }
        Color& VScrollBar::barBorderColor() { return barBorderColor_; }

        const Color& VScrollBar::backgroundColor() const { return backgroundColor_; }
        const Color& VScrollBar::barColor() const { return barColor_; }
        const Color& VScrollBar::barBorderColor() const { return barBorderColor_; }

        HScrollBar::HScrollBar(const iRect& rect, Block* parent, int zIndex)
            : Block(rect, parent, zIndex) {
            completeSize_ = rect.size().width();
            visibleSize_ = rect.size().width();
            currentPos_ = 0.0f;
        }
        void HScrollBar::onDraw(Graphics& g) {
            brushSet_.setFillStyle(backgroundColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillRect({ rect().size() });
            brushSet_.setFillStyle(barColor_);
            g.bindBrushSet(&brushSet_);
            auto k = rect().size().width() / completeSize_;
            auto t = currentPos_ * k;
            auto w = visibleSize_ * k;
            auto r = fRect{ t, 0, w, (float)rect().size().height() };
            g.drawFillRect(r);
            penSet_.setColor(barBorderColor_);
            g.bindPenSet(&penSet_);
            g.drawRect(r);
        }
        void HScrollBar::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (!e || e->button() != MouseButton::Left)
                return Block::onMouseButtonPress(e);
            auto k = rect().size().width() / completeSize_;
            auto t = currentPos_ * k;
            auto w = visibleSize_ * k;
            auto r = fRect{ t, 0, w, (float)rect().size().height() };
            r.position() += this->absolutePosition();
            bPos_ = e->absolutePosition();
            x_ = currentPos_;
            if (contains(r, (fPoint)bPos_)) {
                ssid = Application::onEventCall.connect([&, k] {
                    auto x = Sys::getCursorPosition().x() - bPos_.x();
                    setPosition(x_ + x / k);
                    if (!(Sys::getAsyncKeyState(Key::LeftMouse) & 0x8000))
                        Application::onEventCall.disconnect(ssid);
                    });
            }
            else {
                auto bx = e->absolutePosition().x() - this->absolutePosition().x()
                    - 0.5f * r.size().width();
                setPosition(bx / k);
            }
            return Block::onMouseButtonPress(e);
        }
        void HScrollBar::onMouseWheel(MouseWheelEvent* e) {
            if (!e || e->wheel() == MouseWheel::None)
                return Block::onMouseWheel(e);
            if (!(Sys::getAsyncKeyState(Key::LeftShift) & 0x8000) &&
                !(Sys::getAsyncKeyState(Key::RightShift) & 0x8000))
                return Block::onMouseWheel(e);
            switch (e->wheel()) {
            case MouseWheel::Up:
                setPosition(currentPos_ - step_);
                break;
            case MouseWheel::Down:
                setPosition(currentPos_ + step_);
                break;
            }
            return Block::onMouseWheel(e);
        }
        void HScrollBar::setPosition(float pos) {
            if (pos < 0.0f)
                pos = 0.0f;
            if (pos > completeSize_ - visibleSize_)
                pos = completeSize_ - visibleSize_;
            if (pos == currentPos_)
                return;
            currentPos_ = pos;
            onCurrentPosChanged(currentPos_);
        }
        float HScrollBar::getPosition() const {
            return currentPos_;
        }
        void HScrollBar::setCompleteSize(float size) {
            if (size < visibleSize_)
                size = visibleSize_;
            if (size == completeSize_)
                return;
            completeSize_ = size;
        }
        float HScrollBar::getCompleteSize() const {
            return completeSize_;
        }
        void HScrollBar::setVisibleSize(float size) {
            if (size > completeSize_)
                size = completeSize_;
            if (size == visibleSize_)
                return;
            visibleSize_ = size;
        }
        float HScrollBar::getVisibleSize() const {
            return visibleSize_;
        }
        void HScrollBar::setStep(float step) { step_ = step; }
        float HScrollBar::getStep() const { return step_; }
        Color& HScrollBar::backgroundColor() { return backgroundColor_; }
        Color& HScrollBar::barColor() { return barColor_; }
        Color& HScrollBar::barBorderColor() { return barBorderColor_; }

        const Color& HScrollBar::backgroundColor() const { return backgroundColor_; }
        const Color& HScrollBar::barColor() const { return barColor_; }
        const Color& HScrollBar::barBorderColor() const { return barBorderColor_; }
    }
}