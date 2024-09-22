#pragma once

#include <string>
#include <GraceFt/PixelMap.h>

namespace GFt {
    /// @class Texture
    /// @brief 纹理类
    /// @ingroup 接口类型
    class Texture {
        friend class BrushSet;
        void* texture_;
    public:
        /// @brief 从文件构造纹理
        /// @param path 纹理文件路径
        Texture(const std::wstring& path);
        /// @brief 从位图构造纹理
        /// @param bitmap 位图
        Texture(const PixelMap& bitmap);
        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        ~Texture();
    };
}
