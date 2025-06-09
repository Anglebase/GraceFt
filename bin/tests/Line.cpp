#include <GraceFt/Line.hpp>

using namespace std;
using namespace GFt;

int main() {
    fLine line1(fPoint(0, 0), fPoint(10, 10));
    fLine line2(fPoint(5, 5), fPoint(15, 15));

    cout << "Line 1: " << line1 << endl;
    cout << "Line 2: " << line2 << endl;

    cout << "Line1.dis: " << line1.distance() << endl;
    cout << "Line2.mht: " << line2.manhatten_distance() << endl;

    cout << "same: " << line1.isCollinearWith(line2) << endl;
    return 0;
}