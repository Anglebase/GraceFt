#pragma once

#include <GraceFt/Rect.hpp>

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
        /// @param rect 绘制区域
        virtual void onDraw(const iRect& rect) = 0;

    public:
        /// @brief 构造函数
        /// @param rect 绘制区域
        GraphInterface(iRect rect);
        virtual ~GraphInterface();

        /// @brief 绘制区域
        /// @return 绘制区域
        iRect& rect();
        /// @brief 绘制区域 (const)
        /// @return 绘制区域 (const)
        const iRect& rect() const;
    };
}