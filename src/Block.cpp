#include "Block.h"

#include <algorithm>
#include <ege.h>
#include <dwmapi.h>
#include <Geometry.hpp>

#include <Graphics.h>
#include <BlockFocus.h>

#define DEF_MOUSE_HANDEL_FUNC(eventName)                                                              \
    void Block::handleOn##eventName(const eventName##Event& event, const iPoint& lefttop) {           \
        if (event.isPropagationStopped())                                                             \
            return;                                                                                   \
        auto iter = std::find_if(children_.begin(), children_.end(),                                  \
            [&](const Block* child) { return contains(child->rect(), event.position() - lefttop); }); \
        do {                                                                                          \
            if (iter == children_.end()) break;                                                       \
            if (!event.isPropagationStopped())                                                        \
                (*iter)->handleOn##eventName(event, lefttop + this->rect().position());               \
        } while (false);                                                                              \
        if (!event.isPropagationStopped())                                                            \
            this->on##eventName(event);                                                               \
    }
#define DEF_KEY_HANDEL_FUNC(eventName)                                                    \
    void Block::handleOn##eventName(const eventName##Event& event) {                      \
        if (event.isPropagationStopped())                                                 \
            return;                                                                       \
        this->on##eventName(event);                                                       \
        if (parent_ != nullptr)                                                           \
            parent_->handleOn##eventName(event);                                          \
    }

namespace GFt {
    using namespace ege;
    bool Block::CompareByZIndex::operator()(const Block* a, const Block* b) const {
        return a->zIndex_ > b->zIndex_;
    }
    void Block::onDraw(const iRect& rect) {}
    void Block::onMouseButtonPress(const MouseButtonPressEvent& event) {
        // 默认行为: 受到点击捕获焦点
        BlockFocusManager::setFocusOn(this);
        event.stopPropagation();
    }
    void Block::onMouseButtonRelease(const MouseButtonReleaseEvent& event) {}
    void Block::onMouseMove(const MouseMoveEvent& event) {}
    void Block::onMouseWheel(const MouseWheelEvent& event) {}
    void Block::onKeyPress(const KeyPressEvent& event) {}
    void Block::onKeyRelease(const KeyReleaseEvent& event) {}
    void Block::onTextInput(const TextInputEvent& event) {}
    Block::Block(const iRect& rect, Block* parent, int zIndex) :GraphInterface(rect) {
        parent_ = parent;
        zIndex_ = zIndex;
        if (parent_ != nullptr)
            parent_->children_.insert(this);
    }
    Block::~Block() {}
    void Block::addChild(Block* child) {
        if (child == nullptr)
            return;
        if (child->parent_ != nullptr)
            child->parent_->children_.erase(child);
        child->parent_ = this;
        children_.insert(child);
    }
    void Block::removeChild(Block* child) {
        if (child == nullptr)
            return;
        children_.erase(child);
        child->parent_ = nullptr;
    }
    void Block::setZIndex(int zIndex) {
        if (parent_ == nullptr) {
            zIndex_ = zIndex;
            return;
        }
        parent_->children_.erase(this);
        zIndex_ = zIndex;
        parent_->children_.insert(this);
    }
    void Block::setParent(Block* parent) {
        if (parent == nullptr) {
            if (parent_ != nullptr)
                parent_->children_.erase(this);
            parent_ = nullptr;
            return;
        }
        if (parent_ != nullptr)
            parent_->children_.erase(this);
        parent_ = parent;
        parent_->children_.insert(this);
    }
    int Block::getZIndex() const { return zIndex_; }
    Block* Block::getParent() const { return parent_; }

    iPoint Block::relativePosFrom(Block* block) const {
        return this->absolutePos() - block->absolutePos();
    }

    iPoint Block::absolutePos() const {
        if (parent_ == nullptr) {
            RECT crect;
            GetClientRect(getHWnd(), &crect);
            POINT p = { crect.left, crect.top };
            ClientToScreen(getHWnd(), &p);
            return iPoint{ p.x, p.y };
        }
        return rect().position() + parent_->absolutePos();
    }

    void Block::handleOnDraw() {
        int left, top, right, bottom;
        getviewport(&left, &top, &right, &bottom);
        int x = rect().x(), y = rect().y(), width = rect().width(), height = rect().height();
        setviewport(x + left, y + top, x + left + width, y + top + height);
        this->onDraw(iRect{ x + left, y + top, width, height });
        using Iter = std::reverse_iterator<std::multiset<GFt::Block*, GFt::Block::CompareByZIndex>::iterator>;
        for (Iter riter = children_.rbegin(); riter != children_.rend(); ++riter) {
            auto child = *riter;
            if (child->rect() & this->rect())
                child->handleOnDraw();
        }
        setviewport(left, top, right, bottom);
    }
    DEF_MOUSE_HANDEL_FUNC(MouseButtonPress);
    DEF_MOUSE_HANDEL_FUNC(MouseButtonRelease);
    DEF_MOUSE_HANDEL_FUNC(MouseMove);
    DEF_MOUSE_HANDEL_FUNC(MouseWheel);

    DEF_KEY_HANDEL_FUNC(KeyPress);
    DEF_KEY_HANDEL_FUNC(KeyRelease);
    DEF_KEY_HANDEL_FUNC(TextInput);
}
