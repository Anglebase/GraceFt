# GraceFt - C++图形应用程序框架

## 简介

GraceFt 是一款基于开源图形引擎 EGE (Easy Graphics Engine) 的 C++ 图形应用程序开发框架。它提供了一系列高层封装，使得开发者可以快速地开发出具有图形界面的应用程序。GraceFt 的使用风格与 Qt 相似，但与它的名字一样，相较于 Qt，GraceFt 更加地优雅和简洁。GraceFt 的一大特点是它基于原生 C++ 实现了声明式 UI 的语法，使得代码更加易读。

## 特点

- **简洁性** ：GraceFt 提供了简洁的 API，使得开发过程更加直观。
- **面向对象** ：框架设计遵循面向对象的原则，易于理解和使用。
- **灵活性** ：开发者可以根据需要自由地扩展和定制功能。
- **声明式语法** ：GraceFt 基于原生 C++ 实现声明式UI语法，使得代码更加易读。

## GraceFt 配置

请按照以下步骤安装 GraceFt：

1. 克隆 GraceFt 的代码库：
   ```
   git clone https://github.com/Anglebase/GraceFt.git
   ```
2. 进入项目目录：
   ```
   cd GraceFt
   ```
3. 编译 GraceFt：
   ```
   cmake -B build -S .
   cmake --build build --config Release
   ```
4. 在生成出的 lib 文件夹下就可以找到编译出的静态库文件
5. 将include/GraceFt目录下的所有头文件引入到你的项目中，便可以开发你的应用程序了
6. 在编译时链接 GraceFt 静态库文件，并添加其它必要的链接库(如相应的 EGE 库)

**GraceFt 需要至少 C++20 编译器支持**

## 快速入门

以下是使用 GraceFt 开发一个简单应用程序的示例：

```cpp
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
```
**[使用模板快速创建项目](https://github.com/Anglebase/GraceFt/releases)**

## 文档

完整的 API 文档和使用指南可以在 [这里](https://anglebase.github.io/GraceFt-Doc/) 找到。

## 贡献

我们欢迎任何形式的贡献，包括但不限于：

- 代码提交
- 功能请求
- 问题报告

请在提交前阅读 [贡献指南](./doc/guide.md)。

## 许可证

GraceFt 遵循 [MIT 许可证](https://opensource.org/licenses/MIT)。有关详细信息，请查看 [`LICENSE`](./LICENSE) 文件。

## 开发者
 - [Anglebase](https://github.com/Anglebase)

## 致谢
