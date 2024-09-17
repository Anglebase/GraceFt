#include <UI.h>
#include <Application.h>

using namespace GFt::UI;
using namespace GFt;
using namespace GFt::Widget;

int main() {
    XWindow{
        .name = "Root",
        .rect = iRect{50,50,800,600},
        .content = [](Block& it) {
            XLabel{
                .name = "Label1",
                .text = L"Hello,world!",
                .rect = iRect{100,100,100,50},
                .parent = it,
            };
            XButton{
                .name = "Button2",
                .rect = iRect{100,150,100,50},
                .parent = it,
                .content = [](Button& it) {
                    it.text() = L"Button2";
                    it.onClicked.connect([] {std::cout << "Button2 clicked" << std::endl;});
                }
            };
        }
    };

    auto& UIManager = DeclarativeUIManager::getInstance();
    Block* root = UIManager.findBlock("Root");
    Window* window = Window::createWindow(root);
    Application app{ window };
    window->show();
    return app.run();
}