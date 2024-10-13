#pragma once

#include <GraceFt/Rect.hpp>
#include <GraceFt/Signal.hpp>
#include <GraceFt/Graphics.h>

namespace GFt {
    /// @defgroup 基础UI封装库

    /// @class GraphInterface
    /// @brief 图形绘制接口
    /// @details 图形绘制接口，用于绘制图形，提供绘制区域的接口
    /// @ingroup 基础UI封装库
    class GraphInterface {
        iRect rect_;
    protected:
        /// @brief 绘制接口
        /// @param g 绘图对象
        virtual void onDraw(Graphics& g) = 0;

    public:
        /// @brief 构造函数
        /// @param rect 绘制区域
        GraphInterface(iRect rect);
        virtual ~GraphInterface();

        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setPosition(const iPoint& pos);
        void setSize(const iSize& size);
        void setRect(const iRect& rect);

        const iRect& rect() const;
    public:
        Signal<const iPoint&> onPositionChanged;
        Signal<const iSize&> onSizeChanged;

    };
}