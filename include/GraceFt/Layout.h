#pragma once

namespace GFt {
    /// @brief 布局基类
    /// @ingroup 基础UI封装库
    class Layout {
        int leftPadding_{ 0 };
        int topPadding_{ 0 };
        int rightPadding_{ 0 };
        int bottomPadding_{ 0 };

        bool shouleUpdateLayout_{ true };
    public:
        static inline constexpr float Fixed = 0.f;
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

        /// @brief 设置左边距
        void setLeftPadding(int left);
        /// @brief 设置上边距
        void setTopPadding(int top);
        /// @brief 设置右边距
        void setRightPadding(int right);
        /// @brief 设置下边距
        void setBottomPadding(int bottom);

        /// @brief 获取左边距
        int getLeftPadding() const;
        /// @brief 获取上边距
        int getTopPadding() const;
        /// @brief 获取右边距
        int getRightPadding() const;
        /// @brief 获取下边距
        int getBottomPadding() const;

        /// @brief 标记是否需要更新布局
        void setShouldUpdateLayout(bool shouldUpdateLayout = true);
        /// @brief 检查是否需要更新布局
        bool shouldUpdateLayout() const;
    };
}