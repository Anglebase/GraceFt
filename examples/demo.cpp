#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Tools.h>

int main() {
    using namespace GFt::literals;

    GFt::Block block{
        GFt::iRect{ 5_sw,5_sh,60_sw,60_sh, }
    };
    auto window =
        GFt::Window::createWindow(&block);

    GFt::Application app(window);
    window->show();
    return app.exec();
}