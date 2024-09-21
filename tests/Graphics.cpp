#include <Application.h>
#include <Graphics.h>
#include <Window.h>
#include <Tools.h>

using namespace GFt::literals;
using namespace GFt;

class MyWindow : public Block {
protected:
    void onDraw(const iRect& rect) override {
        static Graphics g;
        BrushSet bs(0x9f9fefcd_rgba);
        auto frect = iRect{ iPoint{50,50}, rect.size() - iSize{100,100} };
        iPolygon ploy;
        g.bindBrushSet(&bs);
        ploy.addPoint(iPoint{ 100, 100 });
        ploy.addPoint(iPoint{ 100, 500 });
        ploy.addPoint(iPoint{ 400, 500 });
        ploy.addPoint(iPoint{ 500, 100 });
        g.drawFillPolygon(ploy);
    }
public:
    MyWindow(const iRect& rect, Block* parent = nullptr, int zIndex = 0) : Block(rect, parent, zIndex) {}
};

int main() {
    MyWindow root(iRect(25_sw, 20_sh, 40_sw, 50_sh));
    auto window = Window::createWindow(&root);
    Application app(window);
    window->show();
    return app.exec();
}