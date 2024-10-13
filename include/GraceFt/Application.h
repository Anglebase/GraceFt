#pragma once

#include <GraceFt/Window.h>
#include <filesystem>

namespace GFt {
    /// @class Application
    /// @brief 应用程序类
    /// @details 该类封装了程序的主要逻辑, 包括渲染, 事件处理, 帧率控制等
    /// @ingroup 基础UI封装库
    class Application {
        void render(Window* window, bool cilpO);
        void handleEvents(Window* window);
        static Window* root_;
        static double FPS_;
        static float realFps_;
        static float renderTime_;
        static float eventTime_;

        static bool shouldClose_;
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

        /// @brief 更新鼠标悬浮状态
        /// @details 此函数用于通知应用更新 BlockHoverManager
        /// @note 该函数默认只会在捕获到鼠标事件时才会被调用，如果 Block 对象树含有具有位置动画的对象,
        ///       则需要在每一帧调用此函数来更新 BlockHoverManager 的状态以确保
        ///       BlockHoverManager 状态的正确性，通常直接将其连接到 onEventCall 信号以实现自动更新
        /// @code
        /// // 将 updateBlockHoverState 函数连接到 onEventCall 信号
        /// // 在 main 函数的开头添加以下代码即可
        /// Window::onWindowCreated.connect([](Window* w) {
        ///     Application::onEventCall.connect(&Application::updateBlockHoverState);
        ///     });
        /// @endcode
        static void updateBlockHoverState();

        /// @brief 运行程序
        /// @param cilpO 是否启用绘图裁剪优化
        /// @return 程序退出状态
        /// @details 该函数会阻塞线程, 直到程序退出
        int exec(bool cilpO = true);
        /// @brief 运行程序
        /// @return 程序退出状态
        /// @details 该函数效果等同于 exec()
        /// @see exec()
        int run(bool cilpO = true);
        /// @brief 退出程序
        /// @details 调用此函数会导致程序退出
        static void shouldClose();
        /// @brief 退出程序
        /// @details 该效果等同于 shouldClose()
        static void exit();
        /// @brief 设置目标帧率
        /// @param fps 目标帧率
        /// @details 若所设定的帧率小于等于0, 则视为无帧率限制
        /// @details 对于大多数设备而言, 推荐帧率值为 60
        static void setFps(double fps);
        /// @brief 获取目标帧率
        /// @return 目标帧率
        static double getFps();
        /// @brief 获取真实帧率
        /// @return 真实帧率
        static float getRealFps();
        /// @brief 获取渲染帧时长
        /// @return 渲染帧时长(以毫秒计)
        static float getRenderTime();
        /// @brief 获取事件处理帧时长
        /// @return 事件处理帧时长(以微秒计)
        static float getEventTime();
        /// @brief 获取根窗口节点
        /// @return 根窗口节点
        static Block* getRoot();
        /// @brief 设置鼠标是否可见
        /// @param show 是否可见
        /// @return 之前鼠标是否可见
        static bool showCursor(bool show);
        /// @brief 获取鼠标相对于屏幕的绝对位置
        /// @return 鼠标位置
        /// @see Sys::getCursorPosition()
        static iPoint getAbsoluteMousePosition();
        /// @brief 获取应用程序的可执行文件所在的路径
        /// @details 此函数是惰性求值函数
        /// @return 可执行文件所在的路径，若失败则返回空路径
        static std::filesystem::path localPath();

        static Signal<void> onRenderCall;   ///< 每一帧渲染(之前)时触发此信号
        static Signal<void> onEventCall;    ///< 每一帧事件处理(之前)时触发此信号
    };
}