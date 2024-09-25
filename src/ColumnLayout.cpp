#include "ColumnLayout.h"

#include <algorithm>

namespace GFt {
    void ColumnLayout::updateLayout() {
        // 计算所有block的高度占比之和
        float sum = 0.0f;
        for (auto& [block, heightPro] : blockLayout_)
            sum += heightPro > 0.f ? heightPro : 0.f;
        // 计算可供分配的高度
        auto availableHeight =
            rect().height() -
            (space_ * (blockLayout_.size() - 1)) -
            (getTopPadding() + getBottomPadding());
        for (auto& [block, heightPro] : blockLayout_)
            availableHeight -= heightPro <= 0.f ? block->rect().height() : 0.f;
        // 计算每个block的高度、高度、x坐标
        for (auto& [block, heightPro] : blockLayout_) {
            if (heightPro > 0.f)
                block->rect().height() = (heightPro / sum) * availableHeight;
            block->rect().width() = rect().width() - (getLeftPadding() + getRightPadding());
            block->rect().x() = getLeftPadding();
        }
        // 计算每个block的y坐标
        int y = getTopPadding();
        for (auto& [block, heightPro] : blockLayout_) {
            block->rect().y() = y;
            y += block->rect().height() + space_;
        }
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
        setShouldUpdateLayout();
        for (auto& [b, h] : blockLayout_)
            if (b == block) {
                h = widthProportion;
                return;
            }
        blockLayout_.push_back({ block, widthProportion });
        this->addChild(block);
    }
    void ColumnLayout::removeItem(Block* block) {
        setShouldUpdateLayout();
        auto it = std::remove_if(blockLayout_.begin(), blockLayout_.end(),
            [block](const std::pair<Block*, float>& item) {
                auto [b, h] = item;
                return b == block;
            });
        std::vector<std::pair<Block*, float>> newBlockLayout(blockLayout_.begin(), it);
        blockLayout_.swap(newBlockLayout);
        this->removeChild(block);
    }
    void ColumnLayout::setSpace(int space) {
        space_ = space;
        setShouldUpdateLayout();
    }
    int ColumnLayout::getSpace() const {
        return space_;
    }
}
