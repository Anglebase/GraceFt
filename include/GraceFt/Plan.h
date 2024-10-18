#pragma once

#include <unordered_map>
#include <functional>
#include <concepts>

namespace GFt {
    /// @brief 计划刻事件管理器
    /// @details 它可以将一系列的计划刻事件添加到计划中，并在特定时刻统一执行这些计划事件，
    ///          计划事件的执行顺序与添加的顺序相同，计划刻事件会在每一帧 onEventCall
    ///          信号被触发时调用，且每个计划刻事件只会被调用一次
    class PlanEvent {
        using PlanFunc = std::function<void()>;
        static std::size_t nextId_;
        std::unordered_map<std::size_t, PlanFunc> planEvents_;

        PlanEvent() = default;
        PlanEvent(const PlanEvent&) = delete;
        PlanEvent(PlanEvent&&) = delete;
        PlanEvent& operator=(const PlanEvent&) = delete;
        PlanEvent& operator=(PlanEvent&&) = delete;

        std::size_t addPlanEvent_(float after, const PlanFunc& planEvent);
        std::size_t addPlanEvent_(const PlanFunc& planEvent);
        std::size_t addPlanEvent_(const std::function<bool()>& condition, const PlanFunc& planEvent);
        std::size_t reAddPlanEvent_(std::size_t id, const PlanFunc& planEvent);
        void removePlanEvent_(std::size_t id);
        static PlanEvent& getInstance();
    private:
        void executePlanEvents();

    public:
        /// @brief 添加立即执行计划事件
        /// @param planEvent 计划事件函数
        /// @return 计划事件ID
        static std::size_t add(const PlanFunc& planEvent);

        /// @brief 添加延时执行计划事件
        /// @param after 计划事件延迟执行时间（单位：毫秒）
        /// @param planEvent 计划事件函数
        /// @details 计划事件会在至少 after 毫秒后执行
        /// @return 计划事件ID
        static std::size_t add(float after, const PlanFunc& planEvent);

        /// @brief 添加条件执行计划事件
        /// @param condition 计划事件条件函数
        /// @param planEvent 计划事件函数
        /// @details 计划事件会在 condition 函数返回 true 时执行
        /// @return 计划事件ID
        static std::size_t add(const std::function<bool()>& condition, const PlanFunc& planEvent);

        /// @brief 移除计划事件
        /// @param id 计划事件ID
        static void remove(std::size_t id);
    };
}