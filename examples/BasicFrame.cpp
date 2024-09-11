#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Tools.h>

// 这里提供了一个最基本的窗口创建和显示的例子，展示了如何使用GraceFt库。

int main() {
    using namespace GFt::literals;                   // 引入设备无关字面量转换命名空间

    auto window =
        GFt::Window::createWindow(                   // 创建窗口
            GFt::iRect{ 5_sw,5_sh,60_sw,60_sh, }     // 设置设备无关的窗口大小
        );

    GFt::Application app(window);                    // 创建应用对象
    return app.exec();                               // 启动事件循环
}