#pragma once

#include <Rect.hpp>

namespace GFt {


    /// @defgroup 工具集

    /// @defgroup 几何求解工具
    /// @ingroup 工具集

    /// @brief 计算两个矩形的交集
    /// @tparam T 矩形的类型，必须是数字类型
    /// @param r1 矩形1
    /// @param r2 矩形2
    /// @return 矩形1和矩形2的交集
    /// @details 计算矩形1和矩形2的交集，如果两个矩形没有交集，则返回一个空矩形
    /// @ingroup 几何求解工具
    template<typename T>
        requires std::is_arithmetic_v<T>
    Rect<T> operator&(const Rect<T>& r1, const Rect<T>& r2) {
        Rect<T> ret;
        ret.width() = std::min(r1.x() + r1.width(), r2.x() + r2.width()) - ret.x();
        if (ret.width() <= 0)
            return Rect<T>();
        ret.height() = std::min(r1.y() + r1.height(), r2.y() + r2.height()) - ret.y();
        if (ret.height() <= 0)
            return Rect<T>();
        ret.x() = std::max(r1.x(), r2.x());
        ret.y() = std::max(r1.y(), r2.y());
        return ret;
    }
    /// @brief 判断点是否在矩形内(包含边界)
    /// @tparam T 矩形的类型，必须是数字类型
    /// @param r 矩形
    /// @param p 点
    /// @return 点是否在矩形内
    /// @ingroup 几何求解工具
    template<typename T>
        requires std::is_arithmetic_v<T>
    bool contains(const Rect<T>& r, const Point<T>& p) {
        return p.x() >= r.x() && p.x() < r.x() + r.width() && p.y() >= r.y() && p.y() < r.y() + r.height();
    }
}