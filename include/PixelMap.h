#pragma once

#include <string>

#include <Size.hpp>
#include <Rect.hpp>

namespace GFt{
    class PixelMap {
        void* pixmap_;
    public:
        PixelMap(const iSize& size = iSize());
        PixelMap(const PixelMap& other);
        PixelMap& operator=(const PixelMap& other);
        PixelMap(PixelMap&& other);
        PixelMap& operator=(PixelMap&& other);
        ~PixelMap();

        PixelMap clip(const iRect& rect) const;
    };
}