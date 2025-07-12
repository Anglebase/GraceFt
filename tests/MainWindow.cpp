#include <GraceFt/Application.h>
#include <GraceFt/widget/MainWindow.h>
#include <GraceFt/Window.h>
#include <GraceFt/Graphics.h>

using namespace GFt;
using namespace GFt::Widget;

class MyMainWindow : public MainWindow {
protected:
    void onDraw(Graphics& g) override {
        // Graphics g;
        // g.drawFillCircle(fCircle{ fPoint{ 0.f,0.f}, 50.f });
    }
public:
    MyMainWindow(const std::wstring& title, const iRect& rect) : MainWindow(title, rect) {}
};

int main() {
    MyMainWindow mainwindow{ L"GFt Main Window", iRect{50, 50, 800, 600} };

    Window* window = Window::createWindow(&mainwindow);
    Application app{ window };
    window->show();
    return app.run();
}