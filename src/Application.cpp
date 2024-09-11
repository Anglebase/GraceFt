#include "Application.h"

#include <thread>
#include <ege.h>

namespace GFt {
    using namespace ege;
    using namespace std;
    Window* Application::root_ = nullptr;
    double Application::FPS_ = -1.0;
    Application::Application(Window* root) {
        if (Application::root_)
            return;
        Application::root_ = root;
    }

    int Application::sync_exec(Window* window) {
        constexpr int max_msg_count = 50;
        for (;is_run(); Application::FPS_ > 0 ? delay_fps(Application::FPS_) : (void)0) {
            int count_mousemsg = 0, count_kbmsg = 0, count_textmsg = 0;
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
                else if (msg.is_down()) {
                    window->handleOnMouseButtonPress(MouseButtonPressEvent{
                        iPoint{ msg.x, msg.y }, button,
                        });
                }
                else if (msg.is_up()) {
                    window->handleOnMouseButtonRelease(MouseButtonReleaseEvent{
                        iPoint{ msg.x, msg.y }, button,
                        });
                }
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
            if (kbmsg()) do {
                auto msg = getkey();
                if (msg.msg == key_msg_down)
                    window->handleOnKeyPress(KeyPressEvent{
                        static_cast<Key>(msg.key),
                        static_cast<bool>(msg.flags & key_flag_shift),
                        static_cast<bool>(msg.flags & key_flag_ctrl),
                        });
                else if (msg.msg == key_msg_up)
                    window->handleOnKeyRelease(KeyReleaseEvent{
                        static_cast<Key>(msg.key),
                        static_cast<bool>(msg.flags & key_flag_shift),
                        static_cast<bool>(msg.flags & key_flag_ctrl),
                        });
                count_kbmsg++;
                if (count_kbmsg > max_msg_count)
                    break;
            } while (kbmsg());
            if (kbhit()) do {
                auto ch = getch();
                window->handleOnTextInput(TextInputEvent{ ch });
                count_textmsg++;
                if (count_textmsg > max_msg_count)
                    break;
            } while (kbhit());
            cleardevice();
            window->handleOnDraw();
            flushwindow();
        }
        return 0;
    }
    int Application::async_exec(Window* window) {
        return 0;
    }

    Application::~Application() {}
    int Application::exec(ExecMode mode) {
        switch (mode) {
        case ExecMode::Sync:
            return sync_exec(Application::root_);
        case ExecMode::Async:
            return async_exec(Application::root_);
        default:
            break;
        }
        return 0;
    }
    double& Application::fps() { return Application::FPS_; }
    const double& Application::fps() const { return Application::FPS_; }
    float Application::getRealFps() const { return getfps(); }
}