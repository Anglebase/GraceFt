#pragma once

#include <GraceFt/Matrix.hpp>

namespace GFt {
    /// @defgroup 线性代数工具
    /// @ingroup 基础设施库

    /// @brief 计算向量点乘
    /// @tparam N 维度数
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 点乘结果
    /// @ingroup 线性代数工具
    template<size N, typename T>
    constexpr T dot(const Vec<N, T>& v1, const Vec<N, T>& v2) {
        Matrix<1, 1, T> m1 = v1 * v2.transpose();
        return m1(0, 0);
    }
    /// @brief 计算向量点乘的运算符重载
    /// @tparam N 维度数
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 点乘结果
    /// @ingroup 线性代数工具
    template<size N, typename T>
    constexpr T operator*(const Vec<N, T>& v1, const Vec<N, T>& v2) {
        return dot(v1, v2);
    }
    /// @brief 计算向量叉乘
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 叉乘结果
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr Vec3<T> cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        Vec3<T> result;
        result[0][0] = v1[0][1] * v2[0][2] - v1[0][2] * v2[0][1];
        result[0][1] = v1[0][2] * v2[0][0] - v1[0][0] * v2[0][2];
        result[0][2] = v1[0][0] * v2[0][1] - v1[0][1] * v2[0][0];
        return result;
    }
    /// @brief 计算向量叉乘的运算符重载
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 叉乘结果
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr Vec3<T> operator^(const Vec3<T>& v1, const Vec3<T>& v2) {
        return cross(v1, v2);
    }
    /// @brief 对向量执行归一化
    /// @details 此操作常用于三维空间中的坐标变换
    /// @tparam T 类型
    /// @param v 向量
    /// @return 归一化后的向量
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr Vec4<T> normalize(const Vec4<T>& v) {
        return v / v[3];
    }
    /// @brief 构造向量
    /// @tparam N 维度数
    /// @tparam T 类型
    /// @tparam TArgs 参数类型
    /// @param args 参数列表
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    template<size N, typename T, typename... TArgs>
    constexpr Vec<N, T> makeVec(TArgs... args) {
        static_assert(sizeof...(args) == N, "Invalid number of arguments");
        static_assert((std::is_same_v<T, TArgs> &&...), "Invalid argument types");
        T data[1][N] = { { args... } };
        return Vec<N, T>(data);
    };
    /// @brief 构造整数二维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr iVec2 makeiVec2(int x, int y) { return makeVec<2, int>(x, y); }
    /// @brief 构造浮点二维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr fVec2 makefVec2(float x, float y) { return makeVec<2, float>(x, y); }
    /// @brief 构造整数三维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @param z 第三个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr iVec3 makeiVec3(int x, int y, int z) { return makeVec<3, int>(x, y, z); }
    /// @brief 构造浮点三维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @param z 第三个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr fVec3 makefVec3(float x, float y, float z) { return makeVec<3, float>(x, y, z); }
    /// @brief 构造整数四维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @param z 第三个元素
    /// @param w 第四个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr iVec4 makeiVec4(int x, int y, int z, int w) { return makeVec<4, int>(x, y, z, w); }
    /// @brief 构造浮点四维向量
    /// @param x 第一个元素
    /// @param y 第二个元素
    /// @param z 第三个元素
    /// @param w 第四个元素
    /// @return 构造的向量
    /// @ingroup 线性代数工具
    constexpr fVec4 makefVec4(float x, float y, float z, float w) { return makeVec<4, float>(x, y, z, w); }

    /// @brief 计算矩阵内积
    /// @tparam M 行数
    /// @tparam N 列数
    /// @tparam T 类型
    /// @param m1 矩阵1
    /// @param m2 矩阵2
    /// @return 内积结果
    /// @ingroup 线性代数工具
    template<size M, size N, typename T>
    constexpr T innerProduct(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
        T result = 0;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                result += m1(i, j) * m2(i, j);
            }
        }
        return result;
    }
    /// @brief 计算矩阵内积的运算符重载
    /// @tparam M 行数
    /// @tparam N 列数
    /// @tparam T 类型
    /// @param m1 矩阵1
    /// @param m2 矩阵2
    /// @return 内积结果
    /// @ingroup 线性代数工具
    template<size M, size N, typename T>
    constexpr T operator|(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2) {
        return innerProduct(m1, m2);
    }
}