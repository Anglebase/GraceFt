#include "Window.h"

#include <Tools.h>
#include <ege.h>

#define H(hide) (hide? ege::INIT_HIDE : 0)

namespace GFt {
    Signal<Window*> Window::onWindowCreated;
    Signal<Window*> Window::onWindowDestroyed;
    Signal<Window*> Window::onWindowResized;
    Signal<Window*> Window::onWindowMoved;
    Signal<Window*> Window::onWindowMinimized;
    Signal<Window*> Window::onWindowMaximized;
    Signal<Window*> Window::onWindowRestored;

    using namespace ege;
    using namespace literals;
    Window* Window::pInstance_ = nullptr;
    Window::Window(int width, int height, int flags)
        : Block(iRect(0, 0, width, height)), store_(width, height) {
        initgraph(width, height, flags | INIT_UNICODE | INIT_ANIMATION | INIT_NOFORCEEXIT | INIT_HIDE);
        setcaption(L"GraceFt v2.0.0");
        setbkcolor(WHITE);
        setcolor(BLACK);
        setfillcolor(EGERGBA(195, 198, 220, 230));
        cleardevice();
        Window::onWindowCreated(this);
    }
    Window::~Window() {
        closegraph();
        Window::onWindowDestroyed(this);
    }
    void Window::show() { showwindow(); }
    void Window::hide() { hidewindow(); }
    void Window::resize(const iSize& size) {
        resizewindow(size.width(), size.height());
        this->rect().size() = size;
        if (root_)
            root_->rect().size() = size;
        onWindowResized(this);
    }
    void Window::move(const iPoint& dpos) {
        RECT rect;
        ::GetWindowRect(getHWnd(), &rect);
        movewindow(dpos.x() + rect.left, dpos.y() + rect.top);
        onWindowMoved(this);
    }
    void Window::moveTo(const iPoint& pos) {
        movewindow(pos.x(), pos.y());
        onWindowMoved(this);
    }
    void Window::setTitle(const std::wstring& title) { setcaption(title.c_str()); }
    void Window::setTopMost(bool topMost) {
        if (isMaximized_)
            return;
        ::SetWindowPos(getHWnd(), topMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        isTopMost_ = topMost;
    }
    void Window::setFrameless(bool frameless) {
        if (isMaximized_)
            return;
        auto style = ::GetWindowLong(getHWnd(), GWL_STYLE);
        frameless ? style &= ~WS_CAPTION : style |= WS_CAPTION;
        ::SetWindowLong(getHWnd(), GWL_STYLE, style);
        isFrameless_ = frameless;
    }
    void Window::setAlpha(float alpha) {
        auto style = ::GetWindowLong(getHWnd(), GWL_EXSTYLE);
        if (alpha >= 1.0f)
            style &= ~WS_EX_LAYERED;
        else
            style |= WS_EX_LAYERED;
        ::SetWindowLong(getHWnd(), GWL_EXSTYLE, style);
        ::SetLayeredWindowAttributes(getHWnd(), 0, alpha * 255, LWA_ALPHA);
    }
    void Window::minimize() {
        RECT rect;
        GetWindowRect(getHWnd(), &rect);
        pos_ = iPoint{ rect.left, rect.top };
        ::ShowWindow(getHWnd(), SW_MINIMIZE);
        isMinimized_ = true;
        isMaximized_ = false;
        onWindowMinimized(this);
    }
    void Window::maximize() {
        RECT rect;
        GetWindowRect(getHWnd(), &rect);
        pos_ = iPoint{ rect.left, rect.top };
        this->moveTo(iPoint{ 0,0 });
        this->resize(iSize{ 100_sw, 100_sh });
        bool t = isTopMost_, f = isFrameless_;
        this->setTopMost(true);
        this->setFrameless(true);
        isTopMost_ = t, isFrameless_ = f;
        isMinimized_ = false;
        isMaximized_ = true;
        onWindowMaximized(this);
    }
    void Window::restore() {
        if (!isMinimized_ && !isMaximized_)
            return;
        this->resize(store_);
        this->moveTo(pos_);
        if (isMaximized_) {
            isMaximized_ = false;
            this->setTopMost(isTopMost_);
            this->setFrameless(isFrameless_);
            std::cout << "Restored" << std::boolalpha << isTopMost_ << " " << isFrameless_ << std::endl;
        }
        isMinimized_ = false;
        isMaximized_ = false;
        onWindowRestored(this);
    }
    Window* Window::createWindow(Block* block, bool hide) {
        if (!block) return nullptr;
        if (Window::pInstance_)
            return Window::pInstance_;
        auto rect = block->rect();
        static Window window(rect.width(), rect.height(), H(hide));
        window.addChild(block);
        movewindow(rect.x(), rect.y());
        flushwindow();
        block->rect().position() = iPoint();
        Window::pInstance_ = &window;
        window.root_ = block;
        return Window::pInstance_;
    }
    Window* Window::createFullScreenWindow(Block* block, bool hide) {
        if (!block) return nullptr;
        if (Window::pInstance_)
            return Window::pInstance_;
        block->rect() = iRect{ 0,0,100_sw,100_sh };
        static Window window(100_sw, 100_sh, H(hide) | INIT_NOBORDER | INIT_TOPMOST);
        window.addChild(block);
        movewindow(0, 0);
        flushwindow();
        block->rect().position() = iPoint();
        Window::pInstance_ = &window;
        window.root_ = block;
        return Window::pInstance_;
    }
    Window* Window::createTopMostWindow(Block* block, bool hide) {
        if (!block) return nullptr;
        if (Window::pInstance_)
            return Window::pInstance_;
        auto rect = block->rect();
        static Window window(rect.width(), rect.height(), H(hide) | INIT_TOPMOST);
        window.addChild(block);
        movewindow(rect.x(), rect.y());
        flushwindow();
        block->rect().position() = iPoint();
        Window::pInstance_ = &window;
        window.root_ = block;
        return Window::pInstance_;
    }
    Window* Window::createNoBorderWindow(Block* block, bool hide) {
        if (!block) return nullptr;
        if (Window::pInstance_)
            return Window::pInstance_;
        auto rect = block->rect();
        static Window window(rect.width(), rect.height(), H(hide) | INIT_NOBORDER);
        window.addChild(block);
        movewindow(rect.x(), rect.y());
        flushwindow();
        block->rect().position() = iPoint();
        Window::pInstance_ = &window;
        window.root_ = block;
        return Window::pInstance_;
    }
    Window* Window::createNoBorderTopMostWindow(Block* block, bool hide) {
        if (!block) return nullptr;
        if (Window::pInstance_)
            return Window::pInstance_;
        auto rect = block->rect();
        static Window window(rect.width(), rect.height(), H(hide) | INIT_NOBORDER | INIT_TOPMOST);
        window.addChild(block);
        movewindow(rect.x(), rect.y());
        flushwindow();
        block->rect().position() = iPoint();
        Window::pInstance_ = &window;
        window.root_ = block;
        return Window::pInstance_;
    }
    Window* Window::window() {
        return Window::pInstance_;
    }
}