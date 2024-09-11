#pragma once

#include <vector>

#include <Color.h>
#include <Texture.h>
#include <Point.hpp>
#include <Rect.hpp>

namespace GFt {
    /// @defgroup 画刷样式枚举
    /// @ingroup 枚举

    /// @brief 填充样式
    /// @ingroup 画刷样式枚举
    enum class FillStyle {
        Empty,      ///< 无填充
        Solid,      ///< 纯色填充
        Line,       ///< 横线填充
    };
    /// @brief 画刷模式
    /// @ingroup 画刷样式枚举
    enum class BrushStyle {
        Default,         ///< 默认画刷模式
        Texture,         ///< 纹理画刷模式
        LinearGradient,  ///< 线性渐变画刷模式
        RadialGradient,  ///< 椭圆径向渐变画刷模式
        PolygonGradient, ///< 多边形径向渐变画刷模式
    };
    /// @class BrushSet
    /// @brief 画刷设置类
    /// @details 该类用于设置画刷的各种属性，包括填充颜色、填充样式、纹理、线性渐变、椭圆径向渐变、多边形径向渐变等
    /// @ingroup 接口类型
    class BrushSet {
        friend class Graphics;
        void* brush_;
        /// @cond IGNORE
        void release();
        /// @endcond
    public:
        /// @brief 构造函数
        /// @param color 填充颜色
        BrushSet(const Color& color);
        /// @brief 拷贝构造
        BrushSet(const BrushSet& other);
        /// @brief 移动构造
        BrushSet(BrushSet&& other);
        /// @brief 复制赋值
        BrushSet& operator=(const BrushSet& other);
        /// @brief 移动赋值
        BrushSet& operator=(BrushSet&& other);
        ~BrushSet();

        /// @brief 设置默认画刷填充
        /// @param color 填充颜色
        /// @param style 填充样式
        void setFillStyle(const Color& color, FillStyle style = FillStyle::Solid);
        /// @brief 设置纹理画刷填充
        /// @param texture 纹理
        /// @param rect 在纹理图像上的矩形区域
        void setTexture(const Texture& texture, const fRect& rect);
        /// @brief 设置线性渐变画刷填充
        /// @param start 起点
        /// @param startColor 起点颜色
        /// @param end 终点
        /// @param endColor 终点颜色
        void setLinearGradient(const fPoint& start, const Color& startColor, const fPoint& end, const Color& endColor);
        /// @brief 设置椭圆径向渐变画刷填充
        /// @param center 中心点
        /// @param centerColor 中心颜色
        /// @param rect 椭圆的外接矩形
        /// @param outerColor 外环颜色
        void setRadialGradient(const fPoint& center, const Color& centerColor, const fRect& rect, const Color& outerColor);
        /// @brief 设置多边形径向渐变画刷填充
        /// @param center 中心点
        /// @param centerColor 中心颜色
        /// @param points 多边形顶点
        /// @param colors 顶点颜色
        void setPolygonGradient(
            const fPoint& center, const Color& centerColor,
            const std::vector<fPoint>& points, const std::vector<Color>& colors
        );
        /// @brief 获取当前画刷模式
        /// @return 画刷模式
        BrushStyle getBrushStyle() const;
    };
}