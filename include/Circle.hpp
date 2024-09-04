#pragma once

#include <iostream>
#include <type_traits>
#include <numbers>

#include <private.inl>
#include <Point.hpp>


namespace GFt {
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 图形数据类型
    /// @{
        /// @class Circle
        /// @brief 圆形模板类
        /// @details 圆形模板类，用于表示圆形的几何信息，包括圆心和半径
        /// @details 此类是 基础设施库 => 图形数据类型 的一部分
        /// @tparam T 数值类型，要求为算术类型
    /// @}
    /// @}
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Circle {
        Point<T> origin_;
        T radius_;
    public:
        /// @brief 构造函数
        /// @param x 圆心 x 坐标
        /// @param y 圆心 y 坐标
        /// @param radius 半径
        constexpr explicit Circle(T x = static_cast<T>(0), T y = static_cast<T>(0), T radius = static_cast<T>(0))
            : origin_(x, y), radius_(std::abs(radius)) {}
        /// @brief 构造函数
        /// @param origin 圆心坐标
        /// @param radius 半径
        constexpr Circle(const Point<T>& origin, T radius) : origin_(origin), radius_(std::abs(radius)) {}
        constexpr Circle(const Circle&) = default;
        constexpr Circle(Circle&&) = default;
        constexpr Circle& operator=(const Circle&) = default;
        constexpr Circle& operator=(Circle&&) = default;

        /// @brief 圆心坐标
        /// @return 圆心坐标
        constexpr Point<T>& origin() { return origin_; }
        /// @brief 圆心 x 坐标
        /// @return 圆心 x 坐标
        constexpr T& x() { return origin_.x(); }
        /// @brief 圆心 y 坐标
        /// @return 圆心 y 坐标
        constexpr T& y() { return origin_.y(); }
        /// @brief 半径
        /// @return 半径
        constexpr T& radius() { return radius_; }
        /// @brief 圆心坐标的 const 版本
        /// @return 圆心坐标
        constexpr const Point<T>& origin() const { return origin_; }
        /// @brief 圆心 x 坐标的 const 版本
        /// @return 圆心 x 坐标
        constexpr const T& x() const { return origin_.x(); }
        /// @brief 圆心 y 坐标的 const 版本
        /// @return 圆心 y 坐标
        constexpr const T& y() const { return origin_.y(); }
        /// @brief 半径的 const 版本
        /// @return 半径
        constexpr const T& radius() const { return radius_; }

        /// @brief 转换此类到 bool 值
        /// @details 若半径大于 0 或圆心不为空，则返回 true，否则返回 false
        /// @return 转换结果
        constexpr explicit operator bool() const { return radius_ > 0 || static_cast<bool>(origin_); }
        /// @brief 逻辑非运算符重载
        /// @details 相当于转换到 bool 值，然后取反
        /// @return 逻辑非运算结果
        constexpr bool operator!() const { return !static_cast<bool>(*this); }

        /// @brief 等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个圆
        /// @return 相等返回 true，否则返回 false
        constexpr bool operator==(const Circle& other) const {
            if constexpr (std::numeric_limits<T>::is_integer) {
                return origin_ == other.origin_ && radius_ == other.radius_;
            }
            return origin_ == other.origin_ &&
                _GFt_private_::fsafe_equal(radius_, other.radius_);
        }
        /// @brief 不等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个圆
        /// @return 不相等返回 true，否则返回 false
        constexpr bool operator!=(const Circle& other) const { return !(*this == other); }

        /// @brief 求此圆周长
        /// @return 圆周长
        constexpr auto perimeter() const {
            constexpr auto coeff = std::numbers::pi * static_cast<T>(2);
            return coeff * radius_;
        }
        /// @brief 求此圆面积
        /// @return 圆面积
        constexpr auto area() const { return std::numbers::pi * std::pow(radius_, 2); }

        /// @brief 输出圆的信息
        /// @param os 输出流
        /// @param circle 圆
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Circle& circle) {
            os << "Circle{" << circle.origin_ << ", " << circle.radius_ << "}";
            return os;
        }
        /// @brief 转换到另一类型
        /// @tparam U 目标类型
        /// @param circle 圆
        /// @return 转换后的圆
        template<typename U>
            requires std::is_arithmetic_v<U>
        friend constexpr Circle<U> cast(const Circle<T>& circle) {
            return Circle<U>(cast<U>(circle.origin_), cast<U>(circle.radius_));
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    /// @brief 整型特化圆模板类
    /// @see Circle
    using iCircle = Circle<int>;
    /// @brief 浮点型特化圆模板类
    /// @see Circle
    using fCircle = Circle<float>;

    /// @}
    /// @}
}