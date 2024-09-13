#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/Graphics.h>
#include <Signal.hpp>

/**
 * @example Button.cpp
 *
 * 这是一个Button的简单实现示例，展示如何通过GraceFt库创建控件
 */

using namespace GFt;
using namespace GFt::literals;

class Button : public Block {
    std::wstring content_;
    PenSet penSet_;
    TextSet textSet_;
    BrushSet brushSet_;
protected:
    void onDraw(const iRect& rect) override {
        iRect r = iRect{ iPoint(), rect.size() };
        Graphics g;
        g.bindPenSet(&penSet_);
        g.bindBrushSet(&brushSet_);
        g.bindTextSet(&textSet_);
        g.drawRect(r);
        g.drawFillRect(r);
        g.drawText(content_, r, TextAlign::Center | TextAlign::Middle);
    }
    void onMouseButtonPress(const MouseButtonPressEvent& event) {
        if (event.button() == MouseButton::Left)
            onClicked();
        return Block::onMouseButtonPress(event);
    }
public:
    Button(const std::wstring& content, const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex), content_(content),
        penSet_(0_rgb), brushSet_(0x9898efee_rgba), textSet_(0_rgb, Font(L"仿宋", 1_em)) {}
    PenSet& penSet() { return penSet_; }
    BrushSet& brushSet() { return brushSet_; }
    TextSet& textSet() { return textSet_; }
    void setContent(const std::wstring& content) { content_ = content; }
    const std::wstring& content() const { return content_; }
public:
    Signal<void> onClicked;
};

class MainWindow : public Block {
    Button* buttonOK_;
    Button* buttonCancel_;
public:
    MainWindow(const iRect& rect) : Block(rect) {
        buttonOK_ = new Button(L"确认", iRect{ 10_px, 10_px, 100_px, 30_px }, this);
        buttonCancel_ = new Button(L"取消", iRect{ 10_px, 50_px, 100_px, 30_px }, this);
        buttonOK_->onClicked.connect([this]() {
            std::wcout << L"OK clicked" << std::endl;
            });
        buttonCancel_->onClicked.connect([this]() {
            std::wcout << L"Cancel clicked" << std::endl;
            });
    }
    ~MainWindow() {
        delete buttonOK_;
        delete buttonCancel_;
    }
};

int main() {
    MainWindow window(iRect{ 100_px, 100_px, 640_px, 480_px });
    Window* w = Window::createWindow(&window);
    Application app(w);
    w->show();
    return app.exec();
}