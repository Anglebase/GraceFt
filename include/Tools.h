#pragma once

namespace GFt {
    /// @defgroup 工具函数
    /// @ingroup API接口库

    /// @brief 设备无关的像素单位 (unsigned long long)
    /// @details 它会将该像素大小以96DPI为基准进行逻辑比例映射，用于屏幕适配
    /// @details 它不会影响实际显示的像素大小
    /// @param n 逻辑像素大小
    /// @return 实际像素大小
    /// @ingroup 工具函数
    unsigned long operator""_px(unsigned long long n);
    /// @brief 设备无关的像素单位 (long double)
    /// @details 它会将该像素大小以96DPI为基准进行逻辑比例映射，用于屏幕适配
    /// @details 它不会影响实际显示的像素大小
    /// @param n 逻辑像素大小
    /// @return 实际像素大小
    /// @ingroup 工具函数
    unsigned long operator""_px(long double n);
    /// @brief 设备无关的字体大小单位 (unsigned long long)
    /// @details 它会将该字体大小以96DPI下的16px(1_em = 16_px)为基准进行逻辑比例映射，用于屏幕适配
    /// @param n 逻辑字号大小
    /// @return 实际字号大小
    /// @ingroup 工具函数
    unsigned long operator""_em(unsigned long long n);
    /// @brief 设备无关的字体大小单位 (long double)
    /// @details 它会将该字体大小以96DPI下的16px(1_em = 16_px)为基准进行逻辑比例映射，用于屏幕适配
    /// @param n 逻辑字号大小
    /// @return 实际字号大小
    /// @ingroup 工具函数
    unsigned long operator""_em(long double n);

    /// @brief 百分比映射的屏幕宽度单位 (unsigned long long)
    /// @details 它以屏幕的物理像素宽度为 100%(100_sw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @ingroup 工具函数
    unsigned long operator""_sw(unsigned long long n);
    /// @brief 百分比映射的屏幕宽度单位 (long double)
    /// @details 它以屏幕的物理像素宽度为 100%(100_sw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @ingroup 工具函数
    unsigned long operator""_sw(long double n);
    /// @brief 百分比映射的屏幕高度单位 (unsigned long long)
    /// @details 它以屏幕的物理像素高度为 100%(100_sw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @ingroup 工具函数
    unsigned long operator""_sh(unsigned long long n);
    /// @brief 百分比映射的屏幕高度单位 (long double)
    /// @details 它以屏幕的物理像素高度为 100%(100_sw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @ingroup 工具函数
    unsigned long operator""_sh(long double n);
    /// @brief 百分比映射的窗口宽度单位 (unsigned long long)
    /// @details 它以窗口的物理像素宽度为 100%(100_vw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @note 此函数仅在应用程序窗口被创建后有效,否则固定返回零值
    /// @ingroup 工具函数
    unsigned long operator""_vw(unsigned long long n);
    /// @brief 百分比映射的窗口宽度单位 (long double)
    /// @details 它以窗口的物理像素宽度为 100%(100_vw) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @note 此函数仅在应用程序窗口被创建后有效,否则固定返回零值
    /// @ingroup 工具函数
    unsigned long operator""_vw(long double n);
    /// @brief 百分比映射的窗口高度单位 (unsigned long long)
    /// @details 它以窗口的物理像素高度为 100%(100_vh) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @note 此函数仅在应用程序窗口被创建后有效,否则固定返回零值
    /// @ingroup 工具函数
    unsigned long operator""_vh(unsigned long long n);
    /// @brief 百分比映射的窗口高度单位 (long double)
    /// @details 它以窗口的物理像素高度为 100%(100_vh) 基准进行逻辑比例映射
    /// @param n 百分数宽度
    /// @return 实际宽度大小
    /// @note 此函数仅在应用程序窗口被创建后有效,否则固定返回零值
    /// @ingroup 工具函数
    unsigned long operator""_vh(long double n);
}