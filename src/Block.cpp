#include "Block.h"

#include <algorithm>
#include <ege.h>
#include <Geometry.hpp>

#define DEF_MOUSE_HANDEL_FUNC(eventName)                                                  \
    void Block::handleOn##eventName(const eventName##Event& event) {                      \
        auto iter = std::find_if(children_.rbegin(), children_.rend(),                    \
            [&](const Block* child) {return contains(child->rect(), event.position());}); \
        if (iter == children_.rend())                                                     \
            return;                                                                       \
        (*iter)->handleOn##eventName(event);                                              \
        this->on##eventName(event);                                                       \
    }
#define DEF_KEY_HANDEL_FUNC(eventName)                                                    \
    void Block::handleOn##eventName(const eventName##Event& event) {                      \
        this->on##eventName(event);                                                       \
        if (parent_ != nullptr)                                                           \
            parent_->handleOn##eventName(event);                                          \
    }

namespace GFt {
    using namespace ege;
    bool Block::CompareByZIndex::operator()(const Block* a, const Block* b) const {
        return a->zIndex_ < b->zIndex_;
    }
    void Block::onDraw(const iRect& rect) {}
    void Block::onMouseButtonPress(const MouseButtonPressEvent& event) {}
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

    void Block::handleOnDraw(Block* block) {
        int left, top, right, bottom;
        getviewport(&left, &top, &right, &bottom);
        int x = rect().x(), y = rect().y();
        setviewport(x + left, y + top, x + right, y + bottom);
        this->onDraw(this->rect());
        for (auto child : block->children_)
            if (child->rect() & this->rect())
                child->handleOnDraw(this);
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
