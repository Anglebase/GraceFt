#pragma once

#include <vector>
#include <iostream>

#include <GraceFt/Point.hpp>

namespace GFt {
    /// @class Polygon
    /// @brief 多边形类
    /// @tparam T 点坐标类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Polygon {
        friend class Path;
        friend class Graphics;
        std::vector<Point<T>> points;
        bool closed = true;
    public:
        /// @brief 默认构造函数
        Polygon() = default;
        /// @brief 构造函数
        /// @param points 多边形顶点
        Polygon(std::vector<Point<T>> points) : points(points) {}

        /// @brief 向多边形中添加点
        void addPoint(Point<T> point) { points.push_back(point); }
        /// @brief 计算多边形点的数量
        std::size_t count() const { return points.size(); }

        /// @brief 设置多边形是否闭合
        /// @param closed 是否闭合
        void setClosed(bool closed) { this->closed = closed; }
        /// @brief 获取多边形是否闭合
        /// @details 默认情况下，多边形是闭合的
        /// @return 是否闭合
        bool isClosed() const { return closed; }

        /// @brief 流操作符重载
        /// @param os 输出流
        /// @param polygon 多边形对象
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Polygon<T>& polygon) {
            os << "Polygon(" << &polygon << ")";
            return os;
        }

        /// @brief 类型转换函数模板
        /// @tparam U 目标类型
        /// @param polygon 多边形对象
        /// @return 转换后的多边形对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        operator Polygon<U>() const {
            Polygon<U> result;
            for (const auto& point : this->points)
                result.addPoint(point);
            result.setClosed(this->isClosed());
            return result;
        }
    };

    /// @brief 整数多边形类型
    /// @ingroup 预定义模板特化类型
    using iPolygon = Polygon<int>;
    /// @brief 浮点数多边形类型
    /// @ingroup 预定义模板特化类型
    using fPolygon = Polygon<float>;
}