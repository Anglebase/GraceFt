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

// 创建控件
// 定义一个按钮类
class Button : public Block {   // 继承 Block 类
    std::wstring content_;
    PenSet penSet_;
    TextSet textSet_;
    BrushSet brushSet_;
protected:
    // 重写 onDraw() 方法，绘制按钮
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
    // 重写 onMouseButtonPress() 方法，响应鼠标点击
    void onMouseButtonPress(const MouseButtonPressEvent& event) {
        if (event.button() == MouseButton::Left)
            onClicked();
        // onMouseButtonPress() 存在默认实现(焦点捕获)
        // 若不需要捕获焦点，可以不调用父类的 onMouseButtonPress()
        return Block::onMouseButtonPress(event);
    }
public:
    // 构造函数
    Button(const std::wstring& content, const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex), content_(content),
        penSet_(0_rgb), brushSet_(0x9898efee_rgba), textSet_(0_rgb, Font(L"仿宋", 1_em)) {}
    // 定义一系列调控函数
    PenSet& penSet() { return penSet_; }
    BrushSet& brushSet() { return brushSet_; }
    TextSet& textSet() { return textSet_; }
    void setContent(const std::wstring& content) { content_ = content; }
    const std::wstring& content() const { return content_; }
public:
    // 定义 onClicked 信号，当按钮被点击时发出该信号
    Signal<void> onClicked;
};

// 使用控件
// 定义一个窗口类
class MainWindow : public Block {
    Button* buttonOK_;
    Button* buttonCancel_;
public:
    // 构造函数
    MainWindow(const iRect& rect) : Block(rect) {
        // 创建两个按钮控件
        buttonOK_ = new Button(L"确认", iRect{ 10_px, 10_px, 100_px, 30_px }, this);
        buttonCancel_ = new Button(L"取消", iRect{ 10_px, 50_px, 100_px, 30_px }, this);
        // 绑定槽函数
        buttonOK_->onClicked.connect([] { std::wcout << L"OK clicked" << std::endl; });
        buttonCancel_->onClicked.connect([] { std::wcout << L"Cancel clicked" << std::endl; });
    }
    // 析构函数
    ~MainWindow() {
        delete buttonOK_;
        delete buttonCancel_;
    }
};

int main() {
    // 创建根节点
    MainWindow window(iRect{ 100_px, 100_px, 640_px, 480_px });
    // 创建窗口
    Window* w = Window::createWindow(&window);
    // 构造应用
    Application app(w);
    // 显示窗口
    w->show();
    // 运行应用
    return app.exec();
}