#include "RowLayout.h"

#include <algorithm>

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
                block->setWidth((widthPro / sum) * availableWidth);
            block->setHeight(rect().height() - (getTopPadding() + getBottomPadding()));
            block->setY(getTopPadding());
        }
        // 计算每个block的x坐标
        int x = getLeftPadding();
        for (auto& [block, widthPro] : blockLayout_) {
            block->setX(x);
            x += block->rect().width() + space_;
        }
        setShouldUpdateLayout(false);
    }

    void RowLayout::onDraw(const iRect& rect) {
        if (shouldUpdateLayout())
            updateLayout();
        return Block::onDraw(rect);
    }

    RowLayout::RowLayout(const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex) {
        onSizeChanged.connect([this](const iSize& size){
            this->setShouldUpdateLayout();
        });
    }
    RowLayout::~RowLayout() = default;
    void RowLayout::addItem(Block* block, float widthProportion) {
        setShouldUpdateLayout();
        for (auto& [b, w] : blockLayout_)
            if (b == block) {
                w = widthProportion;
                return;
            }
        blockLayout_.push_back({ block, widthProportion });
        this->addChild(block);
    }
    void RowLayout::removeItem(Block* block) {
        setShouldUpdateLayout();
        auto it = std::remove_if(blockLayout_.begin(), blockLayout_.end(),
            [block](const std::pair<Block*, float>& p) {
                auto [b, w] = p;
                return b == block;
            });
        this->removeChild(block);
    }
    void RowLayout::setSpace(int space) {
        space_ = space;
        setShouldUpdateLayout();
    }
    int RowLayout::getSpace() const {
        return space_;
    }
}