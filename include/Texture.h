#pragma once

#include <string>

namespace GFt {
    /// @class Texture
    /// @brief 纹理类
    /// @ingroup 接口类型
    class Texture {
        friend class BrushSet;
        void* texture_;
    public:
        /// @brief 构造函数
        /// @param path 纹理文件路径
        Texture(const std::wstring& path);
        Texture(const Texture& other);
        Texture& operator=(const Texture& other);
        Texture(Texture&& other);
        Texture& operator=(Texture&& other);
        ~Texture();
    };
}
