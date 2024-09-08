#pragma once

#include <iostream>
#include <Rect.hpp>

namespace GFt {
    /// @class Elliptic
    /// @brief 椭圆类
    /// @tparam T 数值类型, 要求为算术类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class Elliptic {
        Rect<T> rect_;
    public:
        /// @brief 构造函数
        /// @param rect 椭圆的外接矩形
        constexpr Elliptic(const Rect<T>& rect) : rect_(rect) { rect.normalize(); }
        /// @brief 构造函数
        /// @param center 椭圆的中心点
        /// @param rx 椭圆的水平半径
        /// @param ry 椭圆的竖直半径
        constexpr Elliptic(const Point<T>& center, T rx, T ry)
            : rect_(center.x - rx, center.y - ry, 2 * rx, 2 * ry) {
            rect_.normalize();
        }
        /// @brief 判断两个椭圆是否相同
        /// @param other 另一个椭圆
        /// @return 若两个椭圆相同, 则返回 true, 否则返回 false
        constexpr bool operator==(const Elliptic<T>& other) const { return rect_ == other.rect_; }
        /// @brief 判断两个椭圆是否不同
        /// @param other 另一个椭圆
        /// @return 若两个椭圆不同, 则返回 true, 否则返回 false
        constexpr bool operator!=(const Elliptic<T>& other) const { return !(*this == other); }

        /// @brief 椭圆的外接矩形
        /// @return 椭圆的外接矩形
        constexpr const Rect<T>& rect() const { return rect_; }
        /// @brief 椭圆的宽度
        /// @return 椭圆的宽度
        constexpr T width() const { return rect_.width(); }
        /// @brief 椭圆的高度
        /// @return 椭圆的高度
        constexpr T height() const { return rect_.height(); }
        /// @brief 椭圆的圆心
        /// @return 椭圆的圆心
        constexpr Point<T> center() const { return rect_.center(); }
        /// @brief 椭圆的水平半径
        /// @return 椭圆的水平半径
        constexpr T rx() const { return rect_.width() / 2; }
        /// @brief 椭圆的竖直半径
        /// @return 椭圆的竖直半径
        constexpr T ry() const { return rect_.height() / 2; }
        /// @brief 椭圆的面积
        /// @return 椭圆的面积
        constexpr auto area() const { return std::numbers::pi * (rect_.width() / 2) * (rect_.height() / 2); }

        /// @brief 流操作运算符
        /// @param os 输出流
        /// @param elliptic 椭圆
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Elliptic<T>& elliptic) {
            os << "Elliptic(" << elliptic.rect_ << ")";
            return os;
        }
        /// @brief 类型转换函数
        /// @tparam U 目标类型
        /// @param elliptic 椭圆
        /// @return 目标类型椭圆
        template<typename U>
            requires std::is_arithmetic_v<U>
        friend Elliptic<U> cast(const Elliptic<T>& elliptic) {
            return Elliptic<U>(cast<U>(elliptic.rect_));
        }
    };
}