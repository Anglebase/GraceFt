#include "Texture.h"

#include <ege.h>

#define IMG(x) (static_cast<ege::PIMAGE>(x))

namespace GFt {
    using namespace ege;
    Texture::Texture(const std::wstring& path) {
        auto img = newimage();
        getimage(img, path.c_str());
        texture_ = img;
        ege_gentexture(true, IMG(texture_));
    }
    Texture::Texture(const PixelMap& bitmap) {
        auto img = newimage();
        auto s = bitmap.size();
        resize(img, s.width(), s.height());
        putimage(img, 0, 0, IMG(bitmap.pixmap_));
        texture_ = img;
        ege_gentexture(true, IMG(texture_));
    }
    Texture::Texture(const Texture& other) {
        auto img = newimage();
        resize(img, getwidth(IMG(other.texture_)), getheight(IMG(other.texture_)));
        putimage(img, 0, 0, IMG(other.texture_));
        texture_ = img;
        ege_gentexture(true, IMG(texture_));
    }
    Texture& Texture::operator=(const Texture& other) {
        if (this == &other)
            return *this;
        auto img = newimage();
        resize(img, getwidth(IMG(other.texture_)), getheight(IMG(other.texture_)));
        putimage(img, 0, 0, IMG(other.texture_));
        texture_ = img;
        ege_gentexture(true, IMG(texture_));
        return *this;
    }
    Texture::Texture(Texture&& other) {
        texture_ = other.texture_;
        other.texture_ = nullptr;
    }
    Texture& Texture::operator=(Texture&& other) {
        if (this == &other)
            return *this;
        texture_ = other.texture_;
        other.texture_ = nullptr;
        return *this;
    }
    Texture::~Texture() {
        if (texture_) {
            ege_gentexture(false, IMG(texture_));
            delimage(IMG(texture_));
        }
        texture_ = nullptr;
    }

}