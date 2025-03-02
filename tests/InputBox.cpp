#include <Application.h>
#include <widget/InputBox.h>
#include <Window.h>

using namespace GFt;
using namespace GFt::Widget;

class MyWindow : public Block {
    InputBox* input;

    void printContentLength(const std::wstring& s){
        input->setPlaceholder(std::to_wstring(s.size()) + L"个字符");
        input->clearContent();
    }
public:
    MyWindow(const iRect& rect) : Block(rect) {
        using namespace GFt::literals;
        input = new InputBox(iRect(10, 10, 200, 60), this, std::wstring(L"请输入内容..."));
        input->onEnter.connect(this, &MyWindow::printContentLength);
    }
    ~MyWindow() {
        delete input;
    }
};

int main() {
    MyWindow root(iRect(100, 100, 300, 200));
    Window* window = Window::createWindow(&root);
    Application app(window);
    window->show();
    return app.run();
}