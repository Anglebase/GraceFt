#include <widget/UI.h>
#include <Application.h>

using namespace GFt::UI;
using namespace GFt;
using namespace GFt::Widget;

void RowLayoutContent(RowLayout& it) {
    it.setSpace(5);
    it.setPadding(5);
    XButton{
        .name = "Button1",
        .rect = iRect{100,100,100,100},
        .parent = it,
        .content = [](Button& it) {
            it.text() = L"Button1";
            it.onClicked.connect([&it] {
                std::cout << "Button1 clicked" << std::endl;
                it.setZIndex(it.getZIndex() + 1);
                auto obj = BLOCK("Button2");
                std::cout << "Button2 z-index: " << dynamic_cast<Button*>(obj)->getZIndex() << std::endl;
                std::cout << "Button1 z-index: " << it.getZIndex() << std::endl;
            });
        }
    };
    it.addItem(BLOCK("Button1"));
    XButton{
        .name = "Button2",
        .rect = iRect{150,150,100,100},
        .parent = it,
        .content = [](Button& it) {
            it.text() = L"Button2";
            it.onClicked.connect([&it] {
                std::cout << "Button2 clicked" << std::endl;
                it.setZIndex(it.getZIndex() + 1);
                auto obj = BLOCK("Button1");
                std::cout << "Button1 z-index: " << dynamic_cast<Button*>(obj)->getZIndex() << std::endl;
                std::cout << "Button2 z-index: " << it.getZIndex() << std::endl;
            });
        }
    };
    it.addItem(BLOCK("Button2"), 2.f);
}

void WindowContent(Block& it) {
    XRowLayout{
        .name = "RowLayout",
        .rect = iRect{50,50,200,100},
        .parent = it,
        .content = RowLayoutContent,
    };
}

void RootWindow() {
    XMainWindow{
        .name = "Root",
        .title = L"Test Window",
        .rect = iRect{50,50,800,600},
        .content = WindowContent,
    };
}

int main() {
    RootWindow();

    auto& UIManager = DeclarativeUIManager::getInstance();
    Block* root = UIManager.findBlock("Root");
    Window* window = Window::createWindow(root);
    Application app{ window };
    window->show();
    return app.run();
}