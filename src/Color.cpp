#include "GraceFt/Color.h"
#include <ege/ege.h>

namespace GFt {
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
}

