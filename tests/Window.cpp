#include <GraceFt/Window.h>
#include <GraceFt/Application.h>
#include <GraceFt/widget/Button.h>
#include <iostream>

using namespace std;
using namespace GFt;
using namespace GFt::literals;
using namespace GFt::Widget;

int main() {
    Block block{ iRect{ 50,50,800,600 } };

    Button btn1{ L"置顶窗口" , iRect{ 10,10,100,50 },&block };
    Button btn2{ L"取消置顶", iRect{ 120,10,100,50 },&block };
    Button btn3{ L"移除边框", iRect{ 230,10,100,50 },&block };
    Button btn4{ L"显示边框", iRect{ 340,10,100,50 },&block };
    Button btn5{ L"透明", iRect{ 450,10,100,50 },&block };
    Button btn6{ L"不透明", iRect{ 560,10,100,50 },&block };
    Button btn7{ L"最小化", iRect{ 670,10,100,50 },&block };
    Button btn8{ L"全屏", iRect{ 10,65,100,50 },&block };
    Button btn9{ L"还原", iRect{ 120,65,100,50 },&block };
    Button btn10{ L"最大化", iRect{ 230,65,100,50 },&block };

    btn1.onClicked.connect([]{ Window::window()->setTopMost(true); });
    btn2.onClicked.connect([]{ Window::window()->setTopMost(false); });
    btn3.onClicked.connect([]{ Window::window()->setFrameless(true); });
    btn4.onClicked.connect([]{ Window::window()->setFrameless(false); });
    btn5.onClicked.connect([]{ Window::window()->setAlpha(.8f); });
    btn6.onClicked.connect([]{ Window::window()->setAlpha(1.f); });
    btn7.onClicked.connect([]{ Window::window()->minimize(); });
    btn8.onClicked.connect([]{ Window::window()->fullscreen(); });
    btn9.onClicked.connect([]{ Window::window()->restore(); });
    btn10.onClicked.connect([]{ Window::window()->maximize(); });

    Window* window = Window::createWindow(&block);

    Application app{ window };
    window->show();
    return app.run();
}