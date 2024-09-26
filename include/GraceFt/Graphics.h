#pragma once

#include <GraceFt/TextSet.h>
#include <GraceFt/PenSet.h>
#include <GraceFt/BrushSet.h>
#include <GraceFt/PixelMap.h>
#include <GraceFt/Line.hpp>
#include <GraceFt/Matrix.hpp>
#include <GraceFt/Ellipse.hpp>
#include <GraceFt/RoundRect.hpp>
#include <GraceFt/Bezier.hpp>
#include <GraceFt/Polygon.hpp>
#include <GraceFt/FitCurve.hpp>
#include <GraceFt/Path.h>
#include <GraceFt/PixelMap.h>
#include <GraceFt/Color.h>
#include <GraceFt/Circle.hpp>

namespace GFt {
    /// @defgroup 文本枚举
    /// @ingroup 枚举

    /// @brief 文本对齐方式
    /// @ingroup 文本枚举
    enum TextAlign {
        Left = 0x1,     ///< 左对齐
        Center = 0x2,   ///< 水平居中
        Right = 0x4,    ///< 右对齐
        Top = 0x10,     ///< 顶部对齐
        Middle = 0x20,  ///< 垂直居中
        Bottom = 0x40   ///< 底部对齐
    };

    /// @class Graphics
    /// @brief 绘图接口类
    /// @details 该类提供了绘图相关的接口，包括绘制线段、矩形、圆形、椭圆、圆弧、多边形、贝塞尔曲线、拟合曲线、路径、图像、文本等
    /// @ingroup 接口类型
    class Graphics {
        static PenSet defaultPenSet_;
        static BrushSet defaultBrushSet_;
        static TextSet defaultTextSet_;
        void* target_;
        PixelMap* targetPixelMap_;
    private:
        Graphics(const Graphics& other) = delete;
        Graphics& operator=(const Graphics& other) = delete;
    public:
        /// @brief 默认构造函数
        Graphics();
        Graphics(Graphics&& other);
        Graphics& operator=(Graphics&& other);
        ~Graphics();

        /// @brief 重置所有设置
        void reset();
        /// @brief 设置绘图目标
        /// @param target 绘图目标，如果为nullptr，则绘图目标为屏幕
        void setTarget(PixelMap* target);
        /// @brief 设置抗锯齿
        /// @param enable 是否启用抗锯齿
        void setAntiAliasing(bool enable);
        /// @brief 应用变换矩阵
        /// @param matrix 变换矩阵
        void setTransform(const fMat3x3& matrix);
        /// @brief 重置变换矩阵
        void resetTransform();
        /// @brief 获取绘图目标
        /// @return 绘图目标
        PixelMap* getTarget() const;
        /// @brief 获取当前应用的变换矩阵
        /// @return 变换矩阵
        fMat3x3 getTransform() const;
        /// @brief 使用背景色重绘绘图目标
        void clear();

        /// @brief 获取指定字符在指定回滚字体集合中的宽度
        /// @param c 要获取宽度的字符
        /// @param fonts 回滚字体集合, 若未指定则使用当前的环境设置
        /// @return 字符的像素宽度
        int textWidth(wchar_t c, const std::vector<std::wstring>& fonts = {});
        /// @brief 获取指定字符在指定回滚字体集合中的高度
        /// @param c 要获取高度的字符
        /// @param fonts 回滚字体集合, 若未指定则使用当前的环境设置
        /// @return 字符的像素高度
        int textHeight(wchar_t c, const std::vector<std::wstring>& fonts = {});
        /// @brief 获取指定文本在指定回滚字体集合中的宽度
        /// @param text 要获取宽度的文本
        /// @param fonts 回滚字体集合, 若未指定则使用当前的环境设置
        /// @return 文本的像素宽度
        int textWidth(const std::wstring& text, const std::vector<std::wstring>& fonts = {});
        /// @brief 获取指定文本在指定回滚字体集合中的高度
        /// @param text 要获取高度的文本
        /// @param fonts 回滚字体集合, 若未指定则使用当前的环境设置
        /// @return 文本的像素高度
        int textHeight(const std::wstring& text, const std::vector<std::wstring>& fonts = {});

        /// @brief 设置默认背景色
        /// @param color 背景色
        void setBackgroundColor(const Color& color);
        /// @brief 绑定画笔设置
        /// @param penSet 画笔设置
        void bindPenSet(PenSet* penSet);
        /// @brief 绑定画刷设置
        /// @param brushSet 画刷设置
        void bindBrushSet(BrushSet* brushSet);
        /// @brief 绑定文本设置
        /// @param textSet 文本设置
        void bindTextSet(TextSet* textSet);

        /// @brief 绘制线段
        /// @param line 线段
        void drawLine(const fLine& line);
        /// @brief 绘制矩形
        /// @param rect 矩形
        void drawRect(const fRect& rect);
        /// @brief 绘制圆角矩形
        /// @param rect 圆角矩形
        void drawRoundRect(const fRoundRect& rect);
        /// @brief 绘制椭圆弧
        /// @param rect 椭圆弧所在椭圆的外接矩形
        /// @param startAngle 起始角度
        /// @param sweepAngle 扫过角度
        void drawArc(const fRect& rect, float startAngle, float sweepAngle);
        /// @brief 绘制椭圆
        /// @param rect 椭圆
        void drawEllipse(const fEllipse& ellipse);
        /// @brief 绘制圆
        /// @param circle 圆
        void drawCircle(const fCircle& circle);
        /// @brief 绘制扇形线框
        /// @param rect 扇形所在椭圆的外接矩形
        /// @param startAngle 起始角度
        /// @param sweepAngle 扫过角度
        void drawPie(const fRect& rect, float startAngle, float sweepAngle);
        /// @brief 绘制多边形
        /// @param polygon 多边形
        void drawPolygon(const fPolygon& polygon);
        /// @brief 绘制贝塞尔曲线
        /// @param curve 贝塞尔曲线
        void drawBezier(const fBezier& curve);
        /// @brief 绘制拟合曲线
        /// @param curve 拟合曲线
        void drawFitCurve(const fFitCurve& curve);
        /// @brief 绘制路径
        /// @param path 路径
        void drawPath(const Path& path, const fPoint& pos = fPoint());

        /// @brief 填充矩形
        /// @param rect 矩形
        void drawFillRect(const fRect& rect);
        /// @brief 填充圆角矩形
        /// @param rect 圆角矩形        
        void drawFillRoundRect(const fRoundRect& rect);
        /// @brief 填充扇形
        /// @param rect 扇形所在椭圆的外接矩形
        /// @param startAngle 起始角度
        /// @param sweepAngle 扫过角度
        void drawFillPie(const fRect& rect, float startAngle, float sweepAngle);
        /// @brief 填充多边形
        /// @param points 多边形顶点坐标列表
        void drawFillPolygon(const fPolygon& polygon);
        /// @brief 填充椭圆
        /// @param rect 椭圆
        void drawFillEllipse(const fEllipse& rect);
        /// @brief 填充圆
        /// @param circle 圆
        void drawFillCircle(const fCircle& circle);
        /// @brief 填充闭合拟合曲线
        /// @param curve 拟合曲线
        void drawFillFitCurve(const fFitCurve& curve);
        /// @brief 填充闭合路径
        /// @param path 路径
        void drawFillPath(const Path& path, const fPoint& pos = fPoint());

        /// @brief 绘制位图
        /// @param pos 要绘制的位置
        /// @param pixelMap 要绘制的位图
        void drawImage(const fPoint& pos, const PixelMap& pixelMap);
        /// @brief 绘制位图
        /// @details 若源区域与目标区域的大小不一致，则会执行拉伸操作
        /// @param dest 要绘制的目标区域
        /// @param src 要绘制的区域
        /// @param pixelMap 要绘制的位图
        void drawImage(const fRect& dest, const fRect& src, const PixelMap& pixelMap);
        /// @brief 以带有透明通道的形式绘制位图
        /// @param pixelMap 要绘制的位图
        /// @param dest 要绘制的目标位置
        /// @param src 要绘制的源区域
        void drawAlphaImage(const PixelMap& pixelMap, const fPoint& dest, const fRect& src);
        /// @brief 以带有透明通道的形式绘制位图
        /// @details 若源区域与目标区域的大小不一致，则会执行拉伸操作
        /// @param pixelMap 要绘制的位图
        /// @param dest 要绘制的目标区域
        /// @param src 要绘制的源区域
        /// @param smooth 是否启用平滑处理
        void drawAlphaImage(const PixelMap& pixelMap, const fRect& dest, const fRect& src, bool smooth = false);

        /// @brief 在指定位置绘制文本
        /// @param text 要绘制的文本
        /// @param pos 要绘制的位置
        /// @param font 指定的字体集合
        /// @param show 是否显示文本, 若为false则只计算文本的宽度
        /// @return 实际绘制出的字符的像素宽度
        /// @note 若未指定字体集合则使用环境当前绑定的字体
        ///       若指定了字体集合，则会按照字体列表的顺序依次查找，
        ///       直到找到一个能显示的字体(即字体回滚机制)，此操作将忽略环境当前绑定的字体
        int drawText(const std::wstring& text, const fPoint& pos,
            const std::vector<std::wstring>& fonts = {}, bool show = true);
        /// @brief 在指定矩形区域内绘制文本
        /// @param text 要绘制的文本
        /// @param rect 要绘制的矩形区域
        /// @param flags 文本对齐方式
        /// @param font 指定的字体集合
        /// @return 实际绘制出的字符的像素宽度
        /// @note 若未指定字体集合则使用环境当前绑定的字体
        int drawText(const std::wstring& text, const fRect& rect,
            int flags = TextAlign::Left | TextAlign::Top, const std::vector<std::wstring>& fonts = {});
    };
}