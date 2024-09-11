#include "Window.h"

#include <Tools.h>
#include <ege.h>

#define H(hide) (hide? ege::INIT_HIDE : 0)

namespace GFt {
    using namespace ege;
    using namespace literals;
    Window* Window::pInstance_ = nullptr;
    Window::Window(int width, int height, int flags)
        : Block(iRect(0, 0, width, height)) {
        initgraph(width, height, flags | INIT_UNICODE | INIT_ANIMATION | INIT_NOFORCEEXIT);
        setcaption(L"GraceFt v2.0.0");
        setbkcolor(WHITE);
        setcolor(BLACK);
        setfillcolor(EGERGBA(195, 198, 220, 230));
        cleardevice();
    }
    Window::~Window() {
        closegraph();
    }
    void Window::show() { showwindow(); }
    void Window::hide() { hidewindow(); }
    void Window::resize(const iSize& rect) { resizewindow(rect.width(), rect.height()); }
    void Window::move(const iPoint& dpos) {
        RECT rect;
        GetWindowRect(getHWnd(), &rect);
        movewindow(dpos.x() + rect.left, dpos.y() + rect.top);
    }
    void Window::moveTo(const iPoint& pos) { movewindow(pos.x(), pos.y()); }
    void Window::setTitle(const std::wstring& title) { setcaption(title.c_str()); }
    Window* Window::createWindow(const iRect& rect, bool hide) {
        if (Window::pInstance_)
            return Window::pInstance_;
        static Window window(rect.width(), rect.height(), H(hide));
        movewindow(rect.x(), rect.y());
        flushwindow();
        Window::pInstance_ = &window;
        return Window::pInstance_;
    }
    Window* Window::createFullScreenWindow(bool hide) {
        if (Window::pInstance_)
            return Window::pInstance_;
        static Window window(100_sw, 100_sh, H(hide) | INIT_NOBORDER | INIT_TOPMOST);
        movewindow(0, 0);
        flushwindow();
        Window::pInstance_ = &window;
        return Window::pInstance_;
    }
    Window* Window::createTopMostWindow(const iRect& rect, bool hide) {
        if (Window::pInstance_)
            return Window::pInstance_;
        static Window window(rect.width(), rect.height(), H(hide) | INIT_TOPMOST);
        movewindow(rect.x(), rect.y());
        flushwindow();
        Window::pInstance_ = &window;
        return Window::pInstance_;
    }
    Window* Window::createNoBorderWindow(const iRect& rect, bool hide) {
        if (Window::pInstance_)
            return Window::pInstance_;
        static Window window(rect.width(), rect.height(), H(hide) | INIT_NOBORDER);
        movewindow(rect.x(), rect.y());
        flushwindow();
        Window::pInstance_ = &window;
        return Window::pInstance_;
    }
    Window* Window::createNoBorderTopMostWindow(const iRect& rect, bool hide) {
        if (Window::pInstance_)
            return Window::pInstance_;
        static Window window(rect.width(), rect.height(), H(hide) | INIT_NOBORDER | INIT_TOPMOST);
        movewindow(rect.x(), rect.y());
        flushwindow();
        Window::pInstance_ = &window;
        return Window::pInstance_;
    }
    Window* Window::window() {
        return Window::pInstance_;
    }
}