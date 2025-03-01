#pragma once

#include <GraceFt/Rect.hpp>
#include <GraceFt/Point.hpp>
#include <GraceFt/Line.hpp>

namespace GFt {


    /// @defgroup 工具集

    /// @defgroup 几何求解工具
    /// @details 此部分函数在头文件 Geometry.hpp 中定义
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
        using namespace std;
        Rect<T> ret;
        ret.width() = min(r1.x() + r1.width(), r2.x() + r2.width()) - ret.x();
        if (ret.width() <= 0)
            return Rect<T>();
        ret.height() = min(r1.y() + r1.height(), r2.y() + r2.height()) - ret.y();
        if (ret.height() <= 0)
            return Rect<T>();
        ret.x() = max(r1.x(), r2.x());
        ret.y() = max(r1.y(), r2.y());
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

    /// @brief 计算点a关于点b的对称点
    /// @tparam T 点的类型，必须是数字类型
    /// @param a 点a
    /// @param b 点b
    /// @return 点a关于点b的对称点
    /// @ingroup 几何求解工具
    template<typename T>
        requires std::is_arithmetic_v<T>
    Point<T> centerSymmetric(const Point<T>& a, const Point<T>& b) {
        return Point<T>(2 * b.x() - a.x(), 2 * b.y() - a.y());
    }
    /// @brief 计算直线l关于点p的对称线
    /// @tparam T 点的类型，必须是数字类型
    /// @param l 直线
    /// @param p 点p
    /// @return 直线l关于点p的对称线
    /// @ingroup 几何求解工具
    template<typename T>
        requires std::is_arithmetic_v<T>
    Line<T> centerSymmetric(const Line<T>& l, const Point<T>& p) {
        Point<T> a = l.P1();
        Point<T> b = l.P2();
        Point<T> c = centerSymmetric(a, p);
        Point<T> d = centerSymmetric(b, p);
        return Line<T>(c, d);
    }
}