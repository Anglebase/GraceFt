#include <UI.h>
#include <Application.h>

using namespace GFt::UI;
using namespace GFt;
using namespace GFt::Widget;

void RootWindow(){
    XWindow{
        .name = "Root",
        .rect = iRect{50,50,800,600},
        .content = [](Block& it) {
            XButton{
                .name = DNAME(Button1),
                .text = L"Hello,world!",
                .rect = iRect{100,100,100,100},
                .parent = it,
                .content = [](Button& it) {
                    it.onClicked.connect([&it] {
                        std::cout << "Button1 clicked" << std::endl;
                        it.setZIndex(it.getZIndex() + 1);
                        auto obj = BLOCK(Button2);
                        std::cout << "Button2 z-index: " << dynamic_cast<Button*>(obj)->getZIndex() << std::endl;
                        std::cout << "Button1 z-index: " << it.getZIndex() << std::endl;
                    });
                }
            };
            XButton{
                .name = DNAME(Button2),
                .text = L"Button2",
                .rect = iRect{150,150,100,100},
                .parent = it,
                .content = [](Button& it) {
                    it.onClicked.connect([&it] {
                        std::cout << "Button2 clicked" << std::endl;
                        it.setZIndex(it.getZIndex() + 1);
                        auto obj = BLOCK(Button1);
                        std::cout << "Button1 z-index: " << dynamic_cast<Button*>(obj)->getZIndex() << std::endl;
                        std::cout << "Button2 z-index: " << it.getZIndex() << std::endl;
                    });
                }
            };
        }
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