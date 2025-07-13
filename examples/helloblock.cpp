#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Block.h>

using namespace GFt;

class HelloBlock : public Block
{
protected:
    void onDraw(Graphics& g) override {
        auto r = iRect{iPoint(), rect().size()};
        g.drawText(L"Hello World!", r, TextAlign::Center|TextAlign::Middle);
    }
public:
    HelloBlock(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex) {}
};

int main()
{
    HelloBlock root{iRect{100, 100, 640, 480}};
    Window* window = Window::createWindow(&root);
    window->show();
    Application app{window};
    return app.run();
}