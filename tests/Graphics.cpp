#include <Application.h>
#include <Graphics.h>
#include <Window.h>
#include <Tools.h>
#include <LMath.hpp>

using namespace GFt::literals;
using namespace GFt;

class MyWindow : public Block {
    PixelMap pixmap;
protected:
    void onDraw(const iRect& rect) override {
        static Graphics g;
        BrushSet bs(0x9f9fefcd_rgba);
        g.setTransform(
            rotate((fVec2)fPoint(50.f, 50.f), radians(45.0f))
            * scale((fVec2)fPoint(50.f, 50.f), makefVec2(0.5f, 0.5f))
            * translate((fVec2)fPoint(100.f, 100.f))
            );
        g.drawImage(iPoint(50, 50), pixmap);
    }
public:
    MyWindow(const iRect& rect, Block* parent = nullptr, int zIndex = 0) : Block(rect, parent, zIndex) {
        pixmap = PixelMap::loadFromFile(LR"(C:\Users\Lenovo\Project\.Github\GraceFt_\wall.jpg)");
    }
};

int main() {
    MyWindow root(iRect(25_sw, 20_sh, 40_sw, 50_sh));
    auto window = Window::createWindow(&root);
    Application app(window);
    window->show();
    return app.exec();
}