#pragma once

#include <Window.h>

namespace GFt {
    /// @class Application
    /// @brief 应用程序类
    /// @details 该类封装了程序的主要逻辑, 包括渲染, 事件处理, 帧率控制等
    /// @ingroup 基础UI封装库
    class Application {
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
        /// @brief 构造函数
        /// @param root 根窗口节点
        /// @details 此类在全局只会创建一个对象,即使多次调用其构造函数也只会构造一次
        Application(Window* root);
        ~Application();

        /// @brief 运行程序
        /// @return 程序退出状态
        /// @details 该函数会阻塞线程, 直到程序退出
        int exec();
        /// @brief 设置目标帧率
        /// @param fps 目标帧率
        /// @details 若所设定的帧率小于等于0, 则视为无限制帧率
        /// @details 对于大多数设备而言, 推荐帧率值为 60
        void setFps(double fps);
        /// @brief 获取目标帧率
        /// @return 目标帧率
        double getFps() const;
        /// @brief 获取真实帧率
        /// @return 真实帧率
        float getRealFps() const;
    };
}