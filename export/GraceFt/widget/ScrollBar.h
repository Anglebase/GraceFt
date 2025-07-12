#pragma once

#include <GraceFt/Block.h>

namespace GFt {
    namespace Widget {
        /// @brief 垂直滚动条
        /// @ingroup 部件库
        class VScrollBar : public Block {
            float currentPos_;
            float completeSize_;
            float visibleSize_;
            float step_{ 1.f };

            Color backgroundColor_{ 0xF0,0xF0,0xF0,0xEF };
            Color barColor_{ 0xBF,0xBF,0xBF,0xFF };
            Color barBorderColor_{ 0,0,0,0 };

            PenSet penSet_{ Color{0,0,0,0} };
            BrushSet brushSet_{ Color{0,0,0,0} };

            iPoint bPos_;
            float y_;
            std::size_t ssid;
        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* e) override;
            void onMouseWheel(MouseWheelEvent* e) override;

        public:
            /// @brief 构造函数
            /// @param rect 矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            VScrollBar(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~VScrollBar() override = default;

            /// @brief 设置当前位置
            /// @param pos 位置
            void setPosition(float pos);
            /// @brief 获取当前位置
            /// @return 当前位置
            float getPosition() const;
            /// @brief 设置完整大小
            /// @param size 大小
            void setCompleteSize(float size);
            /// @brief 获取完整大小
            /// @return 完整大小
            float getCompleteSize() const;
            /// @brief 设置可见大小
            /// @param size 大小
            void setVisibleSize(float size);
            /// @brief 获取可见大小
            /// @return 可见大小
            float getVisibleSize() const;
            /// @brief 设置步长
            /// @param step 步长
            void setStep(float step);
            /// @brief 获取步长
            /// @return 步长
            float getStep() const;

            Color& backgroundColor();
            Color& barColor();
            Color& barBorderColor();

            const Color& backgroundColor() const;
            const Color& barColor() const;
            const Color& barBorderColor() const;

        public:
            Signal<float> onCurrentPosChanged;  ///< 滚动条位置发生改变时发出此信号
        };

        /// @brief 水平滚动条
        /// @ingroup 部件库
        class HScrollBar : public Block {
            float currentPos_;
            float completeSize_;
            float visibleSize_;
            float step_{ 1.f };

            Color backgroundColor_{ 0xF0, 0xF0, 0xF0, 0xEF };
            Color barColor_{ 0xBF,0xBF,0xBF,0xFF };
            Color barBorderColor_{ 0,0,0,0 };

            PenSet penSet_{ Color{0,0,0,0} };
            BrushSet brushSet_{ Color{0,0,0,0} };

            iPoint bPos_;
            float x_;
            std::size_t ssid;

        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* e) override;
            void onMouseWheel(MouseWheelEvent* e) override;

        public:
            /// @brief 构造函数
            /// @param rect 矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            HScrollBar(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~HScrollBar() override = default;

            /// @brief 设置当前位置
            /// @param pos 位置
            void setPosition(float pos);
            /// @brief 获取当前位置
            /// @return 当前位置
            float getPosition() const;
            /// @brief 设置完整大小
            /// @param size 大小
            void setCompleteSize(float size);
            /// @brief 获取完整大小
            /// @return 完整大小
            float getCompleteSize() const;
            /// @brief 设置可见大小
            /// @param size 大小
            void setVisibleSize(float size);
            /// @brief 获取可见大小
            /// @return 可见大小
            float getVisibleSize() const;
            /// @brief 设置步长
            /// @param step 步长
            void setStep(float step);
            /// @brief 获取步长
            /// @return 步长
            float getStep() const;

            Color& backgroundColor();
            Color& barColor();
            Color& barBorderColor();

            const Color& backgroundColor() const;
            const Color& barColor() const;
            const Color& barBorderColor() const;

        public:
            Signal<float> onCurrentPosChanged;  ///< 滚动条位置发生改变时发出此信号
        };
    }
}