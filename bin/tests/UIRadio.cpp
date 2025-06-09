#include <GraceFt/widget/UI.h>
#include <GraceFt/Application.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::UI;

int main() {
    XMainWindow{
        .name = "Root",
        .title = L"UI Radio Test",
        .rect = iRect{100, 100, 800, 600},
        .content = [](MainWindow& it) {
            XColumnLayout{
                .name = "ColumnLayout",
                .rect = iRect{0, 0, 800, 600},
                .parent = it,
                .content = [](ColumnLayout& it) {
                    Window::onWindowCreated.connect(
                        [&it](Window* w) {
                            w->onSizeChanged.connect(&it, &ColumnLayout::setSize);
                        }
                    );
                    static RadioManager manager;
                    XRadioBox{
                        .name = "RadioBox1",
                        .radioManager = manager,
                        .parent = it,
                        .content = [](RadioBox& it) {
                            it.text() = L"RadioBox1";
                        }
                    };
                    it.addItem(BLOCK("RadioBox1"));
                    XRadioBox{
                        .name = "RadioBox2",
                        .radioManager = manager,
                        .parent = it,
                        .content = [](RadioBox& it) {
                            it.text() = L"RadioBox2";
                        }
                    };
                    it.addItem(BLOCK("RadioBox2"));
                    XRadioBox{
                        .name = "RadioBox3",
                        .radioManager = manager,
                        .parent = it,
                        .content = [](RadioBox& it) {
                            it.text() = L"RadioBox3";
                        }
                    };
                    it.addItem(BLOCK("RadioBox3"));
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK("Root"));
    Application app{ window };
    window->show();
    return app.run();
}