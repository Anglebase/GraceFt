#include "RowLayout.h"
#include <Graphics.h>
namespace GFt {
    void RowLayout::updateLayout() {
        // 计算所有block的宽度占比之和
        float sum = 0.0f;
        for (auto& [block, widthPro] : blockLayout_)
            sum += widthPro;
        // 计算每个block的宽度、高度、y坐标
        for (auto& [block, widthPro] : blockLayout_) {
            block->rect().width() = (widthPro / sum) *
                (rect().width() - (space_ * (blockLayout_.size() - 1)) - (getLeftPadding() + getRightPadding()));
            block->rect().height() = rect().height() - (getTopPadding() + getBottomPadding());
            block->rect().y() = getTopPadding();
        }
        // 计算每个block的x坐标
        float x = getLeftPadding();
        using Iter = std::map<Block*, float>::reverse_iterator;
        for (Iter iter = blockLayout_.rbegin(); iter != blockLayout_.rend(); ++iter) {
            auto& [block, widthPro] = *iter;
            block->rect().x() = x;
            x += block->rect().width() + space_;
        }
    }

    void RowLayout::onDraw(const iRect& rect) {
        Graphics g;
        using namespace GFt::literals;
        PenSet p(0_rgb, 5);
        g.bindPenSet(&p);
        g.drawRect(iRect{ iPoint{}, rect.size() });
        if (shouleUpdateLayout())
            updateLayout();
        return Block::onDraw(rect);
    }

    RowLayout::RowLayout(const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex) {
        onLayoutUpdate.connect(this, &RowLayout::updateLayout);
    }
    RowLayout::~RowLayout() = default;
    void RowLayout::addLayout(Block* block, float widthProportion) {
        blockLayout_[block] = widthProportion;
        this->addChild(block);
        setShouleUpdateLayout();
    }
    void RowLayout::removeLayout(Block* block) {
        if (blockLayout_.find(block) == blockLayout_.end())
            return;
        blockLayout_.erase(block);
        this->removeChild(block);
        setShouleUpdateLayout();
    }
    void RowLayout::setSpace(int space) {
        space_ = space;
        setShouleUpdateLayout();
    }
    int RowLayout::getSpace() const {
        return space_;
    }
}