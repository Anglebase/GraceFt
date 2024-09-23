#include "RowLayout.h"

namespace GFt {
    void RowLayout::updateLayout() {
        // 计算所有block的宽度占比之和
        float sum = 0.0f;
        for (auto& [block, widthPro] : blockLayout_)
            sum += widthPro > 0.f ? widthPro : 0.f;
        // 计算可供分配的宽度
        auto availableWidth =
            rect().width() -
            (space_ * (blockLayout_.size() - 1)) -
            (getLeftPadding() + getRightPadding());
        for (auto& [block, widthPro] : blockLayout_)
            availableWidth -= widthPro <= 0.f ? block->rect().width() : 0.f;
        // 计算每个block的宽度、高度、y坐标
        for (auto& [block, widthPro] : blockLayout_) {
            if (widthPro > 0.f)
                block->rect().width() = (widthPro / sum) * availableWidth;
            block->rect().height() = rect().height() - (getTopPadding() + getBottomPadding());
            block->rect().y() = getTopPadding();
        }
        // 计算每个block的x坐标
        float x = rect().right() - getRightPadding();
        for (auto& [block, widthPro] : blockLayout_) {
            block->rect().x() = x - block->rect().width();
            x -= block->rect().width() + space_;
        }
        for (auto& [block, widthPro] : blockLayout_)
            block->rect().x() -= x;
        setShouldUpdateLayout(false);
    }

    void RowLayout::onDraw(const iRect& rect) {
        if (shouldUpdateLayout())
            updateLayout();
        return Block::onDraw(rect);
    }

    RowLayout::RowLayout(const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex) {}
    RowLayout::~RowLayout() = default;
    void RowLayout::addItem(Block* block, float widthProportion) {
        blockLayout_[block] = widthProportion;
        this->addChild(block);
        setShouldUpdateLayout();
    }
    void RowLayout::removeItem(Block* block) {
        if (blockLayout_.find(block) == blockLayout_.end())
            return;
        blockLayout_.erase(block);
        this->removeChild(block);
        setShouldUpdateLayout();
    }
    void RowLayout::setSpace(int space) {
        space_ = space;
        setShouldUpdateLayout();
    }
    int RowLayout::getSpace() const {
        return space_;
    }
}