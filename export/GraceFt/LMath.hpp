#pragma once

#include <GraceFt/Matrix.hpp>

namespace GFt {
    /// @defgroup 线性代数工具
    /// @details 此部分函数在头文件 LMath.hpp 中定义
    /// @ingroup 工具集

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
    template<size N, typename T>
    constexpr Vec<N, T> normalize(const Vec<N, T>& v) {
        return v / v[N - 1];
    }
    /// @brief 计算向量模长
    /// @tparam N 维度数
    /// @tparam T 类型
    /// @param v 向量
    /// @return 向量模长
    /// @ingroup 线性代数工具
    template<size N, typename T>
    constexpr T norm(const Vec<N, T>& v) {
        return sqrt(v * v);
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
    /// @brief 创建平移坐标变换矩阵
    /// @tparam M 维度数
    /// @tparam T 类型
    /// @param v 平移向量
    /// @return 平移变换矩阵
    /// @ingroup 线性代数工具
    template<size M, typename T>
        requires (M == 2) || (M == 3)
    constexpr Matrix<M + 1, M + 1, T> translate(const Vec<M, T>& v) {
        Matrix<M + 1, M + 1, T> result = Matrix<M + 1, M + 1, T>::I();
        for (size_t i = 0; i < M; i++)
            result[M][i] = v[0][i];
        return result;
    }
    /// @brief 创建缩放坐标变换矩阵
    /// @tparam M 维度数
    /// @tparam T 类型
    /// @param pos 缩放中心，即缩放操作的基准点，缩放前后该点固定不动
    /// @param s 缩放因子
    /// @return 缩放变换矩阵
    /// @ingroup 线性代数工具
    template<size M, typename T>
        requires (M == 2) || (M == 3)
    constexpr Matrix<M + 1, M + 1, T> scale(const Vec<M, T>& pos, const Vec<M, T>& s) {
        Matrix<M + 1, M + 1, T> result = Matrix<M + 1, M + 1, T>::I();
        for (size_t i = 0; i < M; i++)
            result(i, i) = s[0][i];
        return translate(-pos) * result * translate(pos);
    }
    /// @brief 创建二维坐标系下的旋转坐标变换矩阵
    /// @tparam T 类型
    /// @param axis 旋转中心，即旋转的基准点，旋转前后该点固定不动
    /// @param rad 旋转角度(弧度制)
    /// @return 旋转变换矩阵
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr Matrix<3, 3, T> rotate(const Vec<2, T>& axis, float rad) {
        Matrix<3, 3, T> result = Matrix<3, 3, T>::I();
        float c = std::cos(rad);
        float s = std::sin(rad);
        Matrix<3, 3, T> rot = Matrix<3, 3, T>::I();
        rot(0, 0) = c;
        rot(0, 1) = -s;
        rot(1, 0) = s;
        rot(1, 1) = c;
        return translate(-axis) * rot * translate(axis);
    }
    /// @brief 创建三维坐标系下的旋转坐标变换矩阵
    /// @tparam T 类型
    /// @param axis 旋转轴
    /// @param rad 旋转角度(弧度制)
    /// @return 旋转变换矩阵
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr Matrix<4, 4, T> rotate(const Vec<3, T>& axis, float rad) {
        Matrix<4, 4, T> result = Matrix<4, 4, T>::I();
        float c = std::cos(rad);
        float s = std::sin(rad);
        Vec<3, T> nor = axis / norm(axis);
        float k[3][3] =
        { {          0, -nor[0][2],  nor[0][1] },
          {  nor[0][2],          0, -nor[0][0] },
          { -nor[0][1],  nor[0][0],          0 } };
        Matrix<3, 3, T> I3x3 = Matrix<3, 3, T>::I();
        Mat3x3 K(k);
        Matrix<3, 3, T> R = I3x3 + s * K + (1 - c) * (K * K);
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                result(i, j) = R(i, j);
            }
        }
        return result;
    }

    /// @brief 将角度制转为弧度制
    /// @tparam T 类型
    /// @param deg 角度制
    /// @return 弧度制
    /// @ingroup 线性代数工具
    template<typename T>
    constexpr double radians(T deg) {
        return deg * (M_PI / 180);
    }
}