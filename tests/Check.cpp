#include <GraceFt/Application.h>
#include <GraceFt/widget/CheckBox.h>
#include <GraceFt/Block.h>
#include <GraceFt/Window.h>
#include <GraceFt/widget/MainWindow.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::literals;

int main(){
    MainWindow root{L"Radio Test", iRect{100, 100, 800, 600}};
    CheckBox checkBox1{iRect{50, 100, 100, 20}, &root};
    CheckBox checkBox2{iRect{50, 130, 100, 20}, &root};
    CheckBox checkBox3{iRect{50, 160, 100, 20}, &root};
    CheckBox checkBox4{iRect{50, 190, 100, 20}, &root};

    checkBox1.text() = L"checkBox1";
    checkBox2.text() = L"checkBox2";
    checkBox3.text() = L"checkBox3";
    checkBox4.text() = L"checkBox4";

    checkBox1.onCheckChanged.connect([](bool){
        std::cout << "FPS: " << Application::getRealFps() << std::endl;
        std::cout << "Event: " << Application::getEventTime() << std::endl;
        std::cout << "Render: " << Application::getRenderTime() << std::endl;
    });

    Window* window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}