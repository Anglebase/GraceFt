#pragma once

#include <map>
#include <GraceFt/Rect.hpp>
#include <GraceFt/Layout.h>
#include <GraceFt/Block.h>

namespace GFt {
    class GridLayout : public Layout, public Block {
        int rows_{ 1 }, cols_{ 1 };
        int vspace_{ 0 }, hspace_{ 0 };
        std::map<Block*, iRect> griditems_;

        void updateLayout();
    public:
        void onDraw(const iRect& rect) override;

    public:
        GridLayout(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        ~GridLayout() override;

        void addItem(Block* item, const iRect& rect);
        void removeItem(Block* item);

        void setSpace(int space);
        void setSpace(int hspace, int vspace);
        void setGridSize(int size);
        void setGridSize(int rows, int cols);

        void setVSpace(int vspace);
        void setHSpace(int hspace);
        void setRows(int rows);
        void setCols(int cols);

        int getRows() const;
        int getCols() const;
        int getVSpace() const;
        int getHSpace() const;
    };
}