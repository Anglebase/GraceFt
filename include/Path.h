#pragma once

#include <vector>

#include <Circle.hpp>
#include <Ellipse.hpp>
#include <Bezier.hpp>
#include <FitCurve.hpp>
#include <Polygon.hpp>
#include <Font.h>
#include <Line.hpp>
#include <Matrix.hpp>

namespace GFt {
    /// @class Path
    /// @brief 路径类
    /// @details 用于绘制图形，可以包含多种图元，如直线、圆弧、贝塞尔曲线、多边形等
    /// @ingroup 接口类型
    class Path {
        void* data_;
    public:
        /// @brief 默认构造函数
        Path();
        Path(const Path& other);
        Path(Path&& other);
        Path& operator=(const Path& other);
        Path& operator=(Path&& other);
        ~Path();

        /// @brief 开始一个新的图元
        void start();
        /// @brief 闭合当前图元
        void close();
        /// @brief 闭合所有未闭合的图元
        void closeAll();
        /// @brief 清空路径
        void reset();
        /// @brief 反转路径
        void reverse();
        /// @brief 转变为图形的轮廓线
        void outline();

        /// @brief 获取路径的最后一个点
        /// @return 路径的最后一个点
        fPoint getLastPoint() const;
        /// @brief 计算路径共有多少个控制点
        /// @return 路径控制点的数量
        int count() const;
        /// @brief 获取路径的最小外接矩形
        /// @details 所得的外接矩形是经过变换后的路径的最小外接矩形
        /// @param transform 变换矩阵, 默认为单位矩阵
        /// @return 路径的最小外接矩形
        fRect getBounds(const fMat2x2& transform = fMat2x2::I()) const;

        /// @brief 向路径中添加路径
        /// @param other 要添加的路径
        /// @param connect 是否连接两个路径(仅在路径未闭合时有效)
        void addPath(const Path& other, bool connect = false);
        /// @brief 向路径中添加直线
        /// @param line 直线
        void addLine(const fLine& line);
        /// @brief 向路径中添加圆弧
        /// @param rect 圆弧所在矩形
        /// @param startAngle 圆弧起始角度
        /// @param sweepAngle 圆弧扫过角度
        void addArc(const fRect& rect, float startAngle, float sweepAngle);

        /// @brief 向路径中添加圆
        /// @param circle 圆
        void addCircle(const fCircle& circle);
        /// @brief 向路径中添加矩形
        /// @param rect 矩形
        void addRect(const fRect& rect);
        /// @brief 向路径中添加椭圆
        /// @param ellipse 椭圆
        void addEllipse(const fEllipse& ellipse);
        /// @brief 向路径中添加扇形
        /// @param rect 扇形所在矩形
        /// @param startAngle 扇形起始角度
        /// @param sweepAngle 扇形扫过角度
        void addPie(const fRect& rect, float startAngle, float sweepAngle);

        /// @brief 向路径中添加贝塞尔曲线
        /// @param bezier 贝塞尔曲线
        void addBezier(const fBezier& bezier);
        /// @brief 向路径中添加拟合曲线
        /// @param fitCurve 拟合曲线
        void addFitCurve(const fFitCurve& fitCurve);
        /// @brief 向路径中添加多边形
        /// @param points 多边形的点集
        void addPolygon(const fPolygon& points);

        /// @brief 向路径中添加文本
        /// @param text 文本内容
        /// @param position 文本位置
        /// @param font 字体
        void addText(const std::wstring& text, const fPoint& position, const Font& font = Font(L"宋体"));
    };
};