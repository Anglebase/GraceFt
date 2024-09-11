#include <TextSet.h>

using namespace std;
using namespace GFt;
using namespace GFt::literals;

int main() {
    TextSet ts(0xff00ff_rgb);

    Font font(L"Arial", 24);
    ts.setFont(font);

    return 0;
}