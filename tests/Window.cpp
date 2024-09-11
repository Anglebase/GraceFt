#include <Window.h>
#include <iostream>

using namespace std;
using namespace GFt;

int main() {
    Block block{ iRect{ 30,30,800,600 } };
    Window* window = Window::createWindow(&block);

    return 0;
}