#pragma once

#include <string>

#include <GraceFt/Size.hpp>
#include <GraceFt/Rect.hpp>

namespace GFt{
    /// @class PixelMap
    /// @brief 位图类
    /// @ingroup 接口类型
    class PixelMap {
        friend class Graphics;
        void* pixmap_;
    public:
        /// @brief 构造函数
        /// @param size 位图大小
        PixelMap(const iSize& size = iSize());
        PixelMap(const PixelMap& other);
        PixelMap& operator=(const PixelMap& other);
        PixelMap(PixelMap&& other);
        PixelMap& operator=(PixelMap&& other);
        ~PixelMap();

        /// @brief 从当前位图中裁剪出一个新的位图
        /// @param rect 裁剪区域
        /// @return 裁剪出的位图
        PixelMap clip(const iRect& rect) const;
    };
}