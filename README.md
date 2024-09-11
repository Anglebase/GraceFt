# GraceFt - 快速开发C++图形应用程序

## 简介

GraceFt 是一款基于开源图形引擎 EGE (Easy Graphics Engine) 的 C++ 图形应用程序开发框架。它提供了一系列高层封装，使得开发者可以快速地开发出具有图形界面的应用程序。GraceFt 的使用风格与 Qt 相似，但更加简洁，面向对象，且灵活。

## 特点

- **简洁性**：GraceFt 提供了简洁的 API，使得开发过程更加直观。
- **面向对象**：框架设计遵循面向对象的原则，易于理解和使用。
- **灵活性**：开发者可以根据需要自由地扩展和定制功能。

## 安装

请按照以下步骤安装 GraceFt：

1. 克隆 GraceFt 的代码库：
   ```
   git clone https://github.com/Anglebase/graceft.git
   ```
2. 进入项目目录：
   ```
   cd GraceFt
   ```
3. 编译和安装：
   ```
   cmake -B build -S .
   cmake --build build --config Release
   ```

## 使用

以下是使用 GraceFt 开发一个简单应用程序的示例：

```cpp
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>

int main(int argc, char *argv[]) {
    GraceFt::Application app(argc, argv);

    GraceFt::Window window(800, 600, "Hello, GraceFt!");
    window.show();

    return app.exec();
}
```

## 文档

完整的 API 文档和使用指南可以在 [这里](#) 找到。

## 贡献

我们欢迎任何形式的贡献，包括但不限于：

- 代码提交
- 功能请求
- 问题报告

请在提交前阅读 [贡献指南](#)。

## 许可证

GraceFt 遵循 [MIT 许可证](LICENSE)。有关详细信息，请查看 `LICENSE` 文件。

## 联系方式

- 邮箱：[youremail@example.com](mailto:youremail@example.com)
- 网站：[http://www.yourwebsite.com](http://www.yourwebsite.com)

---

感谢使用 GraceFt，希望它能帮助您快速开发出优秀的 C++ 图形应用程序！
