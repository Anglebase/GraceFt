#include "GraceFt/Font.h"

#include <ege/ege.h>

#define FONT(x) (static_cast<LOGFONTW*>(x))

namespace GFt {
    Font::Font(const std::wstring& fontFamily, long size) {
        auto* font = new LOGFONTW();
        FONT(font)->lfHeight = -size;
        FONT(font)->lfWidth = 0;
        FONT(font)->lfEscapement = 0;
        FONT(font)->lfOrientation = 0;
        FONT(font)->lfWeight = static_cast<long>(FontWeight::Default);
        FONT(font)->lfItalic = false;
        FONT(font)->lfUnderline = false;
        FONT(font)->lfStrikeOut = false;
        FONT(font)->lfCharSet = DEFAULT_CHARSET;
        FONT(font)->lfOutPrecision = OUT_TT_PRECIS;
        FONT(font)->lfClipPrecision = CLIP_DEFAULT_PRECIS;
        FONT(font)->lfQuality = ANTIALIASED_QUALITY;
        FONT(font)->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
        wcscpy_s(FONT(font)->lfFaceName, fontFamily.c_str());
        font_ = static_cast<void*>(font);
    }
    Font::Font(const Font& other) {
        auto* font = new LOGFONTW();
        font_ = static_cast<void*>(font);
        *FONT(font) = *FONT(other.font_);
    }
    /// @note 对象被移动后原对象将失效, 它应该被弃置, 如果通过已被移动的对象访问其成员函数, 将引发空指针解引用(段错误)
    Font::Font(Font&& other) {
        font_ = other.font_;
        other.font_ = nullptr;
    }
    Font& Font::operator=(const Font& other) {
        if (this == &other)
            return *this;
        delete FONT(font_);
        auto* font = new LOGFONTW();
        font_ = static_cast<void*>(font);
        *FONT(font) = *FONT(other.font_);
        return *this;
    }
    /// @note 对象被移动后原对象将失效, 它应该被弃置, 如果通过已被移动的对象访问其成员函数, 将引发空指针解引用(段错误)
    Font& Font::operator=(Font&& other) {
        if (this == &other)
            return *this;
        delete FONT(font_);
        font_ = other.font_;
        other.font_ = nullptr;
        return *this;
    }
    Font::~Font() {
        delete FONT(font_);
        font_ = nullptr;
    }
    void Font::setSize(long size) { FONT(font_)->lfHeight = size; }
    long Font::size() const { return -FONT(font_)->lfHeight; }
    void Font::setWeight(FontWeight weight) { FONT(font_)->lfWeight = static_cast<long>(weight); }
    FontWeight Font::weight() const { return static_cast<FontWeight>(FONT(font_)->lfWeight); }
    void Font::setItalic(bool italic) { FONT(font_)->lfItalic = italic; }
    bool Font::italic() const { return FONT(font_)->lfItalic; }
    void Font::setUnderline(bool underline) { FONT(font_)->lfUnderline = underline; }
    bool Font::underline() const { return FONT(font_)->lfUnderline; }
    void Font::setStrikeOut(bool strikeOut) { FONT(font_)->lfStrikeOut = strikeOut; }
    bool Font::strikeOut() const { return FONT(font_)->lfStrikeOut; }
    void Font::setFontFamily(const std::wstring& fontFamily) { wcscpy_s(FONT(font_)->lfFaceName, fontFamily.c_str()); }
    std::wstring Font::fontFamily() const { return FONT(font_)->lfFaceName; }
    std::ostream& operator<<(std::ostream& os, const Font& font) {
        os << "Font{ " << &font << ": " << font.font_ << " }";
        return os;
    }
}
