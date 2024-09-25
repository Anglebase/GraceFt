#include "GridLayout.h"

namespace GFt {
    void GridLayout::updateLayout() {
        auto unitWidth = (rect().width() - (cols_ - 1.f) * hspace_ -
            (getLeftPadding() + getRightPadding())) / cols_;
        auto unitHeight = (rect().height() - (rows_ - 1.f) * vspace_ -
            (getTopPadding() + getBottomPadding())) / rows_;
        for (auto& [item, rect] : griditems_) {
            item->setX(rect.x() * unitWidth + hspace_ * (rect.x() - 1) + getLeftPadding());
            item->setY(rect.y() * unitHeight + vspace_ * (rect.y() - 1) + getTopPadding());
            item->setWidth(rect.width() * unitWidth + hspace_ * (rect.width() - 1));
            item->setHeight(rect.height() * unitHeight + vspace_ * (rect.height() - 1));
        }
        setShouldUpdateLayout(false);
    }

    void GridLayout::onDraw(const iRect& rect) {
        if (shouldUpdateLayout())
            updateLayout();
        return Block::onDraw(rect);
    }

    GridLayout::GridLayout(const iRect& rect, Block* parent, int zIndex)
        : Block(rect, parent, zIndex) {
        onSizeChanged.connect([this](const iSize& size) {
            this->setShouldUpdateLayout();
            });
    }
    GridLayout::~GridLayout() = default;
    void GridLayout::addItem(Block* item, const iRect& rect) {
        griditems_[item] = rect;
        this->addChild(item);
        setShouldUpdateLayout();
    }
    void GridLayout::removeItem(Block* item) {
        if (griditems_.find(item) == griditems_.end())
            return;
        this->removeChild(item);
        griditems_.erase(item);
        setShouldUpdateLayout();
    }
    void GridLayout::setSpace(int space) {
        vspace_ = hspace_ = space;
        setShouldUpdateLayout();
    }
    void GridLayout::setSpace(int hspace, int vspace) {
        hspace_ = hspace;
        vspace_ = vspace;
        setShouldUpdateLayout();
    }
    void GridLayout::setGridSize(int size) {
        rows_ = cols_ = size;
        setShouldUpdateLayout();
    }
    void GridLayout::setGridSize(int rows, int cols) {
        rows_ = rows;
        cols_ = cols;
        setShouldUpdateLayout();
    }

    void GridLayout::setVSpace(int vspace) {
        vspace_ = vspace;
        setShouldUpdateLayout();
    }
    void GridLayout::setHSpace(int hspace) {
        hspace_ = hspace;
        setShouldUpdateLayout();
    }
    void GridLayout::setRows(int rows) {
        rows_ = rows;
        setShouldUpdateLayout();
    }
    void GridLayout::setCols(int cols) {
        cols_ = cols;
        setShouldUpdateLayout();
    }

    int GridLayout::getRows() const { return rows_; }
    int GridLayout::getCols() const { return cols_; }
    int GridLayout::getHSpace() const { return hspace_; }
    int GridLayout::getVSpace() const { return vspace_; }
}