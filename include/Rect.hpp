#pragma once

#include <iostream>
#include <type_traits>

#include <Point.hpp>
#include <Size.hpp>

namespace GFt {
    /// @class Rect
    /// @brief 矩形模板类
    /// @details 矩形模板类，用于表示矩形的位置和大小
    /// @tparam T 数值类型，要求为算术类型
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
    };

    /// @brief 整数型矩形类型
    using iRect = Rect<int>;
    /// @brief 浮点型矩形类型
    using fRect = Rect<float>;
}