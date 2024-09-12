#include "Application.h"

#include <thread>
#include <mutex>
#include <ege.h>
#include <chrono>

#include <BlockFocus.h>

namespace GFt {
    using namespace ege;
    using namespace std;
    Window* Application::root_ = nullptr;
    double Application::FPS_ = -1.0;
    float Application::realFps_ = 0.0;
    Application::Application(Window* root) {
        if (Application::root_ || !root)
            return;
        Application::root_ = root;
    }
    std::mutex handleMutex;
    void Application::render(Window* window) {
        cleardevice();
        window->handleOnDraw();
        flushwindow();
    }
    void Application::handleEvents(Window* window) {
        constexpr int max_msg_count = 20;
        int count_mousemsg = 0, count_kbmsg = 0, count_textmsg = 0;
        // 鼠标事件
        if (mousemsg()) do {
            auto msg = getmouse();
            // 获取鼠标按键
            MouseButton button;
            if (msg.is_left())
                button = MouseButton::Left;
            else if (msg.is_right())
                button = MouseButton::Right;
            else if (msg.is_mid())
                button = MouseButton::Middle;
            else
                button = MouseButton::Unknown;
            // 处理鼠标事件
            if (msg.is_move())
                window->handleOnMouseMove(MouseMoveEvent(iPoint{ msg.x, msg.y }));
            else if (msg.is_down())
                window->handleOnMouseButtonPress(MouseButtonPressEvent{
                    iPoint{ msg.x, msg.y }, button,
                    });
            else if (msg.is_up())
                window->handleOnMouseButtonRelease(MouseButtonReleaseEvent{
                    iPoint{ msg.x, msg.y }, button,
                    });
            else if (msg.is_wheel())
                window->handleOnMouseWheel(MouseWheelEvent{
                    iPoint{ msg.x, msg.y },
                    msg.wheel > 0
                        ? MouseWheel::Up
                        : msg.wheel < 0
                            ? MouseWheel::Down
                            : MouseWheel::None,
                    });
            count_mousemsg++;
            if (count_mousemsg > max_msg_count)
                break;
        } while (mousemsg());
        // 键盘事件
        Block* block = BlockFocusManager::getFocusOn();
        if (!block)
            return;
        if (kbmsg()) do {
            auto msg = getkey();
            switch (msg.msg) {
            case key_msg_down:
                block->handleOnKeyPress(KeyPressEvent{
                    static_cast<Key>(msg.key),
                    static_cast<bool>(msg.flags & key_flag_shift),
                    static_cast<bool>(msg.flags & key_flag_ctrl),
                    });
                break;
            case key_msg_up:
                block->handleOnKeyRelease(KeyReleaseEvent{
                    static_cast<Key>(msg.key),
                    static_cast<bool>(msg.flags & key_flag_shift),
                    static_cast<bool>(msg.flags & key_flag_ctrl),
                    });
                break;
            case key_msg_char:
                block->handleOnTextInput(TextInputEvent{ msg.key });
                break;
            }
            count_kbmsg++;
            if (count_kbmsg > max_msg_count)
                break;
        } while (kbmsg());
        // 文本输入事件
        if (kbhit()) do {
            auto ch = getch();
            // std::cout << "ch: " << ch << std::endl;
            // if (std::iswprint(ch) || std::iswspace(ch))
            block->handleOnTextInput(TextInputEvent{ ch });
            count_textmsg++;
            if (count_textmsg > max_msg_count)
                break;
        } while (kbhit());
    }
    Application::~Application() {}
    int Application::exec() {
        auto lastTime = chrono::steady_clock::now();
        for (;is_run(); Application::FPS_ > 0 ? delay_fps(Application::FPS_) : (void)0) {
            handleEvents(Application::root_);
            render(Application::root_);
            auto nowTime = chrono::steady_clock::now();
            Application::realFps_ =
                1.0 / chrono::duration_cast<chrono::microseconds>
                (nowTime - lastTime).count() * 1000000.0;
            lastTime = nowTime;
        }
        return 0;
    }
    void Application::setFps(double fps) { Application::FPS_ = fps; }
    double Application::getFps() { return Application::FPS_; }
    float Application::getRealFps() { return Application::realFps_; }
}