#include "Texture.h"

#include <ege.h>

#define IMG(x) (reinterpret_cast<ege::PIMAGE>(x))

namespace GFt {
    using namespace ege;
    Texture::Texture(const std::wstring& path) {
        auto img = newimage();
        getimage(img, path.c_str());
        texture_ = img;
    }
    Texture::Texture(const Texture& other) {
        auto img = newimage();
        resize(img, getwidth(IMG(other.texture_)), getheight(IMG(other.texture_)));
        putimage(img, 0, 0, IMG(other.texture_));
        texture_ = img;
    }
    Texture& Texture::operator=(const Texture& other) {
        if (this != &other) {
            auto img = newimage();
            resize(img, getwidth(IMG(other.texture_)), getheight(IMG(other.texture_)));
            putimage(img, 0, 0, IMG(other.texture_));
            texture_ = img;
        }
        return *this;
    }
    Texture::Texture(Texture&& other) {
        texture_ = other.texture_;
        other.texture_ = nullptr;
    }
    Texture& Texture::operator=(Texture&& other) {
        if (this != &other) {
            texture_ = other.texture_;
            other.texture_ = nullptr;
        }
        return *this;
    }
    Texture::~Texture() {
        if (texture_)
            delimage(IMG(texture_));
        texture_ = nullptr;
    }

}