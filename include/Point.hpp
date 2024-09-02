#pragma once
/// @file Point.hpp

#include <iostream>
#include <cmath>
#include <type_traits>

/// @namespace GFt
/// @brief GraceFt库的命名空间。
namespace GFt {
    /// @class Point
    /// @brief 泛型点类
    /// @details 此类用于表示一个二维坐标点，其坐标数据类型由模板参数 T 指定
    /// @tparam T 点的坐标类型，要求为算术类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Point {
        T x_, y_;
    public:
        /// @brief 构造函数
        /// @param x x 坐标
        /// @param y y 坐标
        constexpr Point(T x = 0, T y = 0) : x_(x), y_(y) {}
        constexpr Point(const Point& p) = default;
        constexpr Point(Point&& p) = default;
        constexpr Point& operator=(const Point& p) = default;
        constexpr Point& operator=(Point&& p) = default;

        /// @brief 点的 x 坐标
        /// @return x 坐标
        constexpr T& x() { return x_; }
        /// @brief 点的 y 坐标
        /// @return y 坐标
        constexpr T& y() { return y_; }

        /// @brief 函数 x() 的 const 版本
        /// @return x 坐标
        /// @see x()
        constexpr const T& x() const { return x_; }
        /// @brief 函数 y() 的 const 版本
        /// @return y 坐标
        /// @see y()
        constexpr const T& y() const { return y_; }

        /// @brief 流操作符重载
        /// @param os 输出流
        /// @param p 点对象
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Point& p) {
            os << "(" << p.x_ << ", " << p.y_ << ")";
            return os;
        }

        /// @brief 加法操作符重载
        /// @details 这相当于两个二维向量的加法
        /// @param p 另一个点对象
        /// @return 两个点的和
        constexpr Point operator+(const Point& p) const { return Point(x_ + p.x_, y_ + p.y_); }
        /// @brief 减法操作符重载
        /// @details 这相当于两个二维向量的减法
        /// @param p 另一个点对象
        /// @return 两个点的差
        constexpr Point operator-(const Point& p) const { return Point(x_ - p.x_, y_ - p.y_); }
        /// @brief 乘法操作符重载
        /// @details 这相当于二维向量的数乘
        /// @param k 一个标量
        /// @return 数乘后的点
        constexpr Point operator*(T k) const { return Point(x_ * k, y_ * k); }
        /// @brief 除法操作符重载
        /// @details 这相当于二维向量的数乘
        /// @param k 一个标量
        /// @return 数乘(1/k)后的点
        constexpr Point operator/(T k) const { return Point(x_ / k, y_ / k); }

        /// @brief 加且赋值操作符重载
        /// @details 如同 this = this + p
        /// @param p 另一个点对象
        /// @return 自身
        constexpr Point& operator+=(const Point& p) {
            *this = *this + p;
            return *this;
        }
        /// @brief 减且赋值操作符重载
        /// @details 如同 this = this - p
        /// @param p 另一个点对象
        /// @return 自身
        constexpr Point& operator-=(const Point& p) {
            *this = *this - p;
            return *this;
        }
        /// @brief 乘且赋值操作符重载
        /// @details 如同 this = this * k
        /// @param k 一个标量
        /// @return 自身
        constexpr Point& operator*=(T k) {
            *this = *this * k;
            return *this;
        }
        /// @brief 除且赋值操作符重载
        /// @details 如同 this = this / k
        /// @param k 一个标量
        /// @return 自身
        constexpr Point& operator/=(T k) {
            *this = *this / k;
            return *this;
        }

        /// @brief 等于判断操作符重载
        /// @param p 另一个点对象
        /// @return 两个点是否相等
        constexpr bool operator==(const Point& p) const { return x_ == p.x_ && y_ == p.y_; }
        /// @brief 不等于判断操作符重载
        /// @param p 另一个点对象
        /// @return 两个点是否不相等
        constexpr bool operator!=(const Point& p) const { return !(*this == p); }

        /// @brief 乘法操作符重载(点积)
        /// @details 这相当于两个二维向量的点积
        /// @param p 另一个点对象
        /// @return 两个点的点积
        constexpr T operator*(const Point& p) const { return x_ * p.x_ + y_ * p.y_; }

        /// @brief 计算模长
        /// @details 这相当于二维向量的模长(欧氏距离,|p|)
        /// @return 点的模长
        constexpr auto norm() const { return std::sqrt(x_ * x_ + y_ * y_); }
        /// @brief 计算点之间的距离
        /// @param p 另一个点对象
        /// @return 两个点之间的距离
        constexpr auto distance(const Point& p) const { return (p - *this).norm(); }
        /// @brief 计算相角(弧度制)
        /// @details 这相当于复数 z=x+iy 的辐角主值 arg(z) (弧度制)
        /// @param p 另一个点对象
        /// @return 两个点的相角(弧度制)
        constexpr auto angle() const { return std::atan2(y_, x_); }

        /// @brief Point<U> 类型转换函数
        /// @details 用于将 Point<T> 类型转换为 Point<U> 类型
        /// @tparam U 坐标转换的目标类型，要求为算术类型
        /// @param p 原始点对象
        /// @return 转换后的点对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        friend constexpr Point<U> cast(const Point<T>& p) {
            return Point<U>(static_cast<U>(p.x_), static_cast<U>(p.y_));
        }
    };

    using iPoint = Point<int>;     ///< 整数型点类别名
    using fPoint = Point<float>;   ///< 浮点型点类别名
}