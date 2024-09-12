#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

#include <_private.inl>

/// @cond IGNORE
#define _LOOP_EACH(code)             \
do{                                  \
    for (size i = 0; i < M; i++)     \
        for (size j = 0; j < N; j++) \
            code;                    \
} while(0)
/// @endcond

namespace GFt {
    using size = std::size_t;
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 复合数据类型
    /// @{
        /// @class Matrix
        /// @brief 矩阵类模板
        /// @tparam M 行数
        /// @tparam N 列数
        /// @tparam T 数据类型
    /// @}
    /// @}
    template<size M, size N, typename T>
        requires (M > 0 && N > 0) && std::is_arithmetic_v<T>
    class Matrix {
        T data[M][N];

    public:
        constexpr static Matrix<M, N, T> I() {
            if constexpr (M != N)
                return Matrix<M, N, T>();
            Matrix<M, N, T> res;
            _LOOP_EACH(res.data[i][j] = static_cast<T>((i == j) ? 1 : 0));
            return res;
        }
    public:
        /// @brief 构造函数
        /// @details 此构造函数将以指定值初始化矩阵，默认初始化为零矩阵
        /// @param val 初始值
        constexpr Matrix(T val = 0) { _LOOP_EACH(data[i][j] = val); }
        /// @brief 构造函数
        /// @details 此构造函数将以给定数组初始化矩阵
        /// @param arr 数组
        constexpr Matrix(const T(&arr)[M][N]) { _LOOP_EACH(data[i][j] = arr[i][j]); }
        constexpr Matrix(const Matrix& other) { _LOOP_EACH(data[i][j] = other.data[i][j]); }
        constexpr Matrix(Matrix&& other) { _LOOP_EACH(data[i][j] = std::move(other.data[i][j])); }
        constexpr Matrix& operator=(const Matrix& other) {
            _LOOP_EACH(data[i][j] = other.data[i][j]);
            return *this;
        }
        constexpr Matrix& operator=(Matrix&& other) {
            _LOOP_EACH(data[i][j] = std::move(other.data[i][j]));
            return *this;
        }
        /// @brief 以 Matrix[M][N] 的形式访问矩阵数据
        /// @return T[M] 的引用
        constexpr T* operator[](size i) { return data[i]; }
        /// @brief 以 Matrix(M,N) 的形式访问矩阵数据
        /// @return T 的引用
        constexpr T& operator()(size i, size j) { return data[i][j]; }
        /// @brief 以 Matrix[M][N] 的形式访问矩阵数据的 const 版本
        /// @return const T[M] 的引用
        constexpr const T* operator[](size i) const { return data[i]; }
        /// @brief 以 Matrix(M,N) 的形式访问矩阵数据的 const 版本
        /// @return T 的 const 引用
        constexpr const T& operator()(size i, size j) const { return data[i][j]; }

        /// @brief 将矩阵转换到 bool 值
        /// @details 若矩阵为零矩阵，则返回 false；否则返回 true
        /// @return 转换结果
        constexpr explicit operator bool() const {
            bool res = false;
            _LOOP_EACH(res |= (data[i][j] != static_cast<T>(0)));
            return res;
        }
        /// @brief 逻辑非运算符重载
        /// @details 相当于 !static_cast<bool>(*this)
        /// @return 逻辑非运算结果
        constexpr bool operator!() const { return !static_cast<bool>(*this); }

        /// @brief 矩阵加法运算符重载
        /// @details 矩阵加法运算，返回矩阵相加结果
        /// @param other 另一个矩阵
        /// @return 矩阵加法结果
        constexpr Matrix operator+(const Matrix& other) const {
            Matrix res;
            _LOOP_EACH(res.data[i][j] = data[i][j] + other.data[i][j]);
            return res;
        }
        /// @brief 矩阵减法运算符重载
        /// @details 矩阵减法运算，返回矩阵相减结果
        /// @param other 另一个矩阵
        /// @return 矩阵减法结果
        constexpr Matrix operator-(const Matrix& other) const {
            Matrix res;
            _LOOP_EACH(res.data[i][j] = data[i][j] - other.data[i][j]);
            return res;
        }
        /// @brief 矩阵数乘运算符重载
        /// @details 矩阵数乘运算，返回矩阵与标量相乘结果
        /// @param scalar 标量
        /// @return 矩阵数乘结果
        constexpr Matrix operator*(T scalar) const {
            Matrix res;
            _LOOP_EACH(res.data[i][j] = data[i][j] * scalar);
            return res;
        }
        /// @brief 矩阵数乘(1/scalar)运算符重载
        /// @details 矩阵数乘(1/scalar)运算，返回矩阵与标量相乘结果
        /// @param scalar 标量
        /// @return 矩阵数乘(1/scalar)结果
        constexpr Matrix operator/(T scalar) const {
            Matrix res;
            _LOOP_EACH(res.data[i][j] = data[i][j] / scalar);
            return res;
        }
        /// @brief 矩阵加且赋值运算符重载
        /// @details 相当于 this = this + other
        /// @param other 另一个矩阵
        /// @return 矩阵加且赋值结果
        constexpr Matrix& operator+=(const Matrix& other) {
            _LOOP_EACH(data[i][j] += other.data[i][j]);
            return *this;
        }
        /// @brief 矩阵减且赋值运算符重载
        /// @details 相当于 this = this - other
        /// @param other 另一个矩阵
        /// @return 矩阵减且赋值结果
        constexpr Matrix& operator-=(const Matrix& other) {
            _LOOP_EACH(data[i][j] -= other.data[i][j]);
            return *this;
        }
        /// @brief 矩阵数乘且赋值运算符重载
        /// @details 相当于 this = this * scalar
        /// @param scalar 标量
        /// @return 矩阵数乘且赋值结果
        constexpr Matrix& operator*=(T scalar) {
            _LOOP_EACH(data[i][j] *= scalar);
            return *this;
        }
        /// @brief 矩阵数乘(1/scalar)且赋值运算符重载
        /// @details 相当于 this = this / scalar
        /// @param scalar 标量
        /// @return 矩阵数乘(1/scalar)且赋值结果
        constexpr Matrix& operator/=(T scalar) {
            _LOOP_EACH(data[i][j] /= scalar);
            return *this;
        }
        /// @brief 矩阵负号运算符重载
        /// @details 相当于 0 - this
        /// @return 矩阵负号运算结果
        constexpr Matrix operator-() const { return 0 - *this; }
        /// @brief 矩阵加号运算符重载
        /// @return 自身
        constexpr Matrix operator+() const { return *this; }
        /// @brief 矩阵数乘运算符重载
        /// @details 矩阵数乘运算，返回矩阵与标量相乘结果
        /// @param scalar 标量
        /// @return 矩阵数乘结果
        friend constexpr Matrix operator*(T scalar, const Matrix& mat) { return mat * scalar; }

        /// @brief 矩阵乘法运算符重载
        /// @details 执行矩阵乘法时要确保左操作数的列数等于右操作数的行数
        /// @tparam P 另一个矩阵的列数
        /// @param other 另一个矩阵
        /// @return 矩阵乘法结果
        template<size P>
            requires (P > 0)
        constexpr Matrix<M, P, T> operator*(const Matrix<N, P, T>& other) const {
            Matrix<M, P, T> res;
            for (size i = 0; i < M; i++)
                for (size j = 0; j < P; j++)
                    for (size k = 0; k < N; k++)
                        res[i][j] += data[i][k] * other[k][j];
            return res;
        }

        /// @brief 等于比较运算符重载
        /// @details 矩阵相等比较，若所有元素都相等则返回 true，否则返回 false
        /// @details 此函数对于浮点数比较是安全的
        /// @param other 另一个矩阵
        /// @return 相等比较结果
        constexpr bool operator==(const Matrix& other) const {
            if constexpr (std::numeric_limits<T>::is_integer) {
                _LOOP_EACH(if (data[i][j] != other.data[i][j]) return false);
                return true;
            }
            _LOOP_EACH({
                if (!_GFt_private_::_fsafe_equal(data[i][j], other.data[i][j]))
                    return false;
                });
            return true;
        }
        /// @brief 不等于比较运算符重载
        /// @details 相当于 !(*this == other)
        /// @param other 另一个矩阵
        /// @return 不等比较结果
        constexpr bool operator!=(const Matrix& other) const {
            return !(*this == other);
        }
        /// @brief 获取矩阵的行数
        /// @return 矩阵的行数
        consteval size rows() const { return M; }
        /// @brief 获取矩阵的列数
        /// @return 矩阵的列数
        consteval size cols() const { return N; }
        /// @brief 获取矩阵的元素个数
        /// @return 矩阵的元素个数
        consteval size count() const { return M * N; }
        /// @brief 求矩阵的转置矩阵
        /// @return 转置矩阵
        constexpr Matrix<N, M, T> transpose() const {
            Matrix<N, M, T> res;
            _LOOP_EACH(res[j][i] = data[i][j]);
            return res;
        }
        /// @brief 求矩阵的行列式值
        /// @details 采用定义式求行列式值
        /// @details 若矩阵不是方阵，则返回零值
        /// @return 矩阵的行列式值
        constexpr T det() const {
            if constexpr (M != N)
                return static_cast<T>(0);
            T result = static_cast<T>(0);
            if constexpr (M == 1 || N == 1) {
                result = data[0][0];
            }
            else {
                for (size i = 0; i < M; i++) {
                    Matrix<M - 1, N - 1, T> submat;
                    for (size j = 1; j < M; j++)
                        for (size k = 0; k < N; k++)
                            if (k != i)
                                submat[j - 1][k >= i ? k - 1 : k] = data[j][k];
                    result += data[0][i] * submat.det() * ((i & 1) ? -1 : 1);
                }
            }
            return result;
        }
        /// @brief 求矩阵的伴随矩阵
        /// @details 采用伴随矩阵定义式求伴随矩阵
        /// @return 伴随矩阵
        constexpr Matrix adjugate() const {
            Matrix adjMat;
            for (size i = 0; i < M; i++)
                for (size j = 0; j < N; j++) {
                    // 构造余子式
                    Matrix<M - 1, N - 1, T> submat;
                    for (size m = 0; m < M; m++)
                        for (size n = 0; n < N; n++)
                            if (m != i && n != j)
                                submat[m > i ? m - 1 : m][n > j ? n - 1 : n] = data[m][n];
                    auto subdet = submat.det(); // 计算余子式的行列式值
                    // 代数余子式
                    adjMat[j][i] = ((i + j) & 1) ? -subdet : subdet;
                }
            return adjMat;
        }
        /// @brief 求矩阵的逆矩阵
        /// @details 采用伴随矩阵法求逆矩阵
        /// @details 若矩阵不可逆，则返回零矩阵
        /// @return 逆矩阵
        constexpr Matrix inverse() const {
            // 矩阵必须为方阵
            if constexpr (M != N)
                return Matrix();
            // 矩阵的行列式值必须不为零
            T tdet = det();
            if (tdet == 0)
                return Matrix();
            // 计算逆矩阵
            Matrix adjMat = adjugate();
            return adjMat / tdet;
        }
        /// @brief 执行矩阵误差修正操作
        /// @details 此操作为将矩阵元素与最近邻整数差值小于 eis 的元素都置为最近邻整数
        /// @details 对于非浮点数矩阵，此操作无效
        /// @param eis 误差范围
        const Matrix& correct(T eis = static_cast<T>(1e-6)) {
            if constexpr (std::is_floating_point_v<T>) {
                using namespace _GFt_private_;
                _LOOP_EACH({
                    if (_fsafe_equal(data[i][j], static_cast<T>(0), eis))
                        data[i][j] = 0;
                    else if (_fsafe_equal(data[i][j], std::floor(data[i][j]), eis))
                        data[i][j] = std::floor(data[i][j]);
                    else if (_fsafe_equal(data[i][j], std::ceil(data[i][j]), eis))
                        data[i][j] = std::ceil(data[i][j]);
                    });
            }
            return *this;
        }
        
        /// @brief 矩阵类型转换函数
        /// @details 矩阵类型转换函数，将矩阵的元素类型转换为 U 类型
        /// @tparam U 目标类型
        /// @param mat 矩阵对象
        /// @return 转换后的矩阵对象
        template<typename U>
            requires std::is_arithmetic_v<U>
        constexpr explicit operator Matrix<M, N, U>() const {
            Matrix<M, N, U> res;
            _LOOP_EACH(res.data[i][j] = static_cast<U>(this->data[i][j]));
            return res;
        }
    };

    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 预定义模板特化类型
    /// @{

    template<typename T>
        requires std::is_arithmetic_v<T>
    using Mat2x2 = Matrix<2, 2, T>; ///< 2x2 矩阵类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    using Mat3x3 = Matrix<3, 3, T>; ///< 3x3 矩阵类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    using Mat4x4 = Matrix<4, 4, T>; ///< 4x4 矩阵类型
    using iMat2x2 = Mat2x2<int>;    ///< 2x2 整数矩阵类型
    using iMat3x3 = Mat3x3<int>;    ///< 3x3 整数矩阵类型
    using iMat4x4 = Mat4x4<int>;    ///< 4x4 整数矩阵类型
    using fMat2x2 = Mat2x2<float>;  ///< 2x2 浮点矩阵类型
    using fMat3x3 = Mat3x3<float>;  ///< 3x3 浮点矩阵类型
    using fMat4x4 = Mat4x4<float>;  ///< 4x4 浮点矩阵类型
    template<size N, typename T>
        requires (N > 0) && std::is_arithmetic_v<T>
    using Vec = Matrix<1, N, T>;    ///< 向量类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    using Vec2 = Vec<2, T>;         ///< 二维向量类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    using Vec3 = Vec<3, T>;         ///< 三维向量类型
    template<typename T>
        requires std::is_arithmetic_v<T>
    using Vec4 = Vec<4, T>;         ///< 四维向量类型
    using iVec2 = Vec2<int>;        ///< 二维整数向量类型
    using iVec3 = Vec3<int>;        ///< 三维整数向量类型
    using iVec4 = Vec4<int>;        ///< 四维整数向量类型
    using fVec2 = Vec2<float>;      ///< 二维浮点向量类型
    using fVec3 = Vec3<float>;      ///< 三维浮点向量类型
    using fVec4 = Vec4<float>;      ///< 四维浮点向量类型

    /// @}
    /// @}

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
}

#undef _LOOP_EACH