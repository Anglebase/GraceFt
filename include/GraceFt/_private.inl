#pragma once
// 这个文件用于声明一些内部使用的函数和结构体
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
    bool _fsafe_equal(T a, T b, T eps = static_cast<T>(1e-6)) {
        return std::abs(a - b) < eps;
    }
    /// @brief 画笔属性结构体
    struct PenSetPrivate {
        unsigned int color;
        int width;
        int line_type;
        int startcap_type;
        int endcap_type;
        int join_type;
        short userdef;
        float miterlimit;
    };
    /// @brief 画刷属性结构体
    struct BrushSetPrivate {
        int mode;    // 填充模式
        union {
            struct {    // 默认填充
                int style;
                unsigned int color;
            } def;
            struct {    // 线性渐变
                float x1, y1, x2, y2;
                unsigned int color1, color2;
            } linear;
            struct {    // 径向渐变
                float cx, cy;
                float x, y, w, h;
                unsigned int ccolor, ocolor;
            } radial;
            struct {    // 纹理填充
                float x, y, w, h;
                void* data;
            } texture;
            struct {    // 多边形渐变
                float cx, cy;
                unsigned int ccolor;
                int num_points;
                int num_colors;
                float* points;
                unsigned int* colors;
            } polygon;
        };
    };
}
/// @endcond

// 此空声明用于运行 Doxygen
namespace GFt {}