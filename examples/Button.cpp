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
    TextSet textSet_;
    BrushSet brushSet_;
protected:
    // 重写 onDraw() 方法，绘制按钮
    void onDraw(const iRect& rect) override {
        iRect r = iRect{ iPoint(), rect.size() };
        Graphics g;
        g.bindBrushSet(&brushSet_);
        g.bindTextSet(&textSet_);
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
        brushSet_(0x9898efee_rgba), textSet_(0_rgb, Font(L"仿宋", 1_em)) {}
    // 定义一系列调控函数
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
    Button* buttonClose_;
    Button* buttonExit_;
public:
    // 构造函数
    MainWindow(const iRect& rect) : Block(rect) {
        // 创建四个按钮控件
        buttonOK_ = new Button(L"确认", iRect{ 10_px, 10_px, 200_px, 60_px }, this);
        buttonCancel_ = new Button(L"取消", iRect{ 10_px, 90_px, 200_px, 60_px }, this);
        buttonClose_ = new Button(L"关闭", iRect{ 10_px, 170_px, 200_px, 60_px }, this);
        buttonExit_ = new Button(L"退出", iRect{ 10_px, 250_px, 200_px, 60_px }, this);
        // 设置按钮的样式
        buttonCancel_->textSet().font().setFontFamily(L"楷体");
        buttonOK_->textSet().font().setFontFamily(L"宋体");
        buttonClose_->textSet().font().setFontFamily(L"黑体");
        buttonExit_->brushSet().setFillStyle(0xff7777ff_rgba);
        buttonCancel_->textSet().font().setSize(2_em);
        buttonOK_->textSet().font().setSize(2_em);
        buttonClose_->textSet().font().setSize(2_em);
        buttonExit_->textSet().font().setSize(2_em);
        // 绑定槽函数
        buttonOK_->onClicked.connect([] { std::cout << "OK clicked" << std::endl; });
        buttonCancel_->onClicked.connect([] { std::cout << "Cancel clicked" << std::endl; });
        buttonClose_->onClicked.connect([] { std::cout << "Close clicked" << std::endl; });
        buttonExit_->onClicked.connect([] { std::cout << "Exit clicked" << std::endl; });

        buttonOK_->HoverOn.connect([](Block*) { std::cout << "OK hover on" << std::endl; });
        buttonCancel_->HoverOn.connect([](Block*) { std::cout << "Cancel hover on" << std::endl; });
        buttonClose_->HoverOn.connect([](Block*) { std::cout << "Close hover on" << std::endl; });
        buttonExit_->HoverOn.connect([](Block*) { std::cout << "Exit hover on" << std::endl; });
        buttonOK_->HoverOff.connect([](Block*) { std::cout << "OK hover off" << std::endl; });
        buttonCancel_->HoverOff.connect([](Block*) { std::cout << "Cancel hover off" << std::endl; });
        buttonClose_->HoverOff.connect([](Block*) { std::cout << "Close hover off" << std::endl; });
        buttonExit_->HoverOff.connect([](Block*) { std::cout << "Exit hover off" << std::endl; });
    }
    // 析构函数
    ~MainWindow() {
        delete buttonOK_;
        delete buttonCancel_;
        delete buttonClose_;
        delete buttonExit_;
    }
};

int main() {
    // 创建根节点
    MainWindow window(iRect{ 100_px, 100_px, 220_px, 320_px });
    // 创建窗口
    Window* w = Window::createWindow(&window);
    // 构造应用
    Application app(w);
    // 显示窗口
    w->show();
    // 运行应用
    return app.exec();
}