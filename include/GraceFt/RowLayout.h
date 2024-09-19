#pragma once

#include <map>
#include <GraceFt/Layout.h>
#include <GraceFt/Block.h>
#include <GraceFt/Signal.hpp>

namespace GFt {
    class RowLayout : public Layout, public Block {
        int space_{ 0 };
        std::map<Block*, float> blockLayout_;

        void updateLayout();

    protected:
        void onDraw(const iRect& rect) override;

    public:
        RowLayout(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        ~RowLayout() override;

        void addLayout(Block* block, float widthProportion = 1.f);
        void removeLayout(Block* block);

        void setSpace(int space);
        int getSpace() const;
    public:
        Signal<void> onLayoutUpdate;
    };
}