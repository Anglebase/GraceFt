#pragma once

#include <string>

#include <GraceFt/Size.hpp>
#include <GraceFt/Rect.hpp>

namespace GFt {
    /// @class PixelMap
    /// @brief 位图类
    /// @ingroup 接口类型
    class PixelMap {
        friend class Graphics;
        friend class Texture;
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
        /// @brief 获取位图大小
        /// @return 位图大小
        iSize size() const;
        /// @brief 为位图的每个像素统一设置Alpha通道
        /// @param alpha 新的Alpha值
        void setAlpha(int alpha);
        /// @brief 将位图保存到文件
        /// @param filename 文件名
        /// @details 支持的格式：PNG、BMP，其它的将保存为PNG
        /// @param withAlpha 是否保存Alpha通道
        void saveToFile(const std::wstring& filename, bool withAlpha = false) const;
    public:
        /// @brief 加载位图文件
        /// @param filename 文件位置
        /// @details 支持的格式：PNG、BMP、JPG、GIF、EMF、WMF、ICO
        /// @return 位图对象
        static PixelMap loadFromFile(const std::wstring& filename);
        /// @brief 从窗口中加载位图
        /// @param rect 窗口位置
        /// @return 位图对象
        static PixelMap loadFromWindow(const iRect& rect);
    };
}