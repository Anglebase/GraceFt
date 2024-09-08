#pragma once

#include <vector>
#include <iostream>

#include <Point.hpp>

namespace GFt {
    /// @class FitCurve
    /// @brief 拟合曲线类
    /// @tparam T 点的坐标类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class FitCurve {
        std::vector<Point<T>> points;
        bool closed = false;
    public:
        /// @brief 默认构造函数
        FitCurve() = default;
        /// @brief 构造函数
        /// @param points 点集
        FitCurve(const std::vector<Point<T>>& points) : points(points) {}

        /// @brief 添加点
        /// @param point 点
        void addPoint(const Point<T>& point) { points.push_back(point); }
        /// @brief 设置拟合曲线是否闭合
        /// @param closed 是否闭合
        void setClosed(bool closed) { this->closed = closed; }
        /// @brief 拟合曲线是否闭合
        /// @return 是否闭合
        bool isClosed() const { return closed; }

        /// @brief 流操作符重载
        /// @param os 输出流
        /// @param curve 拟合曲线
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const FitCurve<T>& curve) {
            os << "FitCurve: " << &curve;
            return os;
        }
        /// @brief 类型转换函数
        /// @tparam U 目标类型
        /// @param curve 拟合曲线
        /// @return 拟合曲线
        template<typename U>
            requires std::is_arithmetic_v<U>
        friend FitCurve<U> cast(const FitCurve<T>& curve) {
            FitCurve<U> result;
            for (const auto& point : curve.points)
                result.addPoint(Point<U>(point.x, point.y));
            result.closed = curve.closed;
            return result;
        }
    };

    using iFitCurve = FitCurve<int>;
    using fFitCurve = FitCurve<float>;
}