#pragma once

#include <vector>

#include <GraceFt/Point.hpp>

namespace GFt {
    /// @class Bezier
    /// @brief 贝塞尔曲线
    /// @tparam T 点的类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Bezier {
        friend class Path;
        friend class Graphics;
        std::vector<Point<T>> points;
    public:
        /// @brief 默认构造函数
        Bezier() = default;
        /// @brief 构造函数
        /// @param p1 点1
        /// @param p2 点2
        /// @param c1 点1控制点
        /// @param c2 点2控制点
        Bezier(const Point<T>& p1, const Point<T>& p2, const Point<T>& c1, const Point<T>& c2) {
            points.push_back(p1);
            points.push_back(c1);
            points.push_back(c2);
            points.push_back(p2);
        }
        /// @brief 添加下一段线
        /// @param c1 新线起始点的控制点
        /// @param p  新线的结束点
        /// @param c2 新线结束点的控制点
        void addPoint(const Point<T>& c1, const Point<T>& p, const Point<T>& c2) {
            points.push_back(c1);
            points.push_back(c2);
            points.push_back(p);
        }
        /// @brief 统计点的数量
        /// @return 点的数量
        int count() const { return static_cast<int>(points.size()); }

        /// @brief 类型转换函数
        /// @tparam U 目标类型
        /// @param b 要转换的贝塞尔曲线
        /// @return 转换后的贝塞尔曲线
        template<typename U>
            requires std::is_arithmetic_v<U>
        operator Bezier<U>() const {
            Bezier<U> result;
            for (const auto& p : this->points)
                result.addPoint(p);
            return result;
        }
    };
    /// @brief 整数型贝塞尔曲线
    /// @ingroup 预定义模板特化类型
    using iBezier = Bezier<int>;
    /// @brief 浮点型贝塞尔曲线
    /// @ingroup 预定义模板特化类型
    using fBezier = Bezier<float>;
}