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
        friend class Path;
        friend class Graphics;
        std::vector<Point<T>> points;
        bool closed = false;
        float tension = 0.25f;
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
        /// @brief 设置拟合曲线的张力
        /// @param tension 张力
        void setTension(float tension) { this->tension = tension; }
        /// @brief 拟合曲线是否闭合
        /// @return 是否闭合
        bool isClosed() const { return closed; }
        /// @brief 拟合曲线的张力
        /// @return 张力
        float getTension() const { return tension; }
        /// @brief 控制点的数量
        /// @return 控制点的数量
        int count() const { return static_cast<int>(points.size()); }

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
        operator FitCurve<U>() const {
            FitCurve<U> result;
            for (const auto& point : this->points)
                result.addPoint(Point<U>(point.x, point.y));
            result.closed = this->closed;
            return result;
        }
    };

    /// @brief 整数型拟合曲线
    /// @ingroup 预定义模板特化类型
    using iFitCurve = FitCurve<int>;
    /// @brief 浮点型拟合曲线
    /// @ingroup 预定义模板特化类型
    using fFitCurve = FitCurve<float>;
}