#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>

namespace GFt {
    /// @typedef SlotId
    /// @tparam Args 信号/槽函数参数类型
    /// @brief 槽函数ID类型
    template<typename... Args>
    using SlotId = std::size_t;
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 对象通信机制
    /// @{
        /// @class Signal
        /// @brief 信号-槽机制支持
        /// @details 支持任意数量的槽函数，支持任意数量的参数，支持任意类型的参数
        /// @details 此类是线程安全的，且它是 基础设施库 => 对象通信机制 的一部分
        /// @tparam Args 信号参数类型
    /// @}
    /// @}
    template<typename... Args>
    class Signal {
        using Slot = std::function<void(Args...)>;
        using Slots = std::unordered_map<SlotId<Args...>, Slot>;

        Slots slots_;
        std::mutex mutex_;
    private:
        Signal(const Signal&) = delete;
        Signal(Signal&&) = delete;
        Signal& operator=(const Signal&) = delete;
        Signal& operator=(Signal&&) = delete;
    public:
        Signal() = default;
        /// @brief 连接槽函数
        /// @param slot 槽函数
        /// @return 槽函数ID
        /// @details 连接的槽函数会在信号发出时被调用
        /// @details 槽函数ID是按顺序生成的，从0开始
        /// @note 生成的槽函数ID时只保证唯一性，不保证其连续性
        /// @note 调用槽函数时不保证调用顺序与连接顺序一致
        SlotId<Args...> connect(const Slot& slot) {
            static SlotId<Args...> id = 0ull;
            std::lock_guard<std::mutex> lock(mutex_);
            slots_[id] = slot;
            return id++;
        }
        /// @brief 断开槽函数
        /// @param id 槽函数ID
        void disconnect(SlotId<Args...> id) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (slots_.find(id) != slots_.end())
                slots_.erase(id);
        }
        /// @brief 发送信号
        /// @param args 信号参数
        /// @note 调用槽函数时不保证调用顺序与连接顺序一致
        /// @note 此函数是线程安全的，但不保证槽函数的线程安全性
        void emit(Args&&... args) {
            Slots slots;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                slots = slots_;
            }
            for (auto& [id, slot] : slots)
                slot(std::forward<Args>(args)...);
        }
        /// @brief 发送信号
        /// @param args 信号参数
        /// @details 效果同 emit(Args&&... args)
        /// @see emit(Args&&... args)
        void operator()(Args&&... args) {
            emit(std::forward<Args>(args)...);
        }
    };
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 对象通信机制
    /// @{
        /// @class Signal<void>
        /// @brief Signal 的无参数特化版本
        /// @see Signal
    /// @}
    /// @}
    template<>
    class Signal<void> {
        using Slot = std::function<void()>;
        using Slots = std::unordered_map<SlotId<void>, Slot>;

        Slots slots_;
        std::mutex mutex_;
    private:
        Signal(const Signal&) = delete;
        Signal(Signal&&) = delete;
        Signal& operator=(const Signal&) = delete;
        Signal& operator=(Signal&&) = delete;
    public:
        Signal() = default;
        /// @brief 连接槽函数
        /// @param slot 槽函数
        /// @return 槽函数ID
        SlotId<void> connect(const Slot& slot) {
            static SlotId<void> id = 0ull;
            std::lock_guard<std::mutex> lock(mutex_);
            slots_[id] = slot;
            return id++;
        }
        /// @brief 断开槽函数
        /// @param id 槽函数ID
        void disconnect(SlotId<void> id) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (slots_.find(id) != slots_.end())
                slots_.erase(id);
        }
        /// @brief 发送信号
        void emit() {
            Slots slots;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                slots = slots_;
            }
            for (auto& [id, slot] : slots)
                slot();
        }
        /// @brief 发送信号
        /// @details 效果同 emit()
        /// @see emit()
        void operator()() {
            emit();
        }
    };
}