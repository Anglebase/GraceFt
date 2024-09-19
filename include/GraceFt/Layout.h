#pragma once

namespace GFt {
    /// @brief 布局基类
    class Layout {
        int leftPadding_{ 0 };
        int topPadding_{ 0 };
        int rightPadding_{ 0 };
        int bottomPadding_{ 0 };

    public:
        Layout() = default;
        virtual ~Layout() = default;

        /// @brief 设置边距
        /// @param padding 统一设置边距
        void setPadding(int padding);
        /// @brief 设置边距
        /// @param leftright 左右边距
        /// @param topbottom 上下边距
        void setPadding(int leftright, int topbottom);
        /// @brief 设置边距
        /// @param left 左边距
        /// @param top 上边距
        /// @param right 右边距
        /// @param bottom 下边距
        void setPadding(int left, int top, int right, int bottom);

        /// @brief 左边距
        int& leftPadding();
        /// @brief 上边距
        int& topPadding();
        /// @brief 右边距
        int& rightPadding();
        /// @brief 下边距
        int& bottomPadding();

        /// @brief 左边距
        int leftPadding() const;
        /// @brief 上边距
        int topPadding() const;
        /// @brief 右边距
        int rightPadding() const;
        /// @brief 下边距
        int bottomPadding() const;
    };
}