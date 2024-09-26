#include <RowLayout.h>
#include <Application.h>
#include <Window.h>
#include <Button.h>
#include <thread>

using namespace GFt;
using namespace GFt::literals;
using namespace GFt::Widget;

int main() {
    Block root = Block(iRect{ 50,50,800,600 });

    Button btn{ L"Btn",iRect{ 50,400,100,50 },&root };
    RowLayout layout{
        iRect{50,50,700,300},
        &root,
    };
    Button btn1{ L"Btn1",iRect{0,0,50,0},&layout };
    Button btn2{ L"Btn2",iRect{0,0,50,0},&layout };
    Button btn3{ L"Btn3",iRect{0,0,50,0},&layout };
    Button btn4{ L"Btn4",iRect{0,0,50,0},&layout };

    layout.addItem(&btn1, 1);
    layout.addItem(&btn2, Layout::Fixed);
    layout.addItem(&btn3, 3);
    layout.addItem(&btn4, 4);
    layout.addItem(&btn4, 1);
    layout.addItem(&btn3, 1);

    layout.setSpace(10);
    layout.setPadding(5, 20);

    btn1.onClicked.connect([]() { std::cout << "Btn1 clicked" << std::endl; });
    btn2.onClicked.connect([&]() {
        std::cout << "Btn2 clicked" << std::endl;
        btn1.hide();
        });
    btn3.onClicked.connect([&]() {
        std::cout << "Btn3 clicked" << std::endl;
        btn1.show();
        });
    btn4.onClicked.connect([&]() {
        std::cout << "Btn4 clicked" << std::endl;
        layout.hide();
        });
    btn.onClicked.connect([&]() {
        std::cout << "Btn clicked" << std::endl;
        layout.show();
        });

    Window* window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}