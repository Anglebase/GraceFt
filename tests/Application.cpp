#include <Application.h>
#include <Graphics.h>
#include <chrono>
#include <string>

using namespace GFt;
using namespace std;

class MyWindow : public Block {
protected:
    void onDraw(const iRect& rect) override {
        using namespace GFt::literals;
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
        g.drawText(std::to_wstring(Application::getRealFps()), fPoint());
        cout << "FPS: " << Application::getRealFps() << endl;
    }
    void onMouseMove(const MouseMoveEvent& event) override {
        cout << "Mouse moved to " << event.position() << endl;
    }
public:
    MyWindow(iRect rect) : Block(rect) {}
};

int main() {
    MyWindow* myWindow = new MyWindow(iRect{ 0,0,800,600 });
    Window* window = Window::createWindow(myWindow);
    Application app(window);
    Application::setFps(60);
    return app.exec();
}