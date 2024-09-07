#include "Color.h"

#include <ege.h>

namespace GFt {
    constexpr Color::Color(byte red, byte green, byte blue, byte alpha)
        : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

    constexpr byte& Color::red() { return red_; }
    constexpr byte& Color::green() { return green_; }
    constexpr byte& Color::blue() { return blue_; }
    constexpr byte& Color::alpha() { return alpha_; }

    constexpr const byte& Color::red() const { return red_; }
    constexpr const byte& Color::green() const { return green_; }
    constexpr const byte& Color::blue() const { return blue_; }
    constexpr const byte& Color::alpha() const { return alpha_; }

    std::tuple<float, float, float> Color::toHSL() const {
        using namespace ege;
        float h, s, l;
        RGBtoHSL(EGERGBA(red_, green_, blue_, alpha_), &h, &s, &l);
        return { h, s, l };
    }
    std::tuple<float, float, float> Color::toHSV() const {
        using namespace ege;
        float h, s, v;
        RGBtoHSV(EGERGBA(red_, green_, blue_, alpha_), &h, &s, &v);
        return { h, s, v };
    }
    Color Color::toGray() const {
        using namespace ege;
        auto gray = RGBtoGRAY(EGERGBA(red_, green_, blue_, alpha_));
        return Color(EGEGET_R(gray), EGEGET_G(gray), EGEGET_B(gray), EGEGET_A(gray));
    }
    Color Color::blend(const Color& other) const {
        using namespace ege;
        auto result = alphablend(
            EGERGBA(red_, green_, blue_, alpha_),
            EGERGBA(other.red_, other.green_, other.blue_, other.alpha_)
        );
        return Color(EGEGET_R(result), EGEGET_G(result), EGEGET_B(result), EGEGET_A(result));
    }

    Color Color::fromHSL(float h, float s, float l) {
        using namespace ege;
        auto rgb = HSLtoRGB(h, s, l);
        return Color(EGEGET_R(rgb), EGEGET_G(rgb), EGEGET_B(rgb), EGEGET_A(rgb));
    }
    Color Color::fromHSV(float h, float s, float v) {
        using namespace ege;
        auto rgb = HSVtoRGB(h, s, v);
        return Color(EGEGET_R(rgb), EGEGET_G(rgb), EGEGET_B(rgb), EGEGET_A(rgb));
    }
    std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "Color(R: "
            << static_cast<int>(color.red()) << ", G: "
            << static_cast<int>(color.green()) << ", B: "
            << static_cast<int>(color.blue()) << ", A: "
            << static_cast<int>(color.alpha()) << ")";
        return os;
    }
    constexpr Color operator""_rgb(unsigned long long int hex) {
        return Color(
            static_cast<byte>(hex >> 16),
            static_cast<byte>(hex >> 8 & 0xFF),
            static_cast<byte>(hex & 0xFF)
        );
    }
    constexpr Color operator""_rgba(unsigned long long int hex) {
        return Color(
            static_cast<byte>(hex >> 24),
            static_cast<byte>(hex >> 16 & 0xFF),
            static_cast<byte>(hex >> 8 & 0xFF),
            static_cast<byte>(hex & 0xFF)
        );
    }
}

