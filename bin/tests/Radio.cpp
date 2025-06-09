#include <GraceFt/Application.h>
#include <GraceFt/widget/RadioBox.h>
#include <GraceFt/Block.h>
#include <GraceFt/Window.h>
#include <GraceFt/widget/MainWindow.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::literals;

int main(){
    MainWindow root{L"Radio Test", iRect{100, 100, 800, 600}};
    RadioManager radioManager;
    RadioBox radioBox1{radioManager, iRect{50, 100, 100, 20}, &root};
    RadioBox radioBox2{radioManager, iRect{50, 130, 100, 20}, &root};
    RadioBox radioBox3{radioManager, iRect{50, 160, 100, 20}, &root};
    RadioBox radioBox4{radioManager, iRect{50, 190, 100, 20}, &root};

    radioBox1.text() = L"RadioBox1";
    radioBox2.text() = L"RadioBox2";
    radioBox3.text() = L"RadioBox3";
    radioBox4.text() = L"RadioBox4";

    radioBox1.onCheckChanged.connect([](bool){
        std::cout << "FPS: " << Application::getRealFps() << std::endl;
        std::cout << "Event: " << Application::getEventTime() << std::endl;
        std::cout << "Render: " << Application::getRenderTime() << std::endl;
    });

    Window* window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}