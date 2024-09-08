#include "PixelMap.h"

#include <ege.h>

#define IMG(x) (reinterpret_cast<PIMAGE>(x))

namespace GFt {
    using namespace ege;
    PixelMap::PixelMap(const iSize& size) {
        if (!size)
            pixmap_ = newimage();
        else
            pixmap_ = newimage(size.width(), size.height());
    }
    PixelMap::PixelMap(const PixelMap& other) {
        auto img = newimage();
        resize(img, getwidth(IMG(other.pixmap_)), getheight(IMG(other.pixmap_)));
        putimage(img, 0, 0, IMG(other.pixmap_));
        pixmap_ = img;
    }
    PixelMap& PixelMap::operator=(const PixelMap& other) {
        if (this != &other) {
            auto img = newimage();
            resize(img, getwidth(IMG(other.pixmap_)), getheight(IMG(other.pixmap_)));
            putimage(img, 0, 0, IMG(other.pixmap_));
            pixmap_ = img;
        }
        return *this;
    }
    PixelMap::PixelMap(PixelMap&& other) {
        pixmap_ = other.pixmap_;
        other.pixmap_ = nullptr;
    }
    PixelMap& PixelMap::operator=(PixelMap&& other) {
        if (this != &other) {
            pixmap_ = other.pixmap_;
            other.pixmap_ = nullptr;
        }
        return *this;
    }
    PixelMap::~PixelMap() {
        if (pixmap_)
            delimage(IMG(pixmap_));
    }
    PixelMap PixelMap::clip(const iRect& rect) const {
        PixelMap result(rect.size());
        putimage(IMG(result.pixmap_), 0, 0, rect.width(), rect.height(), IMG(pixmap_), rect.x(), rect.y());
        return result;
    }
}