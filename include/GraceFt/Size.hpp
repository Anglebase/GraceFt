#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

#include <GraceFt/_private.inl>

namespace GFt {
    /// @class Size
    /// @brief 泛型尺寸类
    /// @details 此类用于表示一个矩形大小的几何信息，并提供常见几何操作
    /// @details 此类是 基础设施库 => 复合数据类型 的一部分
    /// @tparam T 点的坐标类型，要求为算术类型
    /// @ingroup 复合数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Size {
        T width_, height_;
    public:
        /// @brief 构造函数
        /// @param width 宽度
        /// @param height 高度
        /// @details 默认均初始化为 0
        constexpr explicit Size(T width = static_cast<T>(0), T height = static_cast<T>(0))
            : width_(width), height_(height) {}
        constexpr Size(const Size&) = default;
        constexpr Size(Size&&) = default;
        constexpr Size& operator=(const Size&) = default;
        constexpr Size& operator=(Size&&) = default;

        /// @brief 尺寸的宽度
        /// @return 宽度
        constexpr T& width() { return width_; }
        /// @brief 尺寸的高度
        /// @return 高度
        constexpr T& height() { return height_; }
        /// @brief 尺寸宽度的 const 版本
        /// @return 宽度
        constexpr const T& width() const { return width_; }
        /// @brief 尺寸高度的 const 版本
        /// @return 高度
        constexpr const T& height() const { return height_; }

        /// @brief 等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个尺寸对象
        /// @return 两个尺寸对象是否相等
        constexpr bool operator==(const Size& other) const {
            if constexpr (std::numeric_limits<T>::is_integer) {
                return width_ == other.width_ && height_ == other.height_;
            }
            else {
                using namespace _GFt_private_;
                return _fsafe_equal(width_, other.width_) && _fsafe_equal(height_, other.height_);
            }
        }
        /// @brief 不等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个尺寸对象
        /// @return 两个尺寸对象是否不相等
        constexpr bool operator!=(const Size& other) const { return !(*this == other); }

        /// @brief 转换尺寸到 bool 值
        /// @details 若 width 或 height 不全为 0，则返回 true，否则返回 false
        /// @return 转换结果
        constexpr explicit operator bool() const { return width_ != static_cast<T>(0) || height_ != static_cast<T>(0); }
        /// @brief 逻辑非运算符重载
        /// @details 若 width 或 height 不全为 0，则返回 false，否则返回 true
        /// @return 逻辑非运算结果
        constexpr bool operator!() const { return !static_cast<bool>(*this); }

        /// @brief 加法运算符重载
        /// @param other 另一个尺寸对象
        /// @return 两个尺寸对象的和
        constexpr Size operator+(const Size& other) const { return Size(width_ + other.width_, height_ + other.height_); }
        /// @brief 减法运算符重载
        /// @param other 另一个尺寸对象
        /// @return 两个尺寸对象的差
        constexpr Size operator-(const Size& other) const { return Size(width_ - other.width_, height_ - other.height_); }
        /// @brief 乘法运算符重载
        /// @param scalar 标量值
        /// @return 尺寸对象乘以标量后的结果
        constexpr Size operator*(T scalar) const { return Size(width_ * scalar, height_ * scalar); }
        /// @brief 乘法运算符重载
        /// @param scalar 标量值
        /// @return 标量值乘以尺寸对象后的结果
        friend constexpr Size operator*(T scalar, const Size& size) { return Size(size.width_ * scalar, size.height_ * scalar); }
        /// @brief 除法运算符重载
        /// @param scalar 标量值
        /// @return 尺寸对象除以标量后的结果
        constexpr Size operator/(T scalar) const { return Size(width_ / scalar, height_ / scalar); }

        /// @brief 加且赋值运算符重载
        /// @param other 另一个尺寸对象
        /// @return 尺寸对象加上另一个尺寸对象后的结果
        constexpr Size& operator+=(const Size& other) {
            *this = *this + other;
            return *this;
        }
        /// @brief 减且赋值运算符重载
        /// @param other 另一个尺寸对象
        /// @return 尺寸对象减去另一个尺寸对象后的结果
        constexpr Size& operator-=(const Size& other) {
            *this = *this - other;
            return *this;
        }
        /// @brief 乘且赋值运算符重载
        /// @param scalar 标量值
        /// @return 尺寸对象乘以标量后的结果
        constexpr Size& operator*=(T scalar) {
            *this = *this * scalar;
            return *this;
        }
        /// @brief 除且赋值运算符重载
        /// @param scalar 标量值
        /// @return 尺寸对象除以标量后的结果
        constexpr Size& operator/=(T scalar) {
            *this = *this / scalar;
            return *this;
        }

        /// @brief 负号运算符重载
        /// @return 尺寸对象的取反结果
        constexpr Size operator-() const { return Size(-width_, -height_); }
        /// @brief 正号运算符重载
        /// @return 尺寸对象本身
        constexpr Size operator+() const { return *this; }

        /// @brief 求此尺寸的周长
        /// @return 尺寸的周长
        constexpr T perimeter() const { return 2 * (width_ + height_); }
        /// @brief 求尺寸的面积
        /// @return 尺寸的面积
        constexpr T area() const { return width_ * height_; }

        /// @brief 流操作符重载
        /// @param os 输出流
        /// @param size 尺寸对象
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Size& size) {
            os << "[" << size.width_ << ", " << size.height_ << "]";
            return os;
        }

        /// @brief 类型转换函数
        /// @tparam U 目标类型
        /// @return 转换后的尺寸对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        constexpr operator Size<U>() const {
            return Size<U>(static_cast<U>(this->width_), static_cast<U>(this->height_));
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    /// @brief 整数型尺寸
    /// @details 用于表示一个二维坐标尺寸，其坐标数据类型为 int
    /// @see Size
    using iSize = Size<int>;
    /// @brief 浮点型尺寸
    /// @details 用于表示一个二维坐标尺寸，其坐标数据类型为 float
    /// @see Size
    using fSize = Size<float>;

    /// @}
    /// @}
}