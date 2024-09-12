#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Tools.h>
/**
 * @example BasicFrame.cpp
 *
 * 这是一个最基本的创建窗口的例子，展示了如何使用GraceFt库创建窗口并显示一个空白的窗口
 * 通过`using namespace GFt::literals;`你可以引入设备无关的单位字面量，通过它们你
 * 可以方便地设置设备无关的窗口大小、位置等。
 *
 * 在`GFt::Window`中提供了一系列用于创建窗口的工厂函数，它们可以创建多种不同的窗口模式
 * 以满足不同类型的应用需求。不过，在同一个程序中，你只能创建一个窗口对象实例，当你首次调
 * 用它们这些工厂函数之一时，就会创建窗口，之后再次调用它们将返回同一个窗口对象实例，而不
 * 会创建新的窗口。
 */
int main() {
    using namespace GFt::literals;                   // 引入设备无关字面量转换命名空间

    GFt::Block block{                                // 定义一个空白的窗口块作为窗口的根节点
        GFt::iRect{ 5_sw,5_sh,60_sw,60_sh, }         // 设置设备无关的窗口大小和位置
    };
    auto window =
        GFt::Window::createWindow(&block);           // 创建窗口

    GFt::Application app(window);                    // 创建应用对象
    window->show();                                  // 显示窗口
    return app.exec();                               // 启动事件循环
}