#pragma once

#include <Window.h>

namespace GFt {
    /// @brief 程序执行模式
    enum class ExecMode {
        Sync,   ///< 同步模式: 所有逻辑都在主线程中执行
        Async   ///< 异步模式: 绘制逻辑和事件处理逻辑分属于两个不同于主线程的线程
    };

    class Application {
        int sync_exec(Window* window);
        int async_exec(Window* window);
        static Window* root_;
        static double FPS_;
    private:
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

    public:
        explicit Application(Window* root);
        ~Application();
        int exec(ExecMode mode = ExecMode::Sync);
        double& fps();
        const double& fps() const;
        float getRealFps() const;
    };
}