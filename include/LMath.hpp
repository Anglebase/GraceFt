#pragma once

#include <Matrix.hpp>

namespace GFt {
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 复合数据类型
    /// @{

    /// @brief 计算向量点乘
    /// @tparam N 维度数
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 点乘结果
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
    template<size N, typename T>
    constexpr T operator*(const Vec<N, T>& v1, const Vec<N, T>& v2) {
        return dot(v1, v2);
    }
    /// @brief 计算向量叉乘
    /// @tparam T 类型
    /// @param v1 向量1
    /// @param v2 向量2
    /// @return 叉乘结果
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
    template<typename T>
    constexpr Vec3<T> operator^(const Vec3<T>& v1, const Vec3<T>& v2) {
        return cross(v1, v2);
    }
    /// @brief 对向量执行归一化
    /// @details 此操作常用于三维空间中的坐标变换
    /// @tparam T 类型
    /// @param v 向量
    /// @return 归一化后的向量
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
    template<size N, typename T, typename... TArgs>
    constexpr Vec<N, T> makeVec(TArgs... args) {
        static_assert(sizeof...(args) == N, "Invalid number of arguments");
        static_assert((std::is_same_v<T, TArgs> &&...), "Invalid argument types");
        T data[1][N] = { { args... } };
        return Vec<N, T>(data);
    };
    /// @brief 构造整数二维向量
    constexpr iVec2 makeiVec2(int x, int y) { return makeVec<2, int>(x, y); }
    /// @brief 构造浮点二维向量
    constexpr fVec2 makefVec2(float x, float y) { return makeVec<2, float>(x, y); }
    /// @brief 构造整数三维向量
    constexpr iVec3 makeiVec3(int x, int y, int z) { return makeVec<3, int>(x, y, z); }
    /// @brief 构造浮点三维向量
    constexpr fVec3 makefVec3(float x, float y, float z) { return makeVec<3, float>(x, y, z); }
    /// @brief 构造整数四维向量
    constexpr iVec4 makeiVec4(int x, int y, int z, int w) { return makeVec<4, int>(x, y, z, w); }
    /// @brief 构造浮点四维向量
    constexpr fVec4 makefVec4(float x, float y, float z, float w) { return makeVec<4, float>(x, y, z, w); }


    /// @brief 流操作符重载
    /// @details 输出矩阵到流中
    /// @param os 流对象
    /// @param mat 矩阵对象
    /// @return 流对象 os
    template<size M, size N, typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& mat) {
        std::cout << std::endl;
        for (size i = 0; i < M; i++) {
            std::cout << "[";
            for (size j = 0; j < N; j++)
                std::cout << " " << mat[i][j] << ", "[j == N - 1];
            std::cout << "]" << std::endl;
        }
        return os;
    }
    /// @brief 流操作符重载
    /// @details 输出向量到流中
    /// @param os 流对象
    /// @param v 向量对象
    /// @return 流对象 os
    template<size N, typename T>
    std::ostream& operator<<(std::ostream& os, const Vec<N, T>& v) {
        os << "[";
        for (size_t i = 0; i < N; ++i)
            os << " " << v[0][i] << ", "[i == N - 1];
        os << "]";
        return os;
    }
    
    /// @}
    /// @}
}