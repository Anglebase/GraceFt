#pragma once

namespace GFt {
    class Block;
    class BlockFocus {
        Block* focuson_ = nullptr;
    private:
        BlockFocus() = default;
        BlockFocus(const BlockFocus&) = delete;
        BlockFocus& operator=(const BlockFocus&) = delete;
        BlockFocus(BlockFocus&&) = delete;
        BlockFocus& operator=(BlockFocus&&) = delete;
    public:
        static BlockFocus& getInstance();
        Block* getFocusOn();
        void setFocusOn(Block* block);
    };
}