#pragma once

#include <iostream>

#include <Rect.hpp>

namespace GFt {
    /// @class RoundRect
    /// @brief 圆角矩形类
    /// @tparam T 数值类型
    /// @ingroup 图形数据类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    class RoundRect {
        Rect<T> rect_;
        T lt, rt, rb, lb;
    public:
        /// @brief 构造函数
        /// @param rect 矩形
        /// @param rad 圆角半径
        constexpr RoundRect(const Rect<T>& rect, T rad)
            : rect_(rect), lt(rad), rt(rad), rb(rad), lb(rad) {
            rect.normalize();
        }

        /// @brief 圆角矩形所在矩形
        /// @return 矩形
        constexpr const Rect<T>& rect() const { return rect_; }
        /// @brief 圆角矩形左上角圆角半径
        /// @return 半径
        constexpr T& radiusTopLeft() { return lt; }
        /// @brief 圆角矩形右上角圆角半径
        /// @return 半径
        constexpr T& radiusTopRight() { return rt; }
        /// @brief 圆角矩形右下角圆角半径
        /// @return 半径
        constexpr T& radiusBottomRight() { return rb; }
        /// @brief 圆角矩形左下角圆角半径
        /// @return 半径
        constexpr T& radiusBottomLeft() { return lb; }
        /// @brief 圆角矩形左上角圆角半径 (const)
        /// @return 半径 (const)
        constexpr const T& radiusTopLeft() const { return lt; }
        /// @brief 圆角矩形右上角圆角半径 (const)
        /// @return 半径 (const)
        constexpr const T& radiusTopRight() const { return rt; }
        /// @brief 圆角矩形右下角圆角半径 (const)
        /// @return 半径 (const)
        constexpr const T& radiusBottomRight() const { return rb; }
        /// @brief 圆角矩形左下角圆角半径 (const)
        /// @return 半径 (const)
        constexpr const T& radiusBottomLeft() const { return lb; }

        /// @brief 判断两个圆角矩形是否相同
        /// @param other 另一个圆角矩形
        /// @return 相同返回true，否则返回false
        constexpr bool operator==(const RoundRect<T>& other) const {
            using namespace _GFt_private_;
            if constexpr (std::is_floating_point_v<T>) 
                if (_fsafe_equal(lt, other.lt) && _fsafe_equal(rt, other.rt) &&
                    _fsafe_equal(rb, other.rb) && _fsafe_equal(lb, other.lb)) 
                    return rect_ == other.rect_;
            else 
                if (lt == other.lt && rt == other.rt &&
                    rb == other.rb && lb == other.lb) 
                    return rect_ == other.rect_;
            return false;
        }
        /// @brief 判断两个圆角矩形是否不同
        /// @param other 另一个圆角矩形
        /// @return 不同返回true，否则返回false
        constexpr bool operator!=(const RoundRect<T>& other) const {
            return !(*this == other);
        }
        /// @brief 输出圆角矩形信息到输出流
        /// @param os 输出流
        /// @param r 圆角矩形
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const RoundRect<T>& r) {
            os << "RoundRect(" << r.rect_ << ", " << r.lt << ", " << r.rt << ", " << r.rb << ", " << r.lb << ")";
            return os;
        }
        /// @brief 类型转换函数
        /// @tparam U 目标类型
        /// @param r 圆角矩形
        /// @return 转换后的圆角矩形
        template<typename U>
            requires std::is_arithmetic_v<U>
        friend constexpr RoundRect<U> cast(const RoundRect<T>& r) {
            RoundRect<U> result(cast<Rect<U>>(r.rect_));
            result.lt = static_cast<U>(r.lt);
            result.rt = static_cast<U>(r.rt);
            result.rb = static_cast<U>(r.rb);
            result.lb = static_cast<U>(r.lb);
            return result;
        }
    };

    /// @brief 整型圆角矩形类型
    /// @ingroup 预定义模板特化类型
    using iRoundRect = RoundRect<int>;
    /// @brief 浮点型圆角矩形类型
    /// @ingroup 预定义模板特化类型
    using fRoundRect = RoundRect<float>;
}