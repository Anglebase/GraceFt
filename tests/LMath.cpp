#include <LMath.hpp>

using namespace GFt;
using namespace std;

int main() {
    fVec3 v1 = makefVec3(1.0f, 2.0f, 3.0f);
    fVec3 v2 = makefVec3(4.0f, 5.0f, 6.0f);
    auto a = v1 * v2;
    auto b = v1 ^ v2;
    cout << "v1 * v2 = " << a << endl;
    cout << "v1 ^ v2 = " << b << endl;
    cout << "inner product = " << ((v1 | v2) == v1 * v2) << endl;
    return 0;
}