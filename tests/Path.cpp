#include <Application.h>
#include <Path.h>
#include <Window.h>
#include <Block.h>
#include <Graphics.h>
#include <LMath.hpp>
#include <Button.h>
#include <Geometry.hpp>

using namespace GFt;
using namespace GFt::Widget;

class PathTest : public Block {
protected:
    void onDraw(const iRect& rect) override {
        Graphics g;
        // Path path;
        // path.addText(L"传达", iPoint(200, 200), Font(L"微软雅黑", 50));
        // path.transformBy(
        //     scale(makefVec2(200.f, 200.f), makefVec2(2.f, 2.f))
        //     * rotate(makefVec2(200.f, 200.f), radians(30.f))
        // );
        // path.addText(L"信息", iPoint(200, 200), Font(L"微软雅黑", 50));
        // g.drawCircle({ iPoint(400, 400), 30 });
        // g.drawPath(path, iPoint(0, 0));
        // g.drawLine({ iPoint{ 0,0 }, iPoint{ 300,300 } });
        // g.setTransform(
        //     scale(makefVec2(200.f, 200.f), makefVec2(2.f, 2.f))
        //     * rotate(makefVec2(200.f, 200.f), radians(135.f))
        //     * translate(makefVec2(200.f, 200.f))
        // );
        // g.drawPath(path, iPoint(0, 0));
        fLine line{ iPoint{ 0,0 }, iPoint{ 300,300 } };
        g.drawLine(line);
        g.drawCircle(iCircle{ iPoint{ 100,200 }, 5 });
        g.drawLine(centerSymmetric(line, fPoint{ 100,200 }));
    }
public:
    PathTest(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex) {}
};

int main() {
    std::cout << translate(makefVec2(200.f, 200.f)) << std::endl;
    std::cout << rotate(makefVec2(200.f, 200.f), radians(30.f)) << std::endl;
    PathTest pathTest(iRect(50, 50, 800, 600));
    Button button(L"Hello", iRect(100, 100, 200, 50), &pathTest);
    Window* window = Window::createWindow(&pathTest);
    Application app{ window };
    window->show();
    return app.run();
}