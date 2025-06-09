#include <GraceFt/widget/UI.h>
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>

using namespace GFt;
using namespace GFt::UI;
using namespace GFt::Widget;

int main() {
    XMainWindow{
        .name = "MainWindow",
        .title = L"Grace UI Test",
        .rect = iRect{0, 0, 800, 600},
        .content = [](MainWindow& it) {
            XGridLayout{
                .name = "MainLayout",
                .rect = iRect{0, 0, 800, 600},
                .parent = it,
                .content = [](GridLayout& it) {
                    Window::onWindowSizeChanged.connect([&it](Window* w) {
                        it.setSize(w->rect().size());
                    });
                    it.setGridSize(3,3);
                    it.setPadding(20);
                    it.setSpace(10);
                    XButton{
                        .name = "Button1",
                        .parent = it,
                        .content = [](Button& it) {
                            it.text() = L"Button1";
                            it.onClicked.connect([] {
                                std::cout << "Button1 clicked" << std::endl;
                            });
                        }
                    };
                    it.addItem(BLOCK("Button1"),iRect{0,0,1,2});
                    XButton{
                        .name = "Button2",
                        .parent = it,
                        .content = [](Button& it) {
                            it.text() = L"Button2";
                            it.onClicked.connect([] {
                                std::cout << "Button2 clicked" << std::endl;
                            });
                        }
                    };
                    it.addItem(BLOCK("Button2"),iRect{1,0,1,2});
                    XButton{
                        .name = "Button3",
                        .parent = it,
                        .content = [](Button& it) {
                            it.text() = L"Button3";
                            it.onClicked.connect([] {
                                std::cout << "Button3 clicked" << std::endl;
                            });
                        }
                    };
                    it.addItem(BLOCK("Button3"),iRect{2,0,1,2});
                    XHSlider{
                        .name = "Slider1",
                        .parent = it,
                        .content = [](HSlider& it) {
                            it.setRange(0, 100, 0.6f);
                            it.setValue(50);
                            it.onValueChanged.connect([](float value) {
                                std::cout << "Slider1 value changed to " << value << std::endl;
                            });
                        }
                    };
                    it.addItem(BLOCK("Slider1"),iRect{0,2,3,1});
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK("MainWindow"));
    Application app{ window };
    window->show();
    return app.run();
}