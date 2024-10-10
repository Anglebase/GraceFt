#pragma once

#include <list>
#include <functional>
#include <concepts>

namespace GFt {
    /// @brief 计划刻事件管理器
    /// @details 它可以将一系列的计划刻事件添加到计划中，并在特定时刻统一执行这些计划事件，
    ///          计划事件的执行顺序与添加的顺序相同，并且计划刻事件的调用是同步的，
    ///          计划刻事件会在每一帧 onEventCall 信号被触发时同步调用，且每个计划刻事件只会被调用一次
    class PlanEvent {
        using PlanFunc = std::function<void()>;
        std::list<PlanFunc> planEvents_;

        PlanEvent() = default;
        PlanEvent(const PlanEvent&) = delete;
        PlanEvent(PlanEvent&&) = delete;
        PlanEvent& operator=(const PlanEvent&) = delete;
        PlanEvent& operator=(PlanEvent&&) = delete;
    private:
        void executePlanEvents();

    public:
        /// @brief 添加计划事件
        /// @param planEvent 计划事件函数
        void addPlanEvent(const PlanFunc& planEvent);
        /// @brief 添加计划事件
        /// @tparam F 计划事件函数类型
        /// @tparam Args 计划事件函数参数类型
        /// @param f 计划事件函数
        /// @param args 计划事件函数参数

        // template<typename F, typename... Args>
        // void addPlanEvent(F f, Args... args) {
        //     addPlanEvent([f, args...]() { f(args...); });
        // }

        /// @brief 添加计划事件
        /// @tparam Object 计划事件函数所属对象类型
        /// @tparam Func 计划事件函数类型
        /// @tparam Args 计划事件函数参数类型
        /// @param object 计划事件函数所属对象
        /// @param func 计划事件函数
        /// @param args 计划事件函数参数
        template<typename Object, typename Func, typename... Args>
        void addPlanEvent(Object* object, Func func, Args... args) {
            addPlanEvent([object, func, args...]() { (object->*func)(args...); });
        }
        /// @brief 获取计划事件管理器实例
        /// @return 计划事件管理器实例
        static PlanEvent& getInstance();
    };
}