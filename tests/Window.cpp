#include <Window.h>
#include <iostream>

using namespace std;
using namespace GFt;

int main() {
    Window* window = Window::createWindow(iRect{ 30,30,800,600 });
    window->stop();
    return 0;
}