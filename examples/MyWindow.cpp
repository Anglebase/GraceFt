#include <GraceFt/Application.h>
#include <GraceFt/Graphics.h>
#include <GraceFt/Window.h>

/**
 * @example MyWindow.cpp
 *
 * 这是一个自定义窗口内容的示例，展示了如何使用扩展 GFt::Block 类来实现自定义窗口内容，
 * 通过继承 GFt::Block 类，我们可以自定义自己的窗口内容，并通过重写 GFt::Block::onDraw() 方法来绘制窗口内容，
 * 同时， GFt::Block 类也有其它的虚函数，我们可以重写这些虚函数来实现更多的功能。
 *
 * 通过 GFt::Graphics 类，我们可以绘制各种图形，包括矩形、圆形、椭圆、多边形、线段、文本等。
 * 通过 GFt::BrushSet 类，我们可以设置画刷，包括颜色、线宽、样式等。
 * 通过 GFt::TextSet 类，我们可以设置文本的字体、大小、颜色等。
 */

using namespace GFt;
using namespace GFt::literals;

class MyWidget : public Block {
protected:
    void onDraw(const iRect& rect) override {
        static Graphics g;
        static BrushSet brush(0xce00dfaf_rgba);
        iRect r{ iPoint{0,0}, rect.size() };
        g.bindBrushSet(&brush);
        g.drawFillRect(r);
    }
    void onMouseButtonPress(const MouseButtonPressEvent& event) override {
        std::cout << "MyWidget MouseButtonPress: " << event.position() << std::endl;
        Block::onMouseButtonPress(event);
    }
    void onTextInput(const TextInputEvent& event) override {
        event.accept();
    }
public:
    MyWidget(const iRect& rect, Block* parent = nullptr, int zIndex = 0) : Block(rect, parent, zIndex) {}
};

class MyWindow : public Block {
    std::wstring text_;
    MyWidget* widget_;
protected:
    // 重写onDraw()方法，绘制窗口内容
    void onDraw(const iRect& rect) override {
        static Graphics g;                                         // 此函数会被频繁调用，因而
        static BrushSet brush(0xC9C9E69F_rgba);                    // 应该将这些量声明为静态变
        static BrushSet brush2(0xB9EFF68A_rgba);                   // 量或成员变量，以降低频繁
        static TextSet text(0x0_rgb, Font{ L"Consolas", 1.5_em });   // 创建和销毁这些对象的开销
        g.bindBrushSet(&brush);
        g.bindTextSet(&text);
        g.drawFillRect(fRect{ 10,10,200,100 });
        g.drawText(L"This is MyWindow in GraceFt!", fPoint{ 30,40 });
        g.drawText(text_, fPoint{ 30,70 }, { L"Consolas", L"仿宋", L"Segoe UI Emoji" });
        g.bindBrushSet(&brush2);
        g.drawFillRect(fRect{ 50,60,200,100 });
        // 调用父类的onDraw()方法，以执行默认的窗口内容绘制
        Block::onDraw(rect);  // 此函数无默认行为，仅作示例
    }
    void onMouseButtonPress(const MouseButtonPressEvent& event) override {
        std::cout << "MyWindow MouseButtonPress: " << event.position() << std::endl;
        std::cout << "Pos: " << this->absolutePos() << std::endl;
        std::cout << event.position() << std::endl;
        std::cout << event.absolutePosition() << std::endl;
        return Block::onMouseButtonPress(event);
    }
    void onTextInput(const TextInputEvent& event) override {
        switch ((wchar_t)event.character()) {
        case L'\r':
        case L'\n':
            text_.clear();
            break;
        case L'\b':
            if (!text_.empty())
                text_.pop_back();
            break;
        case L'\t':
            text_ += L"    ";
            break;
        default:
            text_ += event.character();
            break;
        }
        std::cout << "TextInput" << std::endl;
    }
public:
    MyWindow(const iRect& rect, Block* parent = nullptr, int zIndex = 0) : Block(rect, parent, zIndex) {
        widget_ = new MyWidget(iRect{ 90,90,200,100 }, this, 1); // 创建自定义窗口内容
    }
    ~MyWindow() {
        delete widget_;
    }
};

int main() {
    MyWindow root(iRect{ 25_sw,20_sh,50_sw,50_sh });          // 创建根节点
    auto window = Window::createWindow(&root); // 创建窗口
    Application app{ window };                                // 构造应用对象
    window->show();                                           // 显示窗口
    return app.exec();                                        // 启动事件循环
}