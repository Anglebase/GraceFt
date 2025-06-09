#include <GraceFt/ColumnLayout.h>
#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/widget/Button.h>

using namespace GFt;
using namespace GFt::literals;
using namespace GFt::Widget;

int main() {
    Block root = Block(iRect{ 50,50,800,600 });
    ColumnLayout layout{
        iRect{50,50,700,300},
        &root,
    };
    Button btn1{ L"Btn1",iRect{},&layout };
    Button btn2{ L"Btn2",iRect{},&layout };
    Button btn3{ L"Btn3",iRect{},&layout };
    Button btn4{ L"Btn4",iRect{},&layout };

    layout.addItem(&btn1);
    layout.addItem(&btn2, 2.f);
    layout.addItem(&btn3);
    layout.addItem(&btn4, 1.5f);
    layout.setSpace(10);
    layout.setPadding(5, 20);

    btn1.onClicked.connect([]() { std::cout << "Btn1 clicked" << std::endl; });
    btn2.onClicked.connect([]() { std::cout << "Btn2 clicked" << std::endl; });
    btn3.onClicked.connect([]() { std::cout << "Btn3 clicked" << std::endl; });
    btn4.onClicked.connect([]() { std::cout << "Btn4 clicked" << std::endl; });

    Window* window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}