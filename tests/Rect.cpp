#include <Rect.hpp>

using namespace GFt;
using namespace std;

int main() {
    iRect rect1(10, 20, 30, 40);
    iPoint point1(15, 25);
    iSize size1(10, 20);
    iRect rect2(point1, size1);

    fRect rect3(1.0f, 2.0f, 3.0f, 4.0f);
    fPoint point2(1.5f, 2.5f);
    fSize size2(1.0f, 2.0f);
    fRect rect4(point2, size2);
    
    cout << "Rect1: " << rect1 << endl;
    cout << "Rect2: " << rect2 << endl;
    cout << "Rect3: " << rect3 << endl;
    cout << "Rect4: " << rect4 << endl;

    return 0;
}