#pragma once

#include <GraceFt/Block.h>
#include <GraceFt/Graphics.h>

namespace GFt {
    namespace Widget {
        /// @brief 文本标签控件
        /// @ingroup 部件库
        class Label : public Block {
            std::wstring text_;

            BrushSet brushSet_;
            TextSet textSet_;

            int leftPadding_{ 3 };
            int rightPadding_{ 3 };
            int topPadding_{ 3 };
            int bottomPadding_{ 3 };
            int textAlignment_{ TextAlign::Left | TextAlign::Middle };

        protected:
            void onDraw(const iRect& rect) override;
            void onMouseButtonPress(MouseButtonPressEvent* event) override;

        public:
            /// @brief 构造函数
            /// @param text 文本内容
            /// @param rect 位置大小
            /// @param parent 父控件
            /// @param zIndex 层级
            Label(const std::wstring& text, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            Label(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~Label() override = default;
            
            /// @brief 文本内容
            std::wstring& text();
            /// @brief 画刷集
            BrushSet& brushSet();
            /// @brief 文本集
            TextSet& textSet();
            /// @brief 左边距
            int& leftPadding();
            /// @brief 右边距
            int& rightPadding();
            /// @brief 上边距
            int& topPadding();
            /// @brief 下边距
            int& bottomPadding();
            /// @brief 文本对齐方式
            int& textAlignment();
            
            /// @see text()
            const std::wstring& text() const;
            /// @see brushSet()
            const BrushSet& brushSet() const;
            /// @see textSet()
            const TextSet& textSet() const;
            /// @see leftPadding()
            int leftPadding() const;
            /// @see rightPadding()
            int rightPadding() const;
            /// @see topPadding()
            int topPadding() const;
            /// @see bottomPadding()
            int bottomPadding() const;
            /// @see textAlignment()
            int textAlignment() const;

            /// @brief 设置边距
            /// @param padding 统一设置边距
            void setPadding(int padding);
            /// @brief 设置边距
            /// @param leftRight 左右边距
            /// @param topBottom 上下边距
            void setPadding(int leftRight, int topBottom);
            /// @brief 设置边距
            /// @param left 左边距
            /// @param right 右边距
            /// @param top 上边距
            /// @param bottom 下边距
            void setPadding(int left, int right, int top, int bottom);
        };
    }
}