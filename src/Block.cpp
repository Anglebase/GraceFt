#include "Block.h"

#include <algorithm>
#include <ege.h>
#include <dwmapi.h>
#include <Geometry.hpp>

#include <Graphics.h>
#include <BlockFocus.h>
#include <Window.h>

#define DEF_MOUSE_HANDEL_FUNC(eventName)                                                \
    void Block::handleOn##eventName(eventName##Event* event, const iPoint& lefttop) {   \
        if (event->isPropagationStopped())                                              \
            return;                                                                     \
        auto iter = std::find_if(children_.begin(), children_.end(),                    \
            [&](const Block* child) {                                                   \
                return contains(iRect{                                                  \
                    child->absolutePosition(), child->rect().size()                          \
                    }, event->absolutePosition()); });                                  \
        do {                                                                            \
            if (iter == children_.end()){                                               \
                BlockHoverManager::setHoverOn(this);                                    \
                break;                                                                  \
            }                                                                           \
            if (!event->isPropagationStopped())                                         \
                (*iter)->handleOn##eventName(event, lefttop + this->rect().position()); \
        } while (false);                                                                \
        if (!event->isPropagationStopped())                                             \
            if (!this->hide_)                                                           \
                this->on##eventName(event);                                             \
    }
#define DEF_KEY_HANDEL_FUNC(eventName)                                                  \
    void Block::handleOn##eventName(eventName##Event* event) {                          \
        if (event->isPropagationStopped())                                              \
            return;                                                                     \
        if (!this->hide_)                                                               \
            this->on##eventName(event);                                                 \
        if (parent_ != nullptr)                                                         \
            parent_->handleOn##eventName(event);                                        \
    }

namespace GFt {
    using namespace ege;
    bool Block::CompareByZIndex::operator()(const Block* a, const Block* b) const {
        return a->zIndex_ > b->zIndex_;
    }
    /// @note 由于此函数会在每帧渲染时调用，因而应尽量避免过多的计算、创建和销毁临时对象，以提高效率。
    /// @note 渲染帧时长(可通过 Application::getRenderTime() 获取)最好控制在16ms以内，否则会引发较为明显的卡顿
    void Block::onDraw(Graphics& g) {}
    void Block::onMouseButtonPress(MouseButtonPressEvent* event) {
        // 默认行为: 受到点击捕获焦点
        BlockFocusManager::setFocusOn(this);
        if (event)
            event->stopPropagation();
    }
    void Block::onMouseButtonRelease(MouseButtonReleaseEvent* event) {}
    void Block::onMouseMove(MouseMoveEvent* event) {}
    void Block::onMouseWheel(MouseWheelEvent* event) {}
    void Block::onKeyPress(KeyPressEvent* event) {}
    void Block::onKeyRelease(KeyReleaseEvent* event) {}
    void Block::onTextInput(TextInputEvent* event) {}
    Block::Block(const iRect& rect, Block* parent, int zIndex) :GraphInterface(rect) {
        parent_ = parent;
        zIndex_ = zIndex;
        if (parent_ != nullptr)
            parent_->addChild(this);
    }
    Block::~Block() {}
    void Block::addChild(Block* child) {
        // 若为空指针则忽略
        if (child == nullptr)
            return;
        // 若已存在则忽略
        using Iter = std::multiset<Block*, CompareByZIndex>::iterator;
        Iter insert_iter = std::find_if(children_.begin(), children_.end(),
            [&](const Block* c) { return c == child; });
        if (insert_iter != children_.end())
            return;
        // 若该节点存在父节点则先从父节点移除
        if (child->parent_ != nullptr)
            child->parent_->removeChild(child);
        // 更新节点数据
        child->parent_ = this;
        children_.insert(child);
        // 引发元素重排
        this->sortChildren_ = false;
    }
    void Block::removeChild(Block* child) {
        // 若为空指针则忽略
        if (child == nullptr)
            return;
        // 若不存在则忽略
        using Iter = std::multiset<Block*, CompareByZIndex>::iterator;
        Iter remove_iter = std::find_if(children_.begin(), children_.end(),
            [&](const Block* c) { return c == child; });
        if (remove_iter == children_.end())
            return;
        // 移除节点
        children_.erase(remove_iter);
        child->parent_ = nullptr;
        // 引发元素重排
        this->sortChildren_ = false;
    }
    void Block::setZIndex(int zIndex) {
        zIndex_ = zIndex;
        if (parent_ != nullptr)
            parent_->sortChildren_ = false;
    }
    void Block::setParent(Block* parent) {
        if (parent == nullptr) {
            if (parent_ != nullptr) {
                parent_->children_.erase(this);
                parent_->sortChildren_ = false;
            }
            parent_ = nullptr;
            return;
        }
        if (parent_ != nullptr) {
            parent_->children_.erase(this);
            parent_->sortChildren_ = false;
        }
        parent_ = parent;
        parent_->children_.insert(this);
        parent_->sortChildren_ = false;
    }
    void Block::hide() {
        hide_ = true;
        ViewChanged(false);
        for (auto child : children_)
            child->hide();
    }
    void Block::show() {
        hide_ = false;
        ViewChanged(true);
        for (auto child : children_)
            child->show();
    }
    bool Block::isHide() const {
        return hide_;
    }
    int Block::getZIndex() const { return zIndex_; }
    Block* Block::getParent() const { return parent_; }

    iPoint Block::relativePosFrom(Block* block) const {
        return this->absolutePosition() - block->absolutePosition();
    }

    iPoint Block::absolutePosition() const {
        if (parent_ == nullptr) {
            RECT crect;
            GetClientRect(getHWnd(), &crect);
            POINT p = { crect.left, crect.top };
            ClientToScreen(getHWnd(), &p);
            return iPoint{ p.x, p.y };
        }
        return rect().position() + parent_->absolutePosition();
    }

    void Block::handleOnDraw(const iPoint& lefttop, bool cilpO) {
        static Graphics g;
        // 设置裁剪区域
        /// @bug 此函数应裁剪到自身的范围
        setviewport(lefttop.x(), lefttop.y(), lefttop.x() + rect().width(), lefttop.y() + rect().height(), 0);
        // 调用自身的绘制函数
        if (!this->hide_) {
            this->onDraw(g);
        }
        if (!sortChildren_) {
            // 元素重排
            std::multiset<Block*, CompareByZIndex> new_set;
            for (auto child : children_)
                new_set.insert(child);
            children_.swap(new_set);
            sortChildren_ = true;
        }
        // 调用子节点的绘制事件处理函数
        using Iter = std::reverse_iterator<std::multiset<GFt::Block*, GFt::Block::CompareByZIndex>::iterator>;
        for (Iter riter = children_.rbegin(); riter != children_.rend(); ++riter) {
            auto child = *riter;
            if (!cilpO || child->rect() & this->rect()) // 子节点与自身有交集才触发绘制
                child->handleOnDraw(lefttop + child->rect().position(), cilpO);
        }
    }
    /// @cond IGNORE
    DEF_MOUSE_HANDEL_FUNC(MouseButtonPress);
    DEF_MOUSE_HANDEL_FUNC(MouseButtonRelease);
    DEF_MOUSE_HANDEL_FUNC(MouseMove);
    DEF_MOUSE_HANDEL_FUNC(MouseWheel);

    DEF_KEY_HANDEL_FUNC(KeyPress);
    DEF_KEY_HANDEL_FUNC(KeyRelease);
    DEF_KEY_HANDEL_FUNC(TextInput);
    /// @endcond
}
