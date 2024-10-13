#pragma once

#include <GraceFt/Color.h>

namespace GFt {
    /// @defgroup  API接口库
    /// @brief 该模块是API接口库，包含了与底层交互的相关内容

    /// @defgroup 枚举
    /// @ingroup  API接口库

    /// @defgroup 画笔样式枚举
    /// @ingroup 枚举

    /// @brief 画线样式
    /// @ingroup 画笔样式枚举
    enum class LineStyle {
        Solid,          ///< 实线
        Dash,           ///< 虚线
        Dot,            ///< 点线
        DashDot,        ///< 点划线
        UserDefined,    ///< 用户自定义线型
        Null            ///< 不可见
    };
    /// @brief 线帽样式
    /// @brief 线帽和接点样式如图
    /// @image html penstyle.png "线帽和接点样式"
    /// @ingroup 画笔样式枚举
    enum class CapStyle {
        Flat,           ///< 平头
        Square,         ///< 方头
        Round           ///< 圆头
    };
    /// @brief 接点样式
    /// @ingroup 画笔样式枚举
    enum class JoinStyle {
        Miter,          ///< 尖角
        Bevel,          ///< 斜角
        Round           ///< 圆角
    };

    /// @defgroup 图形系统
    /// @ingroup  API接口库

    /// @defgroup 接口类型
    /// @ingroup 图形系统

    /// @class PenSet
    /// @brief 画笔设置类
    /// @details 用于设置画笔的各种属性，如线宽、线型、线帽、接点等。
    /// @ingroup 接口类型
    class PenSet {
        friend class Graphics;
        void* pen_;
    public:
        /// @brief 构造函数
        /// @param color 画笔颜色
        /// @param width 画笔宽度，默认为1
        PenSet(const Color& color, int width = 1);
        /// @brief 复制构造
        PenSet(const PenSet& other);
        /// @brief 移动构造
        PenSet(PenSet&& other);
        /// @brief 复制赋值
        PenSet& operator=(const PenSet& other);
        /// @brief 移动赋值
        PenSet& operator=(PenSet&& other);
        ~PenSet();

        /// @brief 设置颜色
        /// @param color 颜色
        void setColor(const Color& color);
        /// @brief 设置线宽
        /// @param width 线宽
        void setLineWidth(int width);
        /// @brief 设置线型
        /// @param style 线型
        void setLineStyle(LineStyle style);
        /// @brief 设置用户自定义线型
        /// @param style 用户自定义线型
        void setLineStyle(short style);
        /// @brief 设置线帽样式
        /// @param style 线帽样式
        void setCapStyle(CapStyle style);
        /// @brief 设置起始线帽样式
        /// @param style 起始线帽样式
        void setStartCap(CapStyle style);
        /// @brief 设置终止线帽样式
        /// @param style 终止线帽样式
        void setEndCap(CapStyle style);
        /// @brief 设置接点样式
        /// @param style 接点样式
        /// @param limit 接点尖角长度限制值，默认为10.0f
        void setJoinStyle(JoinStyle style, float limit = 10.0f);

        /// @brief 获取颜色
        /// @return 颜色
        Color getColor() const;
        /// @brief 获取线宽
        /// @return 线宽
        int getPenWidth() const;
        /// @brief 获取线型
        /// @return 线型
        LineStyle getPenStyle() const;
        /// @brief 获取用户自定义线型
        /// @return 用户自定义线型
        short getUserPenStyle() const;
        /// @brief 获取线帽样式
        /// @return 线帽样式
        CapStyle getCapStyle() const;
        /// @brief 获取起始线帽样式
        /// @return 起始线帽样式
        CapStyle getStartCap() const;
        /// @brief 获取终止线帽样式
        /// @return 终止线帽样式
        CapStyle getEndCap() const;
        /// @brief 获取接点样式
        /// @return 接点样式
        JoinStyle getJoinStyle() const;
    };
}