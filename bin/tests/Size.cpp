#include <GraceFt/Size.hpp>

using namespace GFt;
using namespace std;

int main() {
    iSize s1(10, 20);
    iSize s2(30, 40);
    iSize s3 = s1 + s2;
    iSize s4 = s1 - s2;
    iSize s5 = s1 * 2;
    
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
    cout << "s5: " << s5 << endl;
    
    return 0;
}