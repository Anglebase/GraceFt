#include "GraceFt/GraphInterface.h"

namespace GFt {
    GraphInterface::GraphInterface(iRect rect) :rect_(rect) {}
    GraphInterface::~GraphInterface() {}
    void GraphInterface::setX(int x) {
        if (x == rect_.x()) return;
        rect_.x() = x;
        onPositionChanged(rect_.position());
    }
    void GraphInterface::setY(int y) {
        if (y == rect_.y()) return;
        rect_.y() = y;
        onPositionChanged(rect_.position());
    }
    void GraphInterface::setWidth(int width) {
        if (width == rect_.width()) return;
        rect_.width() = width;
        onSizeChanged(rect_.size());
    }
    void GraphInterface::setHeight(int height) {
        if (height == rect_.height()) return;
        rect_.height() = height;
        onSizeChanged(rect_.size());
    }
    void GraphInterface::setPosition(const iPoint& pos) {
        if (pos == rect_.position()) return;
        rect_.position() = pos;
        onPositionChanged(pos);
    }
    void GraphInterface::setSize(const iSize& size) {
        if (size == rect_.size()) return;
        rect_.size() = size;
        onSizeChanged(size);
    }
    void GraphInterface::setRect(const iRect& rect) {
        setPosition(rect.position());
        setSize(rect.size());
    }
    const iRect& GraphInterface::rect() const {
        return rect_;
    }
}