#pragma once

#include <GraceFt/Font.h>
#include <GraceFt/Color.h>

namespace GFt {
    /// @class TextSet
    /// @brief 文本环境设置类,
    /// @details 用于设置字体、颜色、透明度等属性
    /// @ingroup 接口类型
    class TextSet {
        friend class Graphics;
        Font font_;
        unsigned int color_;
        bool transparent_ = false;
    public:
        /// @brief 构造函数
        /// @param color 文本颜色
        /// @param font 字体
        TextSet(const Color& color, const Font& font = Font(L"宋体"));
        TextSet(const TextSet& other) = default;
        TextSet(TextSet&& other) = default;
        TextSet& operator=(const TextSet& other) = default;
        TextSet& operator=(TextSet&& other) = default;

        /// @brief 字体设置
        /// @return 保有的字体对象
        Font& font();
        const Font& font() const;

        /// @brief 设置颜色
        /// @param color 颜色
        void setColor(const Color& color);
        /// @brief 设置文本背景模式
        /// @param transparent 是否透明
        void setTransparent(bool transparent);

        /// @brief 获取颜色
        /// @return 颜色
        Color getColor() const;
        /// @brief 获取文本背景模式
        /// @return 是否为透明
        bool isTransparent() const;
    };
}