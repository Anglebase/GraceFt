#pragma once

#include <GraceFt/Block.h>

namespace GFt {
    namespace Widget {
        /// @brief 复选框
        /// @ingroup 部件库
        class CheckBox : public Block {
            bool checked_;
            std::wstring text_;
            Font hoverfont_;
            Font normalfont_;
            Font selectedfont_;
            BrushSet hoverbs_;
            BrushSet normalbs_;
            BrushSet selectedbs_;

        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* e) override;

        public:
            /// @brief 构造函数
            /// @param rect 复选框的矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            CheckBox(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            /// @brief 析构函数
            ~CheckBox() override;
            /// @brief 设置复选框的选中状态
            /// @param checked 选中状态
            void setChecked(bool checked);
            /// @brief 获取复选框的选中状态
            /// @return 选中状态
            bool isChecked() const;

            /// @brief 样式信息函数
            std::wstring& text();
            /// @brief 样式信息函数
            Font& hoverFont();
            /// @brief 样式信息函数
            Font& normalFont();
            /// @brief 样式信息函数
            Font& selectedFont();
            /// @brief 样式信息函数
            BrushSet& hoverBrush();
            /// @brief 样式信息函数
            BrushSet& normalBrush();
            /// @brief 样式信息函数
            BrushSet& selectedBrush();

            /// @brief 样式信息函数
            const std::wstring& text() const;
            /// @brief 样式信息函数
            const Font& hoverFont() const;
            /// @brief 样式信息函数
            const Font& normalFont() const;
            /// @brief 样式信息函数
            const Font& selectedFont() const;
            /// @brief 样式信息函数
            const BrushSet& hoverBrush() const;
            /// @brief 样式信息函数
            const BrushSet& normalBrush() const;
            /// @brief 样式信息函数
            const BrushSet& selectedBrush() const;

        public:
            Signal<void> onChecked;         ///< 复选框被选中时触发
            Signal<void> onUnchecked;       ///< 复选框被取消选中时触发
            Signal<bool> onCheckChanged;    ///< 复选框选中状态改变时触发
        };
    }
}