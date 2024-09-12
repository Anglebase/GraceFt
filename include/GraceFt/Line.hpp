#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>
#include <_private.inl>

#include <Point.hpp>

namespace GFt {
    /// @class Line
    /// @brief 几何线模板类
    /// @details 用于表示直线的类模板
    /// @tparam T 点的坐标类型，要求为算术类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Line {
        Point<T> p1, p2;
    public:
        /// @brief 构造函数
        /// @param p1 直线上的一点
        /// @param p2 直线上的另一点
        constexpr Line(const Point<T>& p1, const Point<T>& p2) : p1(p1), p2(p2) {}

        /// @brief 获取直线的锚定点1
        /// @return 直线的锚定点1
        constexpr Point<T>& P1() { return p1; }
        /// @brief 获取直线的锚定点2
        /// @return 直线的锚定点2
        constexpr Point<T>& P2() { return p2; }
        /// @brief 获取直线的锚定点1的 const 版本
        /// @return 直线的锚定点1
        constexpr const Point<T>& P1() const { return p1; }
        /// @brief 获取直线的锚定点2的 const 版本
        /// @return 直线的锚定点2
        constexpr const Point<T>& P2() const { return p2; }

        /// @brief 判断直线是否有效
        /// @return 直线是否有效
        constexpr explicit operator bool() const { return p1 != p2; }
        /// @brief 逻辑非运算符重载
        /// @details 效果同 operator bool() const 的结果取反
        /// @return 逻辑非运算结果
        constexpr bool operator!() const { return!static_cast<bool>(*this); }
        /// @brief 判断两个直线对象是否相同
        /// @param other 另一个直线对象
        /// @return 两个直线对象是否相同
        constexpr bool operator==(const Line<T>& other) const { return p1 == other.p1 && p2 == other.p2; }
        /// @brief 判断两个直线对象是否不同
        /// @param other 另一个直线对象
        /// @return 两个直线对象是否不同
        constexpr bool operator!=(const Line<T>& other) const { return p1 != other.p1 || p2 != other.p2; }

        /// @brief 计算给定的两个锚定点之间的欧式距离
        /// @return 两个锚定点之间的距离
        constexpr auto distance() const { return (p2 - p1).norm(); }
        /// @brief 计算给定的两个锚定点之间的曼哈顿距离
        /// @return 两个锚定点之间的距离
        constexpr auto manhatten_distance() const {
            Point<T> diff = p2 - p1;
            return std::abs(diff.x()) + std::abs(diff.y());
        }
        /// @brief 判断此直线是否与另一个直线共线
        /// @param other 另一个直线对象
        /// @return 两个直线是否共线
        constexpr bool isCollinearWith(const Line<T>& other) const {
            using namespace _GFt_private_;
            if (!(*this))
                return false;
            auto tdx = p2.x() - p1.x();
            auto tdy = p2.y() - p1.y();
            auto odx = other.p2.x() - other.p1.x();
            auto ody = other.p2.y() - other.p1.y();
            bool ret = false;
            if constexpr (std::is_floating_point_v<T>) {
                if (_fsafe_equal(tdx, static_cast<T>(0)) && _fsafe_equal(ody, static_cast<T>(0)))
                    return p2.x() == other.p2.x();
                if (_fsafe_equal(tdx, static_cast<T>(0)) || _fsafe_equal(ody, static_cast<T>(0)))
                    return false;
                auto tk = tdy / tdx;
                auto ok = ody / odx;
                ret = _fsafe_equal(tk, ok)
                    && _fsafe_equal(
                        p1.y() - p1.x() * tk,
                        other.p1.y() - other.p1.x() * ok
                    );
            }
            else {
                if (tdx == 0 && odx == 0)
                    return p2.x() == other.p2.x();
                if (tdx == 0 || odx == 0)
                    return false;
                double tk = tdy / static_cast<double>(tdx);
                double ok = ody / static_cast<double>(odx);
                ret = _fsafe_equal(tk, ok)
                    && _fsafe_equal(
                        p1.y() - p1.x() * tk,
                        other.p1.y() - other.p1.x() * ok
                    );
            }
            return ret;
        }
        /// @brief 流操作运算符重载
        /// @param os 输出流对象
        /// @param line 直线对象
        /// @return 输出流对象 os
        friend std::ostream& operator<<(std::ostream& os, const Line<T>& line) {
            os << "Line{" << line.p1 << ", " << line.p2 << "}";
            return os;
        }
        /// @brief 类型转换函数模板
        /// @tparam U 目标类型
        /// @param line 要转换的直线对象
        /// @return 转换后的直线对象
        template<typename U>
        constexpr operator Line<U>() const {
            return Line<U>(this->p1, this->p2);
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    /// @typedef iLine
    /// @brief 整数型直线类型
    /// @details 用于表示整数型直线的类型别名
    using iLine = Line<int>;
    /// @typedef fLine
    /// @brief 浮点型直线类型
    /// @details 用于表示浮点型直线的类型别名
    using fLine = Line<float>;

    /// @}
    /// @}
}