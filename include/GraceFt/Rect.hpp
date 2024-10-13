#pragma once

#include <iostream>
#include <type_traits>

#include <GraceFt/Point.hpp>
#include <GraceFt/Size.hpp>


namespace GFt {
    /// @defgroup 基础设施库
    
    /// @defgroup 图形数据类型
    /// @ingroup 基础设施库

    /// @class Rect
    /// @brief 矩形模板类
    /// @details 矩形模板类，用于表示矩形的几何信息，包括位置和大小
    /// @details 此类是 基础设施库 => 图形数据类型 的一部分
    /// @tparam T 数值类型，要求为算术类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Rect {
        Point<T> pos_;
        Size<T> size_;
    public:
        /// @brief 构造函数
        /// @param x 矩形左上角的x坐标
        /// @param y 矩形左上角的y坐标
        /// @param width 矩形的宽度
        /// @param height 矩形的高度
        constexpr explicit Rect(
            T x = static_cast<T>(0), T y = static_cast<T>(0),
            T width = static_cast<T>(0), T height = static_cast<T>(0)
        ) : pos_(x, y), size_(width, height) {}
        /// @brief 构造函数
        /// @param pos 矩形左上角的坐标
        /// @param size 矩形的大小
        constexpr Rect(const Point<T>& pos, const Size<T>& size) : pos_(pos), size_(size) {}
        /// @brief 构造函数
        /// @param size 矩形的大小
        /// @details 只从矩形的大小构造矩形，矩形左上角的坐标为 (0, 0)
        constexpr Rect(const Size<T>& size) : pos_(static_cast<T>(0), static_cast<T>(0)), size_(size) {}
        constexpr Rect(const Rect<T>& other) = default;
        constexpr Rect(Rect<T>&& other) = default;
        constexpr Rect<T>& operator=(const Rect<T>& other) = default;
        constexpr Rect<T>& operator=(Rect<T>&& other) = default;

        /// @brief 矩形位置的 x 坐标
        /// @return 坐标值
        constexpr T& x() { return pos_.x(); }
        /// @brief 矩形位置的 y 坐标
        /// @return 坐标值
        constexpr T& y() { return pos_.y(); }
        /// @brief 矩形宽度
        /// @return 宽度值
        constexpr T& width() { return size_.width(); }
        /// @brief 矩形高度
        /// @return 高度值
        constexpr T& height() { return size_.height(); }
        /// @brief 矩形位置的 x 坐标的 const 版本
        /// @return 坐标值
        constexpr const T& x() const { return pos_.x(); }
        /// @brief 矩形位置的 y 坐标的 const 版本
        /// @return 坐标值
        constexpr const T& y() const { return pos_.y(); }
        /// @brief 矩形宽度的 const 版本
        /// @return 宽度值
        constexpr const T& width() const { return size_.width(); }
        /// @brief 矩形高度的 const 版本
        /// @return 高度值
        constexpr const T& height() const { return size_.height(); }

        /// @brief 矩形左上角的坐标
        /// @return 坐标值
        constexpr Point<T>& position() { return pos_; }
        /// @brief 矩形大小
        /// @return 大小值
        constexpr Size<T>& size() { return size_; }
        /// @brief 矩形左上角的坐标的 const 版本
        /// @return 坐标值
        constexpr const Point<T>& position() const { return pos_; }
        /// @brief 矩形大小的 const 版本
        /// @return 大小值
        constexpr const Size<T>& size() const { return size_; }
        /// @brief 矩形的左侧边界坐标
        /// @return 坐标值
        constexpr T left() const { return pos_.x(); }
        /// @brief 矩形的上侧边界坐标
        /// @return 坐标值
        constexpr T top() const { return pos_.y(); }
        /// @brief 矩形的右侧边界坐标
        /// @return 坐标值
        constexpr T right() const { return pos_.x() + size_.width(); }
        /// @brief 矩形的下侧边界坐标
        /// @return 坐标值
        constexpr T bottom() const { return pos_.y() + size_.height(); }

        /// @brief 等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个矩形对象
        /// @return 相等返回 true，否则返回 false
        constexpr bool operator==(const Rect<T>& other) const {
            return pos_ == other.pos_ && size_ == other.size_;
        }
        /// @brief 不等于比较运算符重载
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个矩形对象
        /// @return 不相等返回 true，否则返回 false
        constexpr bool operator!=(const Rect<T>& other) const {
            return pos_ != other.pos_ || size_ != other.size_;
        }

        /// @brief 将矩形转换到 bool 值
        /// @details 矩形位置和大小转换到 bool 值时，均为 false 则返回 false，否则返回 true
        /// @return 转换结果
        constexpr explicit operator bool() const { return static_cast<bool>(size_) || static_cast<bool>(pos_); }
        /// @brief 逻辑非运算符重载
        /// @details 相当于转化为 bool 值再取反
        /// @return 逻辑非运算结果
        constexpr bool operator!() const { return !static_cast<bool>(*this); }

        /// @brief 矩形的中心点坐标
        /// @return 坐标值
        constexpr Point<T> center() const {
            return Point<T>(pos_.x() + size_.width() / static_cast<T>(2), pos_.y() + size_.height() / static_cast<T>(2));
        }
        /// @brief 计算给定尺寸的居中矩形
        /// @param size 矩形的大小
        /// @return 矩形对象
        constexpr Rect<T> centerby(const Size<T>& size) const {
            return Rect<T>(center() - Point<T>(size.width(), size.height()) / static_cast<T>(2), size);
        }
        /// @brief 规范化矩形数据
        /// @details 确保矩形的宽度和高度都不小于 0
        constexpr void normalize() {
            if (size_.width() < static_cast<T>(0)) {
                size_.width() = -size_.width();
                pos_.x() -= size_.width();
            }
            if (size_.height() < static_cast<T>(0)) {
                size_.height() = -size_.height();
                pos_.y() -= size_.height();
            }
        }

        /// @brief 流操作符重载
        /// @param os 输出流
        /// @param rect 矩形对象
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Rect<T>& rect) {
            os << "Rect{" << rect.pos_ << ", " << rect.size_ << "}";
            return os;
        }

        /// @brief 矩形类型转换函数
        /// @tparam U 目标类型
        /// @return 转换后的矩形对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        constexpr operator Rect<U>() const {
            return Rect<U>(this->pos_, this->size_);
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    /// @brief 整数型矩形类型
    /// @see Rect
    using iRect = Rect<int>;
    /// @brief 浮点型矩形类型
    /// @see Rect
    using fRect = Rect<float>;

    /// @}
    /// @}
}