#pragma once

#include <iostream>
#include <string>

#include <GraceFt/Tools.h>

namespace GFt {
    /// @defgroup 字体枚举
    /// @brief 这里列出了字体粗细相关的枚举值
    /// @ingroup 枚举

    /// @enum FontWeight
    /// @brief 字体粗细枚举
    /// @ingroup 字体枚举
    enum class FontWeight {
        Default = 0,        ///< 默认粗细 (0)
        Thin = 100,         ///< 细体 (100)
        Extralight = 200,   ///< 极细体 (200)
        Ultralight = 200,   ///< 超细体 (200)
        Light = 300,        ///< 细体 (300)
        Normal = 400,       ///< 正常粗细 (400)
        Regular = 400,      ///< 正常粗细 (400)
        Medium = 500,       ///< 中粗体 (500)
        Semibold = 600,     ///< 半粗体 (600)
        Demibold = 600,     ///< 半粗体 (600)
        Bold = 700,         ///< 粗体 (700)
        Extrabold = 800,    ///< 极粗体 (800)
        Ultrabold = 800,    ///< 超粗体 (800)
        Heavy = 900,        ///< 黑体 (900)
        Black = 900         ///< 黑体 (900)
    };

    /// @defgroup 图形系统
    /// @brief 这里提供图形处理相关功能
    /// @ingroup API接口库

    /// @defgroup 基础类型
    /// @brief 这里包含了图形相关的基础类型定义
    /// @ingroup 图形系统

    /// @class Font
    /// @brief 字体类
    /// @details 字体类用于管理字体相关的属性，包括字体名称、大小、粗细、斜体、下划线、删除线等。
    /// @ingroup 基础类型
    class Font {
        friend class Graphics;
        void* font_;
    public:
        /// @brief 构造函数
        /// @param fontFamily 字体名称
        /// @param size 字体大小，默认16
        Font(const std::wstring& fontFamily, long size = literals::em(1));
        /// @brief 复制构造
        Font(const Font& other);
        /// @brief 移动构造
        Font(Font&& other);
        /// @brief 复制赋值
        Font& operator=(const Font& other);
        /// @brief 移动赋值
        Font& operator=(Font&& other);
        ~Font();
        /// @brief 设置字体大小
        void setSize(long size);
        /// @brief 获取字体大小
        long size() const;
        /// @brief 设置字体字重(粗细)
        void setWeight(FontWeight weight);
        /// @brief 获取字体字重(粗细)
        FontWeight weight() const;
        /// @brief 设置字体是否为斜体
        void setItalic(bool italic);
        /// @brief 获取字体是否为斜体
        bool italic() const;
        /// @brief 设置字体是否具有下划线
        void setUnderline(bool underline);
        /// @brief 获取字体是否具有下划线
        bool underline() const;
        /// @brief 设置字体是否具有删除线
        void setStrikeOut(bool strikeOut);
        /// @brief 获取字体是否具有删除线
        bool strikeOut() const;
        /// @brief 设置字体名称
        void setFontFamily(const std::wstring& fontFamily);
        /// @brief 获取字体名称
        std::wstring fontFamily() const;
        /// @brief 输出流运算符重载
        friend std::ostream& operator<<(std::ostream& os, const Font& font);
    };
}