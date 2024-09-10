#include "BlockFocus.h"

namespace GFt {
    BlockFocus& BlockFocus::getInstance() {
        static BlockFocus instance;
        return instance;
    }
    Block* BlockFocus::getFocusOn() {
        return this->focuson_;
    }
    void BlockFocus::setFocusOn(Block* block) {
        this->focuson_ = block;
    }
}
