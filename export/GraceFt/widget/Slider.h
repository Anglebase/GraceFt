#pragma once

#include <GraceFt/Block.h>

namespace GFt {
    namespace Widget {
        /// @brief 水平滑动条
        /// @ingroup 部件库
        class HSlider : public Block {
            float value_{ 0 };
            float minValue_{ 0 };
            float maxValue_{ 100 };
            float step_{ 0.1f };

            fPoint handlePos_;

            Color backgroundColor_{ 0,0,0,0 };
            Color foregroundColor_{ 0xC5,0xC9,0xCE };
            Color handleColor_{ 0x5E, 0x77, 0xFC };
            int handleRadius_{ 10 };
            int handleThickness_{ 7 };
            bool showDiff_{ true };

            PenSet penSet_{ Color{0,0,0,0} };
            BrushSet brushSet_{ Color{0,0,0,0} };

            std::size_t ssid;
            bool reverse_{ false };
        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* e) override;

        public:
            /// @brief 构造函数
            /// @param rect 矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            HSlider(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~HSlider() override = default;

            /// @brief 设置范围
            /// @param minValue 最小值
            /// @param maxValue 最大值
            /// @param step 步长
            void setRange(float minValue, float maxValue, float step = 1.0f);
            /// @brief 设置当前值
            /// @param value 值
            void setValue(float value);
            /// @brief 获取当前值
            /// @return 当前值
            float getValue() const;

            Color& backgroundColor();
            Color& foregroundColor();
            Color& handleColor();
            int& handleRadius();
            int& handleThickness();
            void setShowDiff(bool showDiff);
            void setReverse(bool reverse);

            const Color& backgroundColor() const;
            const Color& foregroundColor() const;
            const Color& handleColor() const;
            int handleRadius() const;
            int handleThickness() const;
            bool isShowDiff() const;
            bool isReverse() const;

        public:
            Signal<float> onValueChanged;   ///< 当值发生更改时发出此信号
        };

        /// @brief 垂直滑动条
        /// @ingroup 部件库
        class VSlider : public Block {
            float value_{ 0 };
            float minValue_{ 0 };
            float maxValue_{ 100 };
            float step_{ 0.1f };

            fPoint handlePos_;

            Color backgroundColor_{ 0,0,0,0 };
            Color foregroundColor_{ 0xC5,0xC9,0xCE };
            Color handleColor_{ 0x5E, 0x77, 0xFC };
            int handleRadius_{ 10 };
            int handleThickness_{ 7 };
            bool showDiff_{ true };

            PenSet penSet_{ Color{0,0,0,0} };
            BrushSet brushSet_{ Color{0,0,0,0} };

            std::size_t ssid;
            bool reverse_{ false };
        protected:
            void onDraw(Graphics& g) override;
            void onMouseButtonPress(MouseButtonPressEvent* e) override;

        public:
            /// @brief 构造函数
            /// @param rect 矩形区域
            /// @param parent 父级块
            /// @param zIndex 层级
            VSlider(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
            ~VSlider() override = default;
            
            /// @brief 设置范围
            /// @param minValue 最小值
            /// @param maxValue 最大值
            /// @param step 步长
            void setRange(float minValue, float maxValue, float step = 1.0f);
            /// @brief 设置当前值
            /// @param value 值
            void setValue(float value);
            /// @brief 获取当前值
            /// @return 当前值
            float getValue() const;

            Color& backgroundColor();
            Color& foregroundColor();
            Color& handleColor();
            int& handleRadius();
            int& handleThickness();
            void setShowDiff(bool showDiff);
            void setReverse(bool reverse);

            const Color& backgroundColor() const;
            const Color& foregroundColor() const;
            const Color& handleColor() const;
            int handleRadius() const;
            int handleThickness() const;
            bool isShowDiff() const;
            bool isReverse() const;

        public:
            Signal<float> onValueChanged;    ///< 当值发生更改时发出此信号
        };
    }
}