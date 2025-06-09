#include <GraceFt/Matrix.hpp>
#include <GraceFt/LMath.hpp>

using namespace GFt;
using namespace std;

int main() {
    constexpr float data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    constexpr float data2[4][4] = {{1, 2, 1, 4}, {5, 6, 7, 8}, {9, 6, 11, 12}, {13, 4, 5, 16}};
    fMat3x3 m1(data1);
    fMat4x4 m2(data2);
    fVec4 v1 = makefVec4(1, 2, 3, 4);

    cout << v1 * m2 << endl;

    cout << "I:" << fMat4x4::I() << endl;
    cout << "I == I^-1: " << std::boolalpha << (fMat4x4::I() == fMat4x4::I().transpose()) << endl;
    cout << "det(I): " << fMat4x4::I().det() << endl;
    cout << "I^-1:" << fMat4x4::I().inverse() << endl;
    cout << "m1:" << m1 << endl;
    cout << "m2:" << m2 << endl;
    cout << "m1^T:" << m1.transpose() << endl;
    cout << "m2^T:" << m2.transpose() << endl;
    cout << "det(m1): " << m1.det() << endl;
    cout << "det(m2): " << m2.det() << endl;
    cout << "m1^-1:" << m1.inverse() << endl;
    cout << "m2^-1:" << m2.inverse() << endl;
    cout << "m1*m1^-1: " << m1 * m1.inverse() << endl;
    cout << "m2*m2^-1: " << (m2 * m2.inverse()).correct() << endl;
    cout << "m1*m1^-1 == I: " << std::boolalpha << (m1 * m1.inverse() == fMat3x3::I()) << endl;
    cout << "m2*m2^-1 == I: " << std::boolalpha << (m2 * m2.inverse() == fMat4x4::I()) << endl;
    cout << "m2:" << m2.rows() << "x" << m2.cols() << "=" << m2.count() << " elements" << endl;
    
    return 0;
}