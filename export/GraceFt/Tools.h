#pragma once

#include <type_traits>
#include <vector>
#include <string>

namespace GFt {
    /// @defgroup 设备无关单位
    /// @details 此部分函数在头文件 Tools.h 中定义
    /// @ingroup 工具集

    /// @defgroup 字符串操作函数
    /// @details 此部分函数在头文件 Tools.h 中定义
    /// @ingroup 工具集

    /// @brief 字面量定义
    namespace literals {
        /// @brief 设备无关的像素单位 (unsigned long long)
        /// @details 它会将该像素大小以96DPI为基准进行逻辑比例映射，用于屏幕适配
        /// @details 它不会影响实际显示的像素大小
        /// @param n 逻辑像素大小
        /// @return 实际像素大小
        /// @ingroup 设备无关单位
        int operator""_px(unsigned long long n);
        /// @brief 设备无关的像素单位 (long double)
        /// @details 它会将该像素大小以96DPI为基准进行逻辑比例映射，用于屏幕适配
        /// @details 它不会影响实际显示的像素大小
        /// @param n 逻辑像素大小
        /// @return 实际像素大小
        /// @ingroup 设备无关单位
        int operator""_px(long double n);
        /// @brief 设备无关的字体大小单位 (unsigned long long)
        /// @details 它会将该字体大小以96DPI下的16px(1_em = 16_px)为基准进行逻辑比例映射，用于屏幕适配
        /// @param n 逻辑字号大小
        /// @return 实际字号大小
        /// @ingroup 设备无关单位
        int operator""_em(unsigned long long n);
        /// @brief 设备无关的字体大小单位 (long double)
        /// @details 它会将该字体大小以96DPI下的16px(1_em = 16_px)为基准进行逻辑比例映射，用于屏幕适配
        /// @param n 逻辑字号大小
        /// @return 实际字号大小
        /// @ingroup 设备无关单位
        int operator""_em(long double n);

        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int px(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_px(static_cast<long double>(n));
            else
                return operator""_px(static_cast<unsigned long long>(n));
        }
        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int em(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_em(static_cast<long double>(n));
            else
                return operator""_em(static_cast<unsigned long long>(n));
        }

        /// @brief 百分比映射的屏幕宽度单位 (unsigned long long)
        /// @details 它以屏幕的物理像素宽度为 100%(100_sw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @ingroup 设备无关单位
        int operator""_sw(unsigned long long n);
        /// @brief 百分比映射的屏幕宽度单位 (long double)
        /// @details 它以屏幕的物理像素宽度为 100%(100_sw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @ingroup 设备无关单位
        int operator""_sw(long double n);
        /// @brief 百分比映射的屏幕高度单位 (unsigned long long)
        /// @details 它以屏幕的物理像素高度为 100%(100_sw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @ingroup 设备无关单位
        int operator""_sh(unsigned long long n);
        /// @brief 百分比映射的屏幕高度单位 (long double)
        /// @details 它以屏幕的物理像素高度为 100%(100_sw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @ingroup 设备无关单位
        int operator""_sh(long double n);
        /// @brief 百分比映射的窗口宽度单位 (unsigned long long)
        /// @details 它以窗口的物理像素宽度为 100%(100_vw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @note 此函数仅在应用程序窗口被创建后有效(即构造出 GFt::Window 对象后),否则固定返回零值
        /// @ingroup 设备无关单位

        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int sw(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_sw(static_cast<long double>(n));
            else
                return operator""_sw(static_cast<unsigned long long>(n));
        }
        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int sh(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_sh(static_cast<long double>(n));
            else
                return operator""_sh(static_cast<unsigned long long>(n));
        }

        int operator""_vw(unsigned long long n);
        /// @brief 百分比映射的窗口宽度单位 (long double)
        /// @details 它以窗口的物理像素宽度为 100%(100_vw) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @note 此函数仅在应用程序窗口被创建后有效(即构造出 GFt::Window 对象后),否则固定返回零值
        /// @ingroup 设备无关单位
        int operator""_vw(long double n);
        /// @brief 百分比映射的窗口高度单位 (unsigned long long)
        /// @details 它以窗口的物理像素高度为 100%(100_vh) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @note 此函数仅在应用程序窗口被创建后有效(即构造出 GFt::Window 对象后),否则固定返回零值
        /// @ingroup 设备无关单位
        int operator""_vh(unsigned long long n);
        /// @brief 百分比映射的窗口高度单位 (long double)
        /// @details 它以窗口的物理像素高度为 100%(100_vh) 基准进行逻辑比例映射
        /// @param n 百分数宽度
        /// @return 实际宽度大小
        /// @note 此函数仅在应用程序窗口被创建后有效(即构造出 GFt::Window 对象后),否则固定返回零值
        /// @ingroup 设备无关单位
        int operator""_vh(long double n);

        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int vw(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_vw(static_cast<long double>(n));
            else
                return operator""_vw(static_cast<unsigned long long>(n));
        }
        /// @brief 设备无关的非字面量定义
        /// @ingroup 设备无关单位
        template<typename T>
            requires std::is_arithmetic_v<T>
        int vh(T n) {
            if constexpr (std::is_floating_point_v<T>)
                return operator""_vh(static_cast<long double>(n));
            else
                return operator""_vh(static_cast<unsigned long long>(n));
        }
    }
    template<typename T>
    using StdString = std::basic_string<T>;
    /// @brief 字符串分割函数
    /// @details 该函数将一个字符串按照一个分隔符分割为多个子字符串
    ///          如果分隔符为空，则不会执行任何分割操作
    /// @param str 要分割的字符串
    /// @param delimiter 分隔符
    /// @return 子字符串的集合
    /// @code 示例
    /// std::string str = "hello,world";
    /// std::vector<std::string> substrings = GFt::split(str, ",");
    /// // substrings = {"hello", "world"}
    /// @endcode
    /// @ingroup 字符串操作函数
    template<typename CharT>
    std::vector<StdString<CharT>> split(const StdString<CharT>& str, const StdString<CharT>& delimiter) {
        if (delimiter.empty()) {
            return { str };
        }
        std::vector<StdString<CharT>> result;
        size_t pos = 0;
        while (true) {
            size_t found = str.find(delimiter, pos);
            if (found == StdString<CharT>::npos) {
                result.push_back(str.substr(pos));
                break;
            }
            result.push_back(str.substr(pos, found - pos));
            pos = found + delimiter.size();
        }
        return result;
    }
    /// @brief 这是一个重载
    /// @see split()
    /// @ingroup 字符串操作函数
    template<typename CharT, size_t N>
    std::vector<StdString<CharT>> split(const StdString<CharT>& str, const CharT (&delimiter)[N]) {
        return split(str, StdString<CharT>(delimiter));
    }
    /// @brief 这是一个重载
    /// @see split()
    /// @ingroup 字符串操作函数
    template<typename CharT>
    std::vector<StdString<CharT>> split(const StdString<CharT>& str, CharT delimiter) {
        return split(str, StdString<CharT>(1, delimiter));
    }
    /// @brief 这是一个重载
    /// @see split()
    /// @ingroup 字符串操作函数
    template<typename CharT>
    std::vector<StdString<CharT>> split(const StdString<CharT>& str, CharT* delimiter) {
        return split(str, StdString<CharT>(delimiter));
    }
    /// @brief 字符串拼接函数
    /// @details 该函数将一个字符串集合按照一个分隔符拼接为一个字符串
    /// @param strs 要拼接的字符串集合
    /// @param delimiter 分隔符
    /// @return 拼接后的字符串
    /// @code 示例
    /// std::vector<std::string> strs = {"hello", "world"};
    /// std::string result = GFt::join(strs, ",");
    /// // result = "hello,world"
    /// @endcode
    /// @ingroup 字符串操作函数
    template<typename CharT>
    StdString<CharT> join(const std::vector<StdString<CharT>>& strs, const StdString<CharT>& delimiter) {
        StdString<CharT> result;
        for (const auto& str : strs) {
            result += str + delimiter;
        }
        return result.substr(0, result.size() - delimiter.size());
    }
    /// @brief 这是一个重载
    /// @see join()
    /// @ingroup 字符串操作函数
    template<typename CharT, size_t N>
    StdString<CharT> join(const std::vector<StdString<CharT>>& strs, const CharT (&delimiter)[N]) {
        return join(strs, StdString<CharT>(delimiter));
    }
    /// @brief 这是一个重载
    /// @see join()
    /// @ingroup 字符串操作函数
    template<typename CharT>
    StdString<CharT> join(const std::vector<StdString<CharT>>& strs, CharT delimiter) {
        return join(strs, StdString<CharT>(1, delimiter));
    }
    /// @brief 这是一个重载
    /// @see join()
    /// @ingroup 字符串操作函数
    template<typename CharT>
    StdString<CharT> join(const std::vector<StdString<CharT>>& strs, CharT* delimiter) {
        return join(strs, StdString<CharT>(delimiter));
    }
}