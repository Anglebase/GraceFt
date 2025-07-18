#include <GraceFt/GridLayout.h>
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/widget/Button.h>

using namespace GFt;
using namespace GFt::literals;
using namespace GFt::Widget;

int main() {
    Block root = Block(iRect{ 50,50,800,600 });
    GridLayout layout{
        iRect{50,50,700,500},
        &root,
    };
    layout.setGridSize(3);
    Button btn1{ L"Btn1",iRect{},&layout };
    Button btn2{ L"Btn2",iRect{},&layout };
    Button btn3{ L"Btn3",iRect{},&layout };
    Button btn4{ L"Btn4",iRect{},&layout };
    Button btn5{ L"Btn5",iRect{},&layout };

    layout.addItem(&btn1, iRect{ 0,0,2,1 });
    layout.addItem(&btn2, iRect{ 0,1,1,2 });
    layout.addItem(&btn3, iRect{ 1,1,1,1 });
    layout.addItem(&btn4, iRect{ 2,0,1,2 });
    layout.addItem(&btn5, iRect{ 1,2,2,1 });
    layout.setSpace(5);
    layout.setPadding(5);

    btn1.onClicked.connect([]() { std::cout << "Btn1 clicked" << std::endl; });
    btn2.onClicked.connect([]() { std::cout << "Btn2 clicked" << std::endl; });
    btn3.onClicked.connect([]() { std::cout << "Btn3 clicked" << std::endl; });
    btn4.onClicked.connect([]() { std::cout << "Btn4 clicked" << std::endl; });
    btn5.onClicked.connect([]() { std::cout << "Btn5 clicked" << std::endl; });

    Window* window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}