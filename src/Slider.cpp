#include "GraceFt/widget/Slider.h"
#include <GraceFt/Application.h>
#include <GraceFt/System.h>

namespace GFt {
    namespace Widget {
        void HSlider::onDraw(Graphics& g) {
            auto it = iRect{ rect().size() };
            auto ypos = it.center().y();
            auto xais = handleThickness_ / 2;
            auto p1 = iPoint{ it.x() + xais, ypos };
            auto p2 = iPoint{ it.right() - xais, ypos };
            auto xpos = (value_ - minValue_) / (maxValue_ - minValue_) * (p2 - p1).x() + p1.x();
            handlePos_ = fPoint{ xpos, (float)ypos };

            brushSet_.setFillStyle(backgroundColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillRect(it);
            penSet_.setLineWidth(handleThickness_);
            penSet_.setCapStyle(CapStyle::Round);
            if (!showDiff_) {
                penSet_.setColor(foregroundColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ p1,p2 });
            }
            else {
                penSet_.setColor(reverse_ ? foregroundColor_ : handleColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ p1,handlePos_ });
                penSet_.setColor(reverse_ ? handleColor_ : foregroundColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ handlePos_,p2 });
            }
            brushSet_.setFillStyle(handleColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillCircle({ handlePos_, (float)handleRadius_ });
        }
        void HSlider::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (e->button() != MouseButton::Left)
                return Block::onMouseButtonPress(e);
            auto rel = e->absolutePosition() - this->absolutePosition();
            if ((rel - handlePos_).norm() <= handleRadius_) {
                ssid = Application::onEventCall.connect([&] {
                    auto rel = Application::getAbsoluteMousePosition() - this->absolutePosition();
                    auto it = iRect{ rect().size() };
                    auto ypos = it.center().y();
                    auto xais = handleThickness_ / 2;
                    auto p1 = iPoint{ it.x() + xais, ypos };
                    auto p2 = iPoint{ it.right() - xais, ypos };
                    auto newvalue = (rel.x() - p1.x()) * 1.f / (p2.x() - p1.x()) * (maxValue_ - minValue_) + minValue_;
                    setValue(newvalue);
                    if (!(Sys::getAsyncKeyState(Key::LeftMouse) & 0x8000))
                        Application::onEventCall.disconnect(ssid);
                    });
            }
            else if (std::abs(rel.y() - handlePos_.y()) <= rect().size().height() / 2) {
                auto it = iRect{ rect().size() };
                auto ypos = it.center().y();
                auto xais = handleThickness_ / 2;
                auto p1 = iPoint{ it.x() + xais, ypos };
                auto p2 = iPoint{ it.right() - xais, ypos };
                auto newvalue = (rel.x() - p1.x()) * 1.f / (p2.x() - p1.x()) * (maxValue_ - minValue_) + minValue_;
                setValue(newvalue);
            }
            return Block::onMouseButtonPress(e);
        }

        HSlider::HSlider(const iRect& rect, Block* parent, int zIndex)
            :Block(rect, parent, zIndex) {}

        void HSlider::setRange(float minValue, float maxValue, float step) {
            minValue_ = minValue;
            maxValue_ = maxValue;
            step_ = step;
        }

        void HSlider::setValue(float value) {
            value = std::round((value - minValue_) / step_) * step_ + minValue_;
            if (value <= minValue_)
                value = minValue_;
            if (value >= maxValue_)
                value = maxValue_;
            if (std::abs(value - value_) < step_ / 2)
                return;
            value_ = value;
            onValueChanged(value_);
        }

        float HSlider::getValue() const { return value_; }

        Color& HSlider::backgroundColor() { return backgroundColor_; }
        Color& HSlider::foregroundColor() { return foregroundColor_; }
        Color& HSlider::handleColor() { return handleColor_; }
        int& HSlider::handleRadius() { return handleRadius_; }
        int& HSlider::handleThickness() { return handleThickness_; }
        void HSlider::setShowDiff(bool showDiff) { showDiff_ = showDiff; }
        void HSlider::setReverse(bool reverse) { reverse_ = reverse; }

        const Color& HSlider::backgroundColor() const { return backgroundColor_; }
        const Color& HSlider::foregroundColor() const { return foregroundColor_; }
        const Color& HSlider::handleColor() const { return handleColor_; }
        int HSlider::handleRadius() const { return handleRadius_; }
        int HSlider::handleThickness() const { return handleThickness_; }
        bool HSlider::isShowDiff() const { return showDiff_; }
        bool HSlider::isReverse() const { return reverse_; }

        void VSlider::onDraw(Graphics& g) {
            auto it = iRect{ rect().size() };
            auto xpos = it.center().x();
            auto yais = handleThickness_ / 2;
            auto p1 = iPoint{ xpos, it.y() + yais };
            auto p2 = iPoint{ xpos, it.bottom() - yais };
            auto ypos = (value_ - minValue_) / (maxValue_ - minValue_) * (p2 - p1).y() + p1.y();
            handlePos_ = fPoint{ (float)xpos, ypos };

            brushSet_.setFillStyle(backgroundColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillRect(it);
            penSet_.setLineWidth(handleThickness_);
            penSet_.setCapStyle(CapStyle::Round);
            if (!showDiff_) {
                penSet_.setColor(foregroundColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ p1,p2 });
            }
            else {
                penSet_.setColor(reverse_ ? foregroundColor_ : handleColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ p1,handlePos_ });
                penSet_.setColor(reverse_ ? handleColor_ : foregroundColor_);
                g.bindPenSet(&penSet_);
                g.drawLine({ handlePos_,p2 });
            }
            brushSet_.setFillStyle(handleColor_);
            g.bindBrushSet(&brushSet_);
            g.drawFillCircle({ handlePos_, (float)handleRadius_ });
        }
        void VSlider::onMouseButtonPress(MouseButtonPressEvent* e) {
            if (e->button() != MouseButton::Left)
                return Block::onMouseButtonPress(e);
            auto rel = e->absolutePosition() - this->absolutePosition();
            if ((rel - handlePos_).norm() <= handleRadius_) {
                ssid = Application::onEventCall.connect([&] {
                    auto rel = Application::getAbsoluteMousePosition() - this->absolutePosition();
                    auto it = iRect{ rect().size() };
                    auto xpos = it.center().x();
                    auto yais = handleThickness_ / 2;
                    auto p1 = iPoint{ xpos, it.y() + yais };
                    auto p2 = iPoint{ xpos, it.bottom() - yais };
                    auto newvalue = (rel.y() - p1.y()) * 1.f / (p2.y() - p1.y()) * (maxValue_ - minValue_) + minValue_;
                    setValue(newvalue);
                    if (!(Sys::getAsyncKeyState(Key::LeftMouse) & 0x8000))
                        Application::onEventCall.disconnect(ssid);
                    });
            }
            else if (std::abs(rel.x() - handlePos_.x()) <= rect().size().width() / 2) {
                auto it = iRect{ rect().size() };
                auto xpos = it.center().x();
                auto yais = handleThickness_ / 2;
                auto p1 = iPoint{ xpos, it.y() + yais };
                auto p2 = iPoint{ xpos, it.bottom() - yais };
                auto newvalue = (rel.y() - p1.y()) * 1.f / (p2.y() - p1.y()) * (maxValue_ - minValue_) + minValue_;
                setValue(newvalue);
            }
            return Block::onMouseButtonPress(e);
        }

        Widget::VSlider::VSlider(const iRect& rect, Block* parent, int zIndex)
            :Block(rect, parent, zIndex) {}
        void VSlider::setRange(float minValue, float maxValue, float step) {
            minValue_ = minValue;
            maxValue_ = maxValue;
            step_ = step;
        }
        void VSlider::setValue(float value) {
            value = std::round((value - minValue_) / step_) * step_ + minValue_;
            if (value <= minValue_)
                value = minValue_;
            if (value >= maxValue_)
                value = maxValue_;
            if (std::abs(value - value_) < step_ / 2)
                return;
            value_ = value;
            onValueChanged(value_);
        }

        float VSlider::getValue() const { return value_; }

        Color& VSlider::backgroundColor() { return backgroundColor_; }
        Color& VSlider::foregroundColor() { return foregroundColor_; }
        Color& VSlider::handleColor() { return handleColor_; }
        int& VSlider::handleRadius() { return handleRadius_; }
        int& VSlider::handleThickness() { return handleThickness_; }
        void VSlider::setShowDiff(bool showDiff) { showDiff_ = showDiff; }
        void VSlider::setReverse(bool reverse) { reverse_ = reverse; }

        const Color& VSlider::backgroundColor() const { return backgroundColor_; }
        const Color& VSlider::foregroundColor() const { return foregroundColor_; }
        const Color& VSlider::handleColor() const { return handleColor_; }
        int VSlider::handleRadius() const { return handleRadius_; }
        int VSlider::handleThickness() const { return handleThickness_; }
        bool VSlider::isShowDiff() const { return showDiff_; }
        bool VSlider::isReverse() const { return reverse_; }
    }
}

