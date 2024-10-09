#pragma once

#include <GraceFt/Block.h>
#include <GraceFt/Signal.hpp>
#include <GraceFt/PenSet.h>
#include <GraceFt/BrushSet.h>
#include <GraceFt/TextSet.h>

/// @defgroup 部件库
namespace GFt {
    /// @brief 定义式UI库
    namespace Widget {
        
        /// @brief 按钮控件
        /// @ingroup 部件库
        class Button : public Block {
            std::wstring text_;
            bool disabled_{ false };

            BrushSet brushSet_;
            TextSet textSet_;

            Color textColor_{ 0x00, 0x00, 0x00, 0xFF };
            Color backgroundColor_{ 0xE5, 0xE5, 0xE5, 0xFF };
            Color hoverColor_{ 0xC6, 0xC6, 0xC6, 0xFF };
            Color pressedColor_{ 0xB7, 0xB7, 0xB7, 0xFF };
            Color disabledColor_{ 0xCF, 0xCF, 0xCF, 0xFF };

        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* event) override;
            void onMouseButtonRelease(MouseButtonReleaseEvent* event) override;

        public:
            /// @brief 构造函数
            /// @param text 按钮文本
            /// @param rect 按钮矩形区域
            /// @param parent 父控件
            /// @param zIndex 控件层级
            Button(const std::wstring& text, const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            Button(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            virtual ~Button();
            /// @brief 按钮文本
            std::wstring& text();
            /// @brief 按钮文本颜色
            Color& textColor();
            /// @brief 按钮背景颜色
            Color& backgroundColor();
            /// @brief 按钮悬停颜色
            Color& hoverColor();
            /// @brief 按钮按下颜色
            Color& pressedColor();
            /// @brief 按钮禁用颜色
            Color& disabledColor();
            /// @brief 画刷设置
            BrushSet& brushSet();
            /// @brief 文本设置
            TextSet& textSet();

            /// @brief 按钮文本
            /// @see text()
            const std::wstring& text() const;
            /// @brief 按钮文本颜色
            /// @see textColor()
            const Color& textColor() const;
            /// @brief 按钮背景颜色
            /// @see backgroundColor()
            const Color& backgroundColor() const;
            /// @brief 按钮悬停颜色
            /// @see hoverColor()
            const Color& hoverColor() const;
            /// @brief 按钮按下颜色
            /// @see pressedColor()
            const Color& pressedColor() const;
            /// @brief 按钮禁用颜色
            /// @see disabledColor()
            const Color& disabledColor() const;
            /// @brief 画刷设置
            /// @see brushSet()
            const BrushSet& brushSet() const;
            /// @brief 文本设置
            /// @see textSet()
            const TextSet& textSet() const;

            /// @brief 设置按钮禁用状态
            void setEnable(bool disabled);
            /// @brief 获取按钮禁用状态
            bool isDisabled() const;

        public:
            Signal<bool> onStatusChanged;   ///< 按钮状态改变信号
            Signal<void> onClicked;         ///< 按钮点击信号
            Signal<void> onReleased;        ///< 按钮释放信号
        };
    }
}