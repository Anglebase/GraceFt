#include <GraceFt/UI.h>
#include <GraceFt/Application.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::UI;

int main() {
    XMainWindow{
        .name = "Root",
        .title = L"UI Check Test",
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
                    XCheckBox{
                        .name = "CheckBox1",
                        .parent = it,
                        .content = [](CheckBox& it) {
                            it.text() = L"CheckBox1";
                        }
                    };
                    it.addItem(BLOCK("CheckBox1"));
                    XCheckBox{
                        .name = "CheckBox2",
                        .parent = it,
                        .content = [](CheckBox& it) {
                            it.text() = L"CheckBox2";
                        }
                    };
                    it.addItem(BLOCK("CheckBox2"));
                    XCheckBox{
                        .name = "CheckBox3",
                        .parent = it,
                        .content = [](CheckBox& it) {
                            it.text() = L"CheckBox3";
                        }
                    };
                    it.addItem(BLOCK("CheckBox3"));
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK("Root"));
    Application app{ window };
    window->show();
    return app.run();
}