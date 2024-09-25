#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/UI.h>

using namespace GFt;
using namespace GFt::UI;
using namespace GFt::Widget;
using namespace GFt::literals;

int main() {
    XMainWindow{
        // 主窗口
        .name = "AppWindow",
        .title = L"计算器",
        .rect = iRect{ 50, 50, 600, 800 },
        .content = [](MainWindow& it) {
            // 窗口布局
            XColumnLayout{
                .name = "WindowLayout",
                .rect = iRect{ it.rect().size() },
                .parent = it,
                .content = [](ColumnLayout& it) {
                    // 基本属性配置
                    it.setTopPadding(2_em);
                    Window::onWindowSizeChanged.connect([&it](Window* w) {
                        it.setSize(iSize{100_vw, 100_vh});
                    });
                    XLabel {
                        .name = "exprLabel",
                        .parent = it,
                        .content = [](Label& it) {
                            it.text() = L"123";
                            it.textSet().font().setSize(5_em);
                            it.textSet().font().setWeight(FontWeight::Bold);
                            it.textSet().font().setFontFamily(L"等线");
                        }
                    };
                    XGridLayout {
                        .name = "btns",
                        .parent = it,
                        .content = [](GridLayout& it) {
                            it.setGridSize(4,4);
                            it.setPadding(1_em);
                            it.setSpace(0.5_em);
                            XButton {
                                .name = "+",
                                .parent = it,
                                .content = [](Button& it) {
                                    it.textSet().font().setSize(2_em);
                                    it.textSet().font().setWeight(FontWeight::Bold);
                                    it.textSet().font().setFontFamily(L"等线");
                                    it.text() = L"+";
                                }
                            };
                            it.addItem(BLOCK(+), iRect{3,0,1,1});
                            XButton {
                                .name = "-",
                                .parent = it,
                                .content = [](Button& it) {
                                    it.textSet().font().setSize(2_em);
                                    it.textSet().font().setWeight(FontWeight::Bold);
                                    it.textSet().font().setFontFamily(L"等线");
                                    it.text() = L"-";
                                }
                            };
                            it.addItem(BLOCK(-), iRect{3,1,1,1});
                            XButton {
                                .name = "*",
                                .parent = it,
                                .content = [](Button& it) {
                                    it.textSet().font().setSize(2_em);
                                    it.textSet().font().setWeight(FontWeight::Bold);
                                    it.textSet().font().setFontFamily(L"等线");
                                    it.text() = L"*";
                                }
                            };
                            it.addItem(BLOCK(*), iRect{3,2,1,1});
                            XButton {
                                .name = "/",
                                .parent = it,
                                .content = [](Button& it) {
                                    it.textSet().font().setSize(2_em);
                                    it.textSet().font().setWeight(FontWeight::Bold);
                                    it.textSet().font().setFontFamily(L"等线");
                                    it.text() = L"/";
                                }
                            };
                            it.addItem(BLOCK(/ ), iRect{3,3,1,1});
                            XButton {
                                .name = "C",
                                .parent = it,
                                .content = [](Button& it) {
                                    it.textSet().font().setSize(2_em);
                                    it.textSet().font().setWeight(FontWeight::Bold);
                                    it.textSet().font().setFontFamily(L"等线");
                                    it.text() = L"C";
                                }
                            };
                            it.addItem(BLOCK(C), iRect{0,3,1,1});
                        }
                    };
                    it.addItem(BLOCK(exprLabel), 0.5);
                    it.addItem(BLOCK(btns), 2.5);
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK(AppWindow));
    Application app(window);
    window->show();
    return app.run();
}