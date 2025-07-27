#include "GraceFt/PixelMap.h"

#include <ege.h>
#include <exception>

#define IMG(x) (static_cast<PIMAGE>(x))

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
        if (this == &other)
            return *this;
        auto img = newimage();
        resize(img, getwidth(IMG(other.pixmap_)), getheight(IMG(other.pixmap_)));
        putimage(img, 0, 0, IMG(other.pixmap_));
        pixmap_ = img;
        return *this;
    }
    PixelMap::PixelMap(PixelMap&& other) {
        pixmap_ = other.pixmap_;
        other.pixmap_ = nullptr;
    }
    PixelMap& PixelMap::operator=(PixelMap&& other) {
        if (this == &other)
            return *this;
        pixmap_ = other.pixmap_;
        other.pixmap_ = nullptr;
        return *this;
    }
    PixelMap::~PixelMap() {
        if (pixmap_)
            delimage(IMG(pixmap_));
        pixmap_ = nullptr;
    }
    PixelMap PixelMap::clip(const iRect& rect) const {
        PixelMap result(rect.size());
        putimage(IMG(result.pixmap_), 0, 0, rect.width(), rect.height(), IMG(pixmap_), rect.x(), rect.y());
        return result;
    }
    iSize PixelMap::size() const {
        return iSize(getwidth(IMG(pixmap_)), getheight(IMG(pixmap_)));
    }
    void PixelMap::setAlpha(int alpha) {
        ege_setalpha(alpha, IMG(pixmap_));
    }
    void PixelMap::saveToFile(const std::wstring& filename, bool withAlpha) const {
        auto ret = saveimage(IMG(pixmap_), filename.c_str(), withAlpha);
        if (ret != grOk)
            throw std::runtime_error("Failed to save image");
    }
    PixelMap PixelMap::loadFromFile(const std::wstring& filename) {
        PixelMap result;
        auto ret = getimage(IMG(result.pixmap_), filename.c_str());
        switch (ret) {
        case grOk:
            return result;
        case grAllocError:
            throw std::runtime_error("Memory allocation failed");
        case grFileNotFound:
            throw std::runtime_error("File not found");
        case grIOerror:
            throw std::runtime_error("Read failed");
        default:
            throw std::runtime_error("Unknown error");
        }
    }
    PixelMap PixelMap::loadFromWindow(const iRect& rect) {
        PixelMap result(rect.size());
        auto ret = getimage(IMG(result.pixmap_), rect.x(), rect.y(), rect.width(), rect.height());
        switch (ret) {
        case grOk:
            return result;
        case grAllocError:
            throw std::runtime_error("Memory allocation failed");
        case grIOerror:
            throw std::runtime_error("Read failed");
        default:
            throw std::runtime_error("Unknown error");
        }
    }
}