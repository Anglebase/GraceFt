#include <GraceFt/widget/ScrollBar.h>
#include <GraceFt/widget/MainWindow.h>
#include <GraceFt/Window.h>
#include <GraceFt/Application.h>

using namespace GFt;
using namespace GFt::Widget;

int main() {
    MainWindow window{ L"Slider Test", iRect{100, 100, 800, 600} };

    VScrollBar vsb{ iRect{50, 50, 20, 400}, &window };
    vsb.setCompleteSize(1000);
    vsb.setStep(10);
    vsb.onCurrentPosChanged.connect([](float pos) {
        std::cout << "Vertical ScrollBar pos: " << pos << std::endl;
        });
    HScrollBar hsb{ iRect{100, 50, 400, 20}, &window };
    hsb.setCompleteSize(1000);
    hsb.setStep(10);
    hsb.onCurrentPosChanged.connect([](float pos) {
        std::cout << "Horizontal ScrollBar pos: " << pos << std::endl;
        });

    Window* w = Window::createWindow(&window);
    Application app{ w };
    w->show();
    return app.run();
}