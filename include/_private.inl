#pragma once

#include <cmath>

/// @cond IGNORE
namespace _GFt_private_ {
    /// @brief 安全浮点数比较函数模板
    /// @tparam T 数值类型
    /// @param a 数值 a
    /// @param b 数值 b
    /// @param eps 误差范围
    /// @return 若 |a - b| < eps，则返回 true；否则返回 false
    template<typename T>
        requires std::is_floating_point_v<T>
    constexpr bool fsafe_equal(T a, T b, T eps = static_cast<T>(1e-6)) {
        return std::abs(a - b) < eps;
    }
}
/// @endcond