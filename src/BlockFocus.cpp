#include "GraceFt/BlockFocus.h"
#include <GraceFt/Block.h>
namespace GFt {
    Block* BlockFocusManager::focuson_ = nullptr;
    Block* BlockHoverManager::hoveron_ = nullptr;
    Block* BlockFocusManager::getFocusOn() {
        return BlockFocusManager::focuson_;
    }
    void BlockFocusManager::setFocusOn(Block* block) {
        if (block == BlockFocusManager::focuson_)
            return;
        if (BlockFocusManager::focuson_)
            BlockFocusManager::focuson_->FocusOff(block);
        if (block)
            block->FocusOn(BlockFocusManager::focuson_);
        BlockFocusManager::focuson_ = block;
    }
    Block* BlockHoverManager::getHoverOn() {
        return BlockHoverManager::hoveron_;
    }
    void BlockHoverManager::setHoverOn(Block* block) {
        if (block == BlockHoverManager::hoveron_)
            return;
        if (BlockHoverManager::hoveron_)
            BlockHoverManager::hoveron_->HoverOff(block);
        if (block)
            block->HoverOn(BlockHoverManager::hoveron_);
        BlockHoverManager::hoveron_ = block;
    }
}
