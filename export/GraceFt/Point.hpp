#pragma once
/// @file Point.hpp

#include <iostream>
#include <cmath>
#include <type_traits>

#include <_private.inl>
#include <GraceFt/Matrix.hpp>

/// @namespace GFt
/// @brief GraceFt库的命名空间
namespace GFt {
    /// @class Point
    /// @brief 泛型点类
    /// @details 此类用于表示一个二维坐标点的几何信息，并提供了常用的几何操作
    /// @details 此类是 基础设施库 => 复合数据类型 的一部分
    /// @tparam T 点的坐标类型，要求为算术类型
    /// @ingroup 复合数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Point {
        T x_, y_;
    public:
        /// @brief 构造函数
        /// @param x x 坐标
        /// @param y y 坐标
        constexpr explicit Point(T x = static_cast<T>(0), T y = static_cast<T>(0)) : x_(x), y_(y) {}
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
        /// @details 此函数对于浮点数比较是安全的
        /// @param p 另一个点对象
        /// @return 两个点是否相等
        constexpr bool operator==(const Point& p) const {
            if constexpr (std::numeric_limits<T>::is_integer) {
                return x_ == p.x_ && y_ == p.y_;
            }
            else {
                using namespace _GFt_private_;
                return _fsafe_equal(x_, p.x_) && _fsafe_equal(y_, p.y_);
            }
        }
        /// @brief 不等于判断操作符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param p 另一个点对象
        /// @return 两个点是否不相等
        constexpr bool operator!=(const Point& p) const { return !(*this == p); }

        /// @brief 将点转换到 bool 值
        /// @details 若 x 和 y 坐标不全为 0，则返回 true，否则返回 false
        /// @return 转化后的 bool 值
        constexpr explicit operator bool() const { return x_ != static_cast<T>(0) || y_ != static_cast<T>(0); }
        /// @brief 逻辑非操作符重载
        /// @details 若 x 和 y 坐标不全为 0，则返回 false，否则返回 true
        /// @return 逻辑非后的 bool 值
        constexpr bool operator!() const { return !static_cast<bool>(*this); }

        /// @brief 乘法操作符重载(点积)
        /// @details 这相当于两个二维向量的点积
        /// @param p 另一个点对象
        /// @return 两个点的点积
        constexpr T operator*(const Point& p) const { return x_ * p.x_ + y_ * p.y_; }

        /// @brief 计算模长
        /// @details 这相当于二维向量的模长(即|p|)
        /// @return 点的模长
        constexpr auto norm() const { return std::sqrt(x_ * x_ + y_ * y_); }
        /// @brief 计算相角(弧度制)
        /// @details 这相当于复数 z=x+iy 的辐角主值 arg(z) (弧度制)
        /// @return 点的相角(弧度制)
        constexpr auto angle() const { return std::atan2(y_, x_); }

        /// @brief 计算点之间的距离
        /// @details 此函数求得两个点之间的欧氏距离
        /// @param p1 第一个点对象
        /// @param p2 第二个点对象
        /// @return 两个点之间的距离
        constexpr friend auto distance(const Point& p1, const Point& p2) { return (p1 - p2).norm(); }
        /// @brief Point<U> 类型转换函数
        /// @details 用于将 Point<T> 类型转换为 Point<U> 类型
        /// @tparam U 坐标转换的目标类型，要求为算术类型
        /// @return 转换后的点对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        constexpr operator Point<U>() const {
            return Point<U>(static_cast<U>(this->x_), static_cast<U>(this->y_));
        }
        /// @brief Vec2<T> 类型转换函数
        /// @details 用于将 Point<T> 类型转换为 Vec2<T> 类型
        /// @tparam T 坐标转换的目标类型，要求为算术类型
        /// @return 转换后的 Vec2 对象
        constexpr operator Vec2<T>() const {
            Vec2<T> v;
            v[0][0] = x_;
            v[0][1] = y_;
            return v;
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    /// @brief 整数型点类别别名
    /// @details 用于表示一个二维坐标点，其坐标数据类型为 int
    /// @see Point
    using iPoint = Point<int>;
    /// @brief 浮点型点类别别名
    /// @details 用于表示一个二维坐标点，其坐标数据类型为 float
    /// @see Point
    using fPoint = Point<float>;

    /// @}
    /// @}
}