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
        /// @param after 计划事件延迟执行时间（单位：毫秒）
        /// @param planEvent 计划事件函数
        /// @details 计划事件会在至少 after 毫秒后执行
        void addPlanEvent(float after, const PlanFunc& planEvent);

        /// @brief 获取计划事件管理器实例
        /// @return 计划事件管理器实例
        static PlanEvent& getInstance();
    };
}