#pragma once

#include <string>

namespace GFt {
    class Texture {
        friend class BrushSet;
        void* texture_;
    public:
        Texture(const std::wstring& path);
        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        ~Texture();
    };
}
