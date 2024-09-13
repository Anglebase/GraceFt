#include "TextSet.h"

#include <ege.h>

namespace GFt {
    using namespace ege;
    TextSet::TextSet(const Color& color, const Font& font) : font_(font) {
        color_ = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
    }
    Font& TextSet::font() { return font_; }
    const Font& TextSet::font() const { return font_; }
void TextSet::setColor(const Color& color) {
        color_ = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
    }
    void TextSet::setTransparent(bool transparent) { transparent_ = transparent; }
    Color TextSet::getColor() const {
        return Color(
            EGEGET_R(color_),
            EGEGET_G(color_),
            EGEGET_B(color_),
            EGEGET_A(color_)
        );
    }
    bool TextSet::isTransparent() const { return transparent_; }
}