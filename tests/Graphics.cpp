#include <Application.h>
#include <Graphics.h>
#include <Window.h>
#include <Tools.h>
#include <LMath.hpp>

using namespace GFt::literals;
using namespace GFt;

class MyWindow : public Block {
    PixelMap pixmap;
    Texture texture;
protected:
    void onDraw(Graphics& g) override {
        BrushSet bs(0x9f9fefcd_rgba);
        // bs.setTexture(texture, iRect(0, 0, 100, 100));
        // bs.setLinearGradient(iPoint{ 50,50 }, 0xff00_rgb, iPoint{ 150,150 }, 0xff_rgb);
        // bs.setRadialGradient(iPoint{ 150,150 }, 0xff00_rgb, iRect{ 50,50,200,200 }, 0xff_rgb);
        bs.setPolygonGradient(iPoint{ 125,125 }, 0xffff_rgb,
            std::vector<fPoint>{ iPoint{ 50,50 }, iPoint{ 50,200 }, iPoint{ 200,200 }, iPoint{ 200,50 } },
            std::vector<Color> { 0xff0000_rgb, 0xff00_rgb, 0xff_rgb, 0xff00ff_rgb });
        g.bindBrushSet(&bs);
        g.setAntiAliasing(true);
        Path path;
        path.addText(L"Hello, world!", iPoint{ 0,0 }, Font{ L"宋体", 4_em });
        // g.setTransform(
        //     rotate((fVec2)fPoint(0, 0), radians(180.0f))
        //     * translate((fVec2)fPoint(100, 100))
        // );
        // g.drawFillRect(iRect(50, 50, 200, 200));
        // g.drawFillRect(iRect(iPoint{0,0}, rect.size()));
        g.drawFillPath(path, iPoint{ 20,20 });
    }
public:
    MyWindow(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex), texture(LR"(C:\Users\Lenovo\Project\OpenGL\wall.jpg)") {
        pixmap = PixelMap::loadFromFile(LR"(C:\Users\Lenovo\Project\OpenGL\wall.jpg)");
    }
};

int main() {
    MyWindow root(iRect(25_sw, 20_sh, 40_sw, 50_sh));
    auto window = Window::createWindow(&root);
    Application app(window);
    window->show();
    window->setTopMost(true);
    return app.exec();
}