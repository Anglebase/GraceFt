#include "BlockFocus.h"

namespace GFt {
    Block* BlockFocusManager::focuson_ = nullptr;
    Block* BlockFocusManager::getFocusOn() {
        return BlockFocusManager::focuson_;
    }
    void BlockFocusManager::setFocusOn(Block* block) {
        BlockFocusManager::focuson_ = block;
    }
}
