#include <widget/MainWindow.h>
#include <widget/Slider.h>
#include <Window.h>
#include <Application.h>

using namespace GFt;
using namespace GFt::Widget;

int main() {
    MainWindow window{ L"Slider Test", iRect{100, 100, 800, 600} };

    HSlider slider{ iRect{ 100, 100, 200, 50 }, &window };
    slider.onValueChanged.connect([](float value) {
        std::cout << "Slider value changed to " << value << std::endl;
        });
    VSlider vslider{ iRect{ 100, 200, 50, 200 }, &window };
    vslider.onValueChanged.connect([](float value) {
        std::cout << "Vertical slider value changed to " << value << std::endl;
        });

    Window* w = Window::createWindow(&window);
    Application app{ w };
    w->show();
    return app.run();
}