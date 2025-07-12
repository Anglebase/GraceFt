#pragma once

namespace GFt {
    class Block;
    /// @class BlockFocusManager
    /// @brief 焦点块管理器，用于管理当前焦点块
    /// @ingroup 基础UI封装库
    class BlockFocusManager {
        static Block* focuson_;
    private:
        BlockFocusManager() = delete;
    public:
        /// @brief 获取当前焦点块
        /// @return 当前焦点块
        static Block* getFocusOn();
        /// @brief 设置当前焦点块
        /// @param block 要设置的焦点块
        static void setFocusOn(Block* block);
    };

    /// @class BlockHoverManager
    /// @brief 鼠标悬停管理器，用于管理当前鼠标悬停块
    /// @ingroup 基础UI封装库
    class BlockHoverManager {
        static Block* hoveron_;
    private:
        BlockHoverManager() = delete;
    public:
        /// @brief 获取当前鼠标悬停块
        /// @return 当前鼠标悬停块
        static Block* getHoverOn();
        /// @brief 设置当前鼠标悬停块
        /// @param block 要设置的鼠标悬停块
        static void setHoverOn(Block* block);
    };
}