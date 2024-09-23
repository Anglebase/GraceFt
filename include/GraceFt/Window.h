#pragma once

#include <GraceFt/Block.h>
#include <GraceFt/Signal.hpp>

namespace GFt {
    /// @class Window
    /// @brief 全局窗口对象
    /// @details 此类用于表示一个全局唯一的窗口对象, 并提供了窗口创建的一系列工厂函数
    /// @details 同时也提供了一些操作窗口的成员函数
    /// @ingroup 基础UI封装库
    class Window final : public Block {
        static Window* pInstance_;
        Block* root_;

        iSize store_;
        iPoint pos_;
        bool isMaximized_{ false };
        bool isMinimized_{ false };
        bool isTopMost_{ false };
        bool isFrameless_{ false };

    private:
        Window(int width, int height, int flags);
        Window(const Window& other) = delete;
        Window& operator=(const Window& other) = delete;
        Window(Window&& other) = delete;
        Window& operator=(Window&& other) = delete;

    public:
        ~Window();
        /// @brief 显示窗口
        void show();
        /// @brief 隐藏窗口
        void hide();
        /// @brief 更改窗口的大小
        /// @param size 新的窗口大小
        void resize(const iSize& size);
        /// @brief 移动窗口(相对位置)
        /// @param dpos 相对于当前位置的差值
        void move(const iPoint& dpos);
        /// @brief 移动窗口(绝对位置)
        /// @param pos 新的窗口位置
        void moveTo(const iPoint& pos);
        /// @brief 设置窗口标题
        /// @param title 新的标题
        void setTitle(const std::wstring& title);
        /// @brief 设置窗口是否置顶
        /// @param topMost 是否置顶
        /// @note 当窗口最大化或处于全屏显示状态时, 此函数无效
        void setTopMost(bool topMost = true);
        /// @brief 设置窗口是否无边框
        /// @param frameless 是否无边框
        /// @note 当窗口最大化或处于全屏显示状态时, 此函数无效
        void setFrameless(bool frameless = true);
        /// @brief 设置窗口透明度
        /// @param alpha 透明度值(0.0~1.0)
        void setAlpha(float alpha);
        /// @brief 窗口最小化
        void minimize();
        /// @brief 全屏显示窗口
        void fullscreen();
        /// @brief 最大化窗口
        void maximize();
        /// @brief 还原最大化或全屏显示的窗口
        /// @note 
        void restore();

    public:
        /// @brief 创建普通窗口
        /// @param rect 窗口大小
        /// @param hide 是否在创建后隐藏窗口
        static Window* createWindow(Block* block, bool hide = false);
        /// @brief 创建全屏窗口
        /// @param hide 是否在创建后隐藏窗口
        static Window* createFullScreenWindow(Block* block, bool hide = false);
        /// @brief 创建置顶窗口
        /// @param rect 窗口大小
        /// @param hide 是否在创建后隐藏窗口
        static Window* createTopMostWindow(Block* block, bool hide = false);
        /// @brief 创建无边框窗口
        /// @param rect 窗口大小
        /// @param hide 是否在创建后隐藏窗口
        static Window* createNoBorderWindow(Block* block, bool hide = false);
        /// @brief 创建无边框置顶窗口
        /// @param rect 窗口大小
        /// @param hide 是否在创建后隐藏窗口
        static Window* createNoBorderTopMostWindow(Block* block, bool hide = false);
        /// @brief 获取已创建的窗口对象实例
        /// @return 已创建的窗口对象指针
        static Window* window();
    public:
        static Signal<Window*> onWindowCreated;  ///< 窗口创建信号
        static Signal<Window*> onWindowDestroyed;  ///< 窗口销毁信号
        static Signal<Window*> onWindowResized;  ///< 窗口大小改变信号
        static Signal<Window*> onWindowMoved;  ///< 窗口位置改变信号
        static Signal<Window*> onWindowMinimized;  ///< 窗口最小化信号
        static Signal<Window*> onWindowMaximized;  ///< 窗口最大化信号
        static Signal<Window*> onWindowRestored;  ///< 窗口还原信号
        static Signal<Window*> onWindowFullscreened;  ///< 窗口全屏信号
        static Signal<Window*> onWindowSizeChanged;  ///< 窗口大小改变信号
    };
}