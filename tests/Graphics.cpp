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
        TextSet textSet(0x0_rgb, Font{ L"JetBrains Mono", 1.6_em });
        g.bindTextSet(&textSet);
        PenSet penSet(0x4fd53cef_rgba, 30_px);
        iPolygon poly1;
        poly1.setClosed(false);
        poly1.addPoint(iPoint(10_vw, 30_vh));
        poly1.addPoint(iPoint(30_vw, 50_vh));
        poly1.addPoint(iPoint(10_vw, 70_vh));
        penSet.setCapStyle(CapStyle::Round);
        penSet.setJoinStyle(JoinStyle::Round);
        g.bindPenSet(&penSet);
        g.drawPolygon(poly1);
        g.drawText(L"CapStyle::Round", fPoint(5_vw, 72_vh));
        g.drawText(L"JoinStyle::Round", fPoint(10_vw, 52_vh));

        iPolygon poly2;
        poly2.setClosed(false);
        poly2.addPoint(iPoint(40_vw, 30_vh));
        poly2.addPoint(iPoint(60_vw, 50_vh));
        poly2.addPoint(iPoint(40_vw, 70_vh));
        penSet.setCapStyle(CapStyle::Square);
        penSet.setJoinStyle(JoinStyle::Bevel);
        g.bindPenSet(&penSet);
        g.drawPolygon(poly2);
        g.drawText(L"CapStyle::Square", fPoint(35_vw, 72_vh));
        g.drawText(L"JoinStyle::Bevel", fPoint(40_vw, 52_vh));

        iPolygon poly3;
        poly3.setClosed(false);
        poly3.addPoint(iPoint(70_vw, 30_vh));
        poly3.addPoint(iPoint(90_vw, 50_vh));
        poly3.addPoint(iPoint(70_vw, 70_vh));
        penSet.setCapStyle(CapStyle::Flat);
        penSet.setJoinStyle(JoinStyle::Miter);
        g.bindPenSet(&penSet);
        g.drawPolygon(poly3);
        g.drawText(L"CapStyle::Flat", fPoint(65_vw, 72_vh));
        g.drawText(L"JoinStyle::Miter", fPoint(70_vw, 52_vh));

        penSet.setColor(0x0_rgb);
        penSet.setLineWidth(2_px);
        penSet.setCapStyle(CapStyle::Flat);
        penSet.setJoinStyle(JoinStyle::Miter);
        g.bindPenSet(&penSet);
        g.drawLine(iLine{ iPoint{0_vw,30_vh},iPoint{100_vw,30_vh} });
        textSet.font() = Font{ L"黑体", -1.6_em };
        g.bindTextSet(&textSet);
        g.drawText(L"参考线", fPoint(87_vw, 30_vh));
    }
    void onMouseMove(MouseMoveEvent* event) override {
        // std::cout << 100_vw << ", " << 100_vh << std::endl;
        // std::cout << 40_sw << ", " << 50_sh << std::endl;
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