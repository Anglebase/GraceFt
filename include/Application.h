#pragma once

#include <Window.h>

namespace GFt {

    class Application {
        int sync_exec(Window* window);
        int async_exec(Window* window);
        void render(Window* window);
        void handleEvents(Window* window);
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
        int exec();
        double& fps();
        const double& fps() const;
        float getRealFps() const;
    };
}