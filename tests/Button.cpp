#include <Application.h>
#include <Button.h>
#include <Window.h>

using namespace GFt;

class MyWindow : public Block {
    Button* button;
    void onButtonClicked() {
        std::cout << "Button clicked!" << std::endl;
    }
public:
    MyWindow(const iRect& rect) : Block(rect) {
        using namespace GFt::literals;
        button = new Button(L"点我", iRect(10, 10, 200, 60), this);
        button->brushSet().setFillStyle(0x00ffff_rgb);
        button->onClicked.connect(this, &MyWindow::onButtonClicked);
        button->HoverOn.connect([this](Block* block) {
            this->button->brushSet().setFillStyle(0x0000ff_rgb);
            });
        button->HoverOff.connect([this](Block* block) {
            this->button->brushSet().setFillStyle(0x00ffff_rgb);
        });
    }
    ~MyWindow() {
        delete button;
    }
};

int main() {
    MyWindow root(iRect(100, 100, 300, 200));
    Window* window = Window::createWindow(&root);
    Application app(window);
    Application::setFps(60);
    window->show();
    return app.run();
}