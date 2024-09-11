#include <Application.h>
#include <Graphics.h>
#include <chrono>

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
        auto time =
            chrono::duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()
            ).count() / 1000.0;
        g.drawLine(fLine{
            fPoint{ 50,50 },
            fPoint{ 50 + 100 * static_cast<float>(std::sin(time)),
                    50 + 100 * static_cast<float>(std::cos(time)) } });
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