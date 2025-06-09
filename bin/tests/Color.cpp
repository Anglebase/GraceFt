#include <GraceFt/Color.h>

using namespace std;
using namespace GFt;

int main() {
    Color c1(255, 0, 0);
    Color c2(0, 255, 0);
    Color c3(0, 0, 255);

    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;

    auto [h, s, l] = c1.toHSL();
    cout << "c1 HSL: " << h << ", " << s << ", " << l << endl;

    return 0;
}