#include "ColumnLayout.h"

namespace GFt {
    void ColumnLayout::updateLayout() {
        // 计算所有block的高度占比之和
        float sum = 0.0f;
        for (auto& [block, heightPro] : blockLayout_)
            sum += heightPro;
        // 计算可供分配的高度
        auto availableHeight =
            rect().height() -
            (space_ * (blockLayout_.size() - 1)) -
            (getTopPadding() + getBottomPadding());
        for (auto& [block, heightPro] : blockLayout_)
            availableHeight -= !heightPro > 0.f ? block->rect().height() : 0.f;
        // 计算每个block的高度、高度、y坐标
        for (auto& [block, heightPro] : blockLayout_) {
            if (heightPro > 0.f)
                block->rect().height() = (heightPro / sum) * availableHeight;
            block->rect().width() = rect().width() - (getLeftPadding() + getRightPadding());
            block->rect().x() = getLeftPadding();
        }
        // 计算每个block的x坐标
        float y = rect().bottom() - getBottomPadding();
        for (auto& [block, heightPro] : blockLayout_) {
            block->rect().y() = y - block->rect().height();
            y -= block->rect().height() + space_;
        }
        for (auto& [block, heightPro] : blockLayout_)
            block->rect().y() -= y;
        setShouldUpdateLayout(false);
    }

    void GFt::ColumnLayout::onDraw(const iRect& rect) {
        if (shouldUpdateLayout())
            updateLayout();
        return Block::onDraw(rect);
    }
    ColumnLayout::ColumnLayout(const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex) {}
    ColumnLayout::~ColumnLayout() = default;

    void ColumnLayout::addItem(Block* block, float widthProportion) {
        blockLayout_[block] = widthProportion;
        this->addChild(block);
        setShouldUpdateLayout();
    }
    void ColumnLayout::removeItem(Block* block) {
        if (blockLayout_.find(block) == blockLayout_.end())
            return;
        blockLayout_.erase(block);
        this->removeChild(block);
        setShouldUpdateLayout();
    }
    void ColumnLayout::setSpace(int space) {
        space_ = space;
        setShouldUpdateLayout();
    }
    int ColumnLayout::getSpace() const {
        return space_;
    }
}
