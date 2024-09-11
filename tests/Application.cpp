#include <Application.h>
#include <Graphics.h>

using namespace GFt;
using namespace std;

class MyWindow : public Block {
protected:
    void onDraw(const iRect& rect) override {
        Block::onDraw(rect);
        Graphics g;
        g.setBackgroundColor(0xe9e9e9_rgb);
        g.clear();
        g.drawFillRect(fRect{ 20,20,100,100 });
    }
    void onMouseMove(const MouseMoveEvent& event) override {
        cout << "Mouse moved to " << event.position() << endl;
    }
public:
    MyWindow(iRect rect) : Block(rect) {}
};

int main() {
    Window* window = Window::createWindow(iRect{ 50,50,800,600 });
    MyWindow* myWindow = new MyWindow(iRect{ 100,100,200,200 });
    window->addChild(myWindow);
    Application app(window);
    return app.exec();
}