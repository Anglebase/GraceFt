#pragma once

#include <GraceFt/Block.h>

namespace GFt {
    class RadioManager;
    namespace Widget {
        /// @brief 单选框
        /// @ingroup 部件库
        class RadioBox : public Block {
            GFt::RadioManager& manager_;
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
            /// @param manager 要与此单选框关联的管理器实例
            /// @param rect 单选框的矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            RadioBox(GFt::RadioManager& manager, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            /// @brief 析构函数
            ~RadioBox() override;
            /// @brief 设置单选框的选中状态
            /// @param checked 选中状态
            void setChecked(bool checked);
            /// @brief 获取单选框的选中状态
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
            Signal<void> onChecked;         ///< 单选框被选中时触发
            Signal<void> onUnchecked;       ///< 单选框被取消选中时触发
            Signal<bool> onCheckChanged;    ///< 单选框选中状态改变时触发
        };
    }
    /// @brief 单选框管理器
    /// @ingroup 部件库
    class RadioManager {
        Widget::RadioBox* radiobox_;
    public:
        RadioManager();
        ~RadioManager();
        /// @brief 设置当前选中的单选框
        /// @param radiobox 要选中的单选框
        void setRadioBox(Widget::RadioBox* radiobox);
        /// @brief 获取当前选中的单选框
        /// @return 当前选中的单选框
        Widget::RadioBox* getRadioBox() const;
    };
}