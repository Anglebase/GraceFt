#include <Application.h>
#include <widget/Button.h>
#include <Window.h>

using namespace GFt;
using namespace GFt::Widget;

class MyWindow : public Block {
    Button* button;
    void onButtonClicked() {
        std::cout << "Button clicked!" << std::endl;
        static int count = 0;
        count++;
        if (count >= 5)
            button->setEnable(false);
    }
public:
    MyWindow(const iRect& rect) : Block(rect) {
        using namespace GFt::literals;
        button = new Button(L"点我", iRect(10, 10, 200, 60), this);
        button->onClicked.connect(this, &MyWindow::onButtonClicked);
    }
    ~MyWindow() {
        delete button;
    }
};

int main() {
    MyWindow root(iRect(100, 100, 300, 200));
    Window* window = Window::createWindow(&root);
    Application app(window);
    window->show();
    return app.run();
}