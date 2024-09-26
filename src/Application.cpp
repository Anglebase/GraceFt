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
    float Application::renderTime_ = 0.0f;
    float Application::eventTime_ = 0.0f;
    bool Application::shouldClose_ = false;
    Application::Application(Window* root) {
        if (Application::root_ || !root)
            return;
        Application::root_ = root;
    }
    void Application::render(Window* window, bool clipO) {
        cleardevice();
        window->handleOnDraw(iPoint{}, clipO);
        flushwindow();
    }
    void Application::handleEvents(Window* window) {
        constexpr int max_msg_count = 10;
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
            if (msg.is_move()) {
                MouseMoveEvent event{ iPoint{ msg.x, msg.y } };
                window->handleOnMouseMove(&event);
            }
            else if (msg.is_down()) {
                MouseButtonPressEvent event{ iPoint{ msg.x, msg.y }, button, };
                window->handleOnMouseButtonPress(&event);
            }
            else if (msg.is_up()) {
                MouseButtonReleaseEvent event{ iPoint{ msg.x, msg.y }, button, };
                window->handleOnMouseButtonRelease(&event);
            }
            else if (msg.is_wheel()) {
                MouseWheel wheels;
                if (msg.wheel > 0)
                    wheels = MouseWheel::Up;
                else if (msg.wheel < 0)
                    wheels = MouseWheel::Down;
                else
                    wheels = MouseWheel::None;
                MouseWheelEvent event{ iPoint{ msg.x, msg.y }, wheels };
                window->handleOnMouseWheel(&event);
            }
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
            {
                KeyPressEvent event{
                        static_cast<Key>(msg.key),
                        static_cast<bool>(msg.flags & key_flag_shift),
                        static_cast<bool>(msg.flags & key_flag_ctrl),
                };
                block->handleOnKeyPress(&event);
            }
            break;
            case key_msg_up:
            {
                KeyReleaseEvent event{
                  static_cast<Key>(msg.key),
                  static_cast<bool>(msg.flags & key_flag_shift),
                  static_cast<bool>(msg.flags & key_flag_ctrl),
                };
                block->handleOnKeyRelease(&event);
            }
            break;
            case key_msg_char:
            {
                TextInputEvent event{ msg.key };
                block->handleOnTextInput(&event);
            }
            break;
            }
            count_kbmsg++;
            if (count_kbmsg > max_msg_count)
                break;
        } while (kbmsg());
        // 文本输入事件
        if (kbhit()) do {
            auto ch = getch();
            TextInputEvent event{ ch };
            block->handleOnTextInput(&event);
            count_textmsg++;
            if (count_textmsg > max_msg_count)
                break;
        } while (kbhit());
    }
    Application::~Application() {}
    /// @note 若未检测到窗口被成功创建，此函数不会阻塞，将会立即返回错误码 1(通常此函数返回值直接作为程序的退出码)
    int Application::exec(bool cilpO) {
        if (ege::getHWnd() == (HWND)0)
            return 1;
        auto lastTime = chrono::steady_clock::now();
        for (;is_run() && !Application::shouldClose_; Application::FPS_ > 0 ? delay_fps(Application::FPS_) : (void)0) {
            auto t1 = chrono::steady_clock::now();
            handleEvents(Application::root_);

            auto t2 = chrono::steady_clock::now();
            render(Application::root_, cilpO);

            auto nowTime = chrono::steady_clock::now();

            Application::realFps_ =
                1.0 / chrono::duration_cast<chrono::microseconds>
                (nowTime - lastTime).count() * 1000000.0;
            Application::eventTime_ = (t2 - t1).count() * 1e-3f;
            Application::renderTime_ = (nowTime - t2).count() * 1e-6f;
            lastTime = nowTime;
        }
        return 0;
    }
    int Application::run(bool cilpO) { return exec(cilpO); }
    void Application::shouldClose() { Application::shouldClose_ = true; }
    void Application::exit() { Application::shouldClose_ = true; }
    void Application::setFps(double fps) { Application::FPS_ = fps; }
    double Application::getFps() { return Application::FPS_; }
    float Application::getRealFps() { return Application::realFps_; }
    float Application::getRenderTime() { return Application::renderTime_; }
    float Application::getEventTime() { return Application::eventTime_; }
}