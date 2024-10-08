#pragma once

#include <iostream>
#include <tuple>

namespace GFt {
    /// @typedef byte
    using byte = unsigned char;
    /// @class Color
    /// @brief 颜色类
    /// @details 颜色类，包含红绿蓝和透明度四个通道，支持HSL和HSV两种颜色空间，支持颜色的混合、转换等操作
    /// @ingroup 基础类型
    class Color {
        byte red_, green_, blue_, alpha_;
    public:
        /// @brief 构造函数
        /// @details 若未指定任何参数，则默认构造为黑色
        /// @param red 红色通道
        /// @param green 绿色通道
        /// @param blue 蓝色通道
        /// @param alpha 透明度通道，默认值为255
        constexpr Color(byte red = 0, byte green = 0, byte blue = 0, byte alpha = 255)
            : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

        /// @return 红色通道
        constexpr byte& red() { return red_; }
        /// @return 绿色通道
        constexpr byte& green() { return green_; }
        /// @return 蓝色通道
        constexpr byte& blue() { return blue_; }
        /// @return 透明度通道
        constexpr byte& alpha() { return alpha_; }

        /// @return 红色通道 (const)
        constexpr const byte& red() const { return red_; }
        /// @return 绿色通道 (const)
        constexpr const byte& green() const { return green_; }
        /// @return 蓝色通道 (const)
        constexpr const byte& blue() const { return blue_; }
        /// @return 透明度通道 (const)
        constexpr const byte& alpha() const { return alpha_; }

        /// @brief 转换为HSL颜色空间
        /// @return 以tuple形式返回HSL颜色空间的三个值，分别为Hue(0~360), Saturation(0~1), Lightness(0~1)
        std::tuple<float, float, float> toHSL() const;
        /// @brief 转换为HSV颜色空间
        /// @return 以tuple形式返回HSV颜色空间的三个值，分别为Hue(0~360), Saturation(0~1), Value(0~1)
        std::tuple<float, float, float> toHSV() const;
        /// @brief 转换为灰度颜色
        /// @return 灰度颜色
        Color toGray() const;
        /// @brief 混合颜色
        /// @param other 另一个颜色
        /// @return 混合后的颜色
        Color blend(const Color& other) const;

        /// @brief 静态函数，从HSL颜色空间创建颜色
        /// @param h Hue(0~360)
        /// @param s Saturation(0~1)
        /// @param l Lightness(0~1)
        /// @return 颜色
        static Color fromHSL(float h, float s, float l);
        /// @brief 静态函数，从HSV颜色空间创建颜色
        /// @param h Hue(0~360)
        /// @param s Saturation(0~1)
        /// @param v Value(0~1)
        /// @return 颜色
        static Color fromHSV(float h, float s, float v);

        /// @brief 友元函数，输出颜色
        /// @param os 输出流
        /// @param color 颜色
        /// @return 输出流 os
        friend std::ostream& operator<<(std::ostream& os, const Color& color);
    };

    namespace literals {
        /// @brief _rgb 字面量运算符重载
        /// @details 允许使用类似"0xRRGGBB"的形式创建颜色
        /// @param hex 16进制颜色值
        /// @return 颜色对象
        /// @code 
        /// Color c = 0xFF0000_rgb; // 红色
        /// @endcode
        constexpr Color operator""_rgb(unsigned long long int hex) {
            return Color(
                static_cast<byte>(hex >> 16 & 0xFF),
                static_cast<byte>(hex >> 8 & 0xFF),
                static_cast<byte>(hex & 0xFF)
            );
        }
        /// @brief _rgba 字面量运算符重载
        /// @details 允许使用类似"0xRRGGBBAA"的形式创建颜色
        /// @param hex 16进制颜色值
        /// @return 颜色对象
        /// @code
        /// Color c = 0xFF00007F_rgba; // 半透明红色
        /// @endcode
        constexpr Color operator""_rgba(unsigned long long int hex) {
            return Color(
                static_cast<byte>(hex >> 24 & 0xFF),
                static_cast<byte>(hex >> 16 & 0xFF),
                static_cast<byte>(hex >> 8 & 0xFF),
                static_cast<byte>(hex & 0xFF)
            );
        }
    }
}