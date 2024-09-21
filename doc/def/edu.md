# GraceFt 教程

## 基本介绍
GraceFt 是一款基于 C++ 开源图形引擎 [EGE(Easy Graphics Engine)](https://club.xege.org/) 的图形应用程序框架，GracFt 基于[GPL v3.0](https://www.gnu.org/licenses/gpl-3.0.html)开源协议开源。GraceFt 的一大特色是它完全基于原生的C++实现了**声明式**的界面编程模型，使得界面开发更加简单、直观。目前，GraecFt 的所有内容全部位于命名空间 GFt 下, GFt 中分为3个主要模块: GFt::UI 、 GFt::Widget 和 GFt 根命名空间。GFt 的根命名空间提供了一系列基础设施, GFt::Widget 提供了一些常用部件, GFt::UI 提供了声明式的界面编程模型的实现支持；其次 GFt 中还有 GFt::literals 命名空间提供了一些方便的字面量定义。

## 环境配置
1. **确保你的电脑上已经安装了至少支持 C++20 的编译器**: GracFt 是基于 C++20 开发的，所以你的编译器必须支持 C++20 才能编译 GraceFt 项目
2. **确保你的电脑上已经安装了 CMake 3.15 或以上版本**: GraceFt 项目是使用 CMake 构建的，所以你需要确保你的电脑上已经安装了 CMake 3.15 或以上版本
3. **下载项目模板或手动配置项目环境**: 你可以从 [Github](https://github.com/Graceful-Engineering-Team/GraceFt) 下载项目模板，或者手动配置自己习惯的项目环境
4. **从此刻开始，你就可以开始编写你的 GraceFt 项目了！**

## Hello World

### 定义式界面编程模型

下面是一个简单的 "Hello World" 程序，展示了如何基于定义式的界面编程模型，使用 GraceFt 编写一个窗口程序：

**首先，你需要包含构建应用程序相关的 GraceFt 头文件：**
```cpp
#include <GraceFt/Application.h>
```
在这个文件中定义了一个 `GFt::Application` 类，它是 GraceFt 应用程序的入口类，掌管着整个应用程序的事件循环。

**同时，也需要包含一个用于构建窗口的头文件：**
```cpp
#include <GraceFt/Window.h>
```
在这个文件中定义了一个 `GFt::Window` 类，它管理着窗口的各种属性和行为，它是由单例模式+工厂模式实现的，这意味着你只能创建一个 `GFt::Window` 对象。

**接下来就是 GraceFt 的核心了，你需要包含一个头文件来创建UI对象：**
```cpp
#include <GraceFt/Block.h>
```
这个头文件定义了一个 `GFt::Block` 类，它是 GraceFt 界面编程模型的核心类，也是所有界面元素的基类，你可以通过继承 `GFt::Block` 类来创建各种类型的界面元素。

**通过继承 `GFt::Block` 类，你就可以创建你的第一个界面元素了，比如一个 `GFt::HelloBlock` 对象：**
```cpp
class HelloBlock : public GFt::Block
{
protected:
    void onDraw(const GFt::iRect& rect) override {
        GFt::Graphics g;
        auto r = GFt::iRect{GFt::iPoint(), rect.size()};
        g.drawText(L"Hello World!", r, GFt::TextAlign::Center|GFt::TextAlign::Middle);
    }
public:
    HelloBlock(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex) {}
};
```
为了能够使用 `GFt::Graphics` 类绘制文本，你需要包含 `GraceFt/Graphics.h` 头文件。
```cpp
#include <GraceFt/Graphics.h>
```
新的 `HelloBlock` 类继承自 `GFt::Block` 类，并重写了 `onDraw` 方法，在这个方法中，我们使用 `GFt::Graphics` 类在指定的矩形区域内居中的位置绘制了一个文本 "Hello World!"。接下来演示该如何使用这个类来构建图形用户界面。

**最后，实现main函数，并启用 GraceFt 应用程序的事件循环：**
首先要创建UI对象节点树，不过这个示例只有一个UI对象，所以节点树只有一个根节点：
```cpp
GFt::HelloBlock root{iRect{100, 100, 640, 480}};
```
处于简单起见，我们这里将窗口对象设置为栈变量，不过在实际项目中，你应该使用尽量使用堆内存分配窗口对象，因为UI元素的生命周期往往远长于栈变量的生命周期。

然后，我们基于这个对象来创建一个窗口对象，并将它显示在屏幕上：
```cpp
GFt::Window* window = GFt::Window::createWindow(&root);
window->show();
```
正如刚刚所说，`GFt::Window` 是一个单例模式+工厂模式的类，所以你只能创建一个 `GFt::Window` 对象，之后再通过创建窗口的工厂函数尝试创建对象时，都会返回已经创建的窗口对象实例。创建窗口之后，你就可以调用 `show` 方法将窗口显示在屏幕上，如果没有调用 `show` 方法，窗口将不会显示在屏幕上。构造窗口对象时，会将根节点的矩形区域作为窗口在桌面上的初始位置和大小。

最后，你需要基于刚才创建的窗口对象再创建一个 `GFt::Application` 对象，并启动事件循环：
```cpp
GFt::Application app{window};
app.run();
```
类 `GFt::Application` 是专门用来管理事件循环的类，它会监听窗口的各种事件，并把这些事件分发给相应的元素进行处理。

下面是完整的程序：
```cpp
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Block.h>
#include <GraceFt/Graphics.h>

class HelloBlock : public GFt::Block
{
protected:
    void onDraw(const GFt::iRect& rect) override {
        GFt::Graphics g;
        auto r = GFt::iRect{GFt::iPoint(), rect.size()};
        g.drawText(L"Hello World!", r, GFt::TextAlign::Center|GFt::TextAlign::Middle);
    }
public:
    HelloBlock(const GFt::iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex) {}
};

int main()
{
    HelloBlock root{GFt::iRect{100, 100, 640, 480}};
    GFt::Window* window = GFt::Window::createWindow(&root);
    window->show();
    GFt::Application app{window};
    return app.run();
}
```
编译并运行程序，你将会看到一个窗口出现在屏幕上，上面显示着 "Hello World!" 文本。

但代码中频繁出现的 `GFt` 会令人感到厌烦，因此也可以通过 `using namespace` 来简化代码：
```cpp
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Block.h>
#include <GraceFt/Graphics.h>

using namespace GFt;

class HelloBlock : public Block
{
protected:
    void onDraw(const iRect& rect) override {
        Graphics g;
        auto r = iRect{iPoint(), rect.size()};
        g.drawText(L"Hello World!", r, TextAlign::Center|TextAlign::Middle);
    }
public:
    HelloBlock(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex) {}
};

int main()
{
    HelloBlock root{iRect{100, 100, 640, 480}};
    Window* window = Window::createWindow(&root);
    window->show();
    Application app{window};
    return app.run();
}
```
这样，代码更加简洁，更加易读，但是需要注意的是头文件中不应该包含 `using namespace` 语句，否则可能会导致名称歧义错误。

这是 GraceFt 的定义式的界面编程模型的基本用法，你可以通过继承 `GFt::Block` 类来创建各种类型的界面元素，并通过 `GFt::Window` 类来管理窗口的各种属性和行为，通过 `GFt::Application` 类来管理事件循环。接下来，将通过另一个Hello World示例来展示如何使用 GraecFt 的声明式的界面编程模型来创建窗口程序。

### 声明式界面编程模型

GraceFt 的声明式界面编程模型是基于 C++20 的[指派符列表初始化](https://zh.cppreference.com/w/cpp/language/list_initialization)实现的，它提供了一种更加简洁的声明式的界面编程模型，使得界面开发更加简单、直观。下面是一个简单的 "Hello World" 程序，展示了如何基于声明式的界面编程模型，使用 GraceFt 编写一个窗口程序：
```cpp
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/UI.h>

int main() {
    GFt::UI::XWindow{
        .name = "Root",
        .rect = GFt::iRect{50,50,640,480},
        .content = [](GFt::Block& block) {
            GFt::UI::XLabel{
                .name = "HelloLabel",
                .text = L"Nothing to see here",
                .rect = GFt::iRect{250,150,140,180},
                .parent = block,
                .content = [](GFt::Widget::Label& label) {
                    label.text() = L"Hello, world!";
                }
            };
        }
    };

    GFt::Window* window = GFt::Window::createWindow(BLOCK(Root));
    window->show();
    GFt::Application app{ window };
    return app.run();
}
```
通过这段代码，可以产生一个与之前定义式的界面编程模型显示内容完全相同的窗口程序。声明式界面编程模型的实现利用了无名对象在语句结束时会立即析构的特性，通过析构函数向声明式UI管理器注册UI对象并构建对象树，同时还提供了一些方便的宏来简化代码，例如 `BLOCK` 宏用来获取指定的UI对象指针。声明式的界面编程模型是函数式的，这意味着代码可以被简单地重用和组合，使得界面开发更加灵活、可扩展。对于上面这段代码，也可以通过 `using namespace` 来简化代码：
```cpp
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/UI.h>

using namespace GFt;
using namespace GFt::UI;
using namespace GFt::Widget;

int main() {
    XWindow{
        .name = "Root",
        .rect = iRect{50,50,640,480},
        .content = [](Block& block) {
            XLabel{
                .name = "HelloLabel",
                .text = L"Nothing to see here",
                .rect = iRect{250,150,140,180},
                .parent = block,
                .content = [](Label& label) {
                    label.text() = L"Hello, world!";
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK(Root));
    window->show();
    Application app{ window };
    return app.run();
}
```
声明式的界面编程模型的底层依然是使用定义式的UI类实现的，但是它相对于定义式的界面编程模型，提供了更加简洁的语法，使得代码更加易读、易写。

## 核心架构

### 对象树
在 GraceFt 中，所有的 UI 元素都被组织成一个树状结构，称为对象树，这类似于 HTML 文档的 DOM 树。对象树的每个元素都是 `GFt::Block` 类的子类构建的，它是所有 UI 元素的基类，它提供了一些基本的属性和行为，例如位置、尺寸、父节点、子节点、Z轴顺序等。在声明式的界面编程模型中，可以通过比定义式的界面编程模型更加简单直观的方式去构建对象树。

### 事件循环
事件循环是所有图形应用程序的核心，它负责监听窗口的各种事件，并把这些事件分发给相应的元素进行处理。在 GraceFt 中，事件循环的这些行为是由 `GFt::Application` 类来管理的。为了优化事件循环的性能，GraceFt 摒弃了整树遍历的方式，而是采用了事件分发的方式，这使得事件处理更加高效。对于窗口来说，事件分为三大类，分别为绘制事件、鼠标事件和键盘事件。如果在事件循环中启用了裁剪优化，那么 GraceFt 将不会绘制与父节点区域没有交际的子节点，这可以提高绘制效率，但如果你不希望它们不被绘制可以通过 `GFt::Application::exec()` 的参数关闭裁剪优化，它默认是开启的。对于鼠标事件来说，GraceFt 的事件循环将依据当前的鼠标位置来确定哪个元素应该响应鼠标事件，并将事件传递给相应的元素(参见 `GFt::Block::onMouseButtonPress()` 方法的文档)。对于键盘事件来说，GraceFt 的事件循环将依据当前的键盘焦点来确定哪个元素应该响应键盘事件，并将事件传递给相应的元素(参见 `GFt::Block::onKeyPress()` 方法的文档)。

## 基于模板项目创建新项目

为了便于开发者的使用，GraceFt 提供了 GraceFt 项目模板，你可以从[Github](https://github.com/Anglebase/GraceFt/releases)上获取它，下面将介绍如何基于模板项目创建新项目。

### 准备工作
1. 确保你的电脑上已经安装 CMake 3.15 或以上版本和至少支持 C++20 的编译器(推荐使用[GCC 14.2](https://github.com/skeeto/w64devkit/releases)或更高版本)
2. 下载项目模板并解压到你喜欢的目录，使用你习惯的IDE打开项目目录(推荐使用[Visual Studio Code](https://code.visualstudio.com/))
*3. 通过启用 CMake 构建可以得到一个Hello GraceFt的示例程序*