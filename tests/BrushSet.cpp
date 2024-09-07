#include <BrushSet.h>

using namespace std;
using namespace GFt;

int main() {
    BrushSet brushSet(0xffffff_rgb);
    brushSet.setFillStyle(0xffff00_rgb, FillStyle::Line);
    brushSet.setLinearGradient(
        fPoint(0, 0), Color(0x0000ff_rgb),
        fPoint(100, 100), Color(0xff0000_rgb)
    );
    cout << "BrushSet:" << (int)brushSet.getBrushStyle() << endl;
    return 0;
}
