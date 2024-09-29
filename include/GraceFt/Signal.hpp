#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>
#include <concepts>

namespace GFt {
    /// @typedef SlotId
    /// @tparam Args 信号/槽函数参数类型
    /// @brief 槽函数ID类型
    template<typename... Args>
    using SlotId = std::size_t;
    /// @addtogroup 糖衣工具
    /// @ingroup 基础设施库

    /// @class Signal
    /// @brief 信号-槽机制支持
    /// @details 支持任意数量的槽函数，支持任意数量的参数，支持任意类型的参数
    /// @details 此类是线程安全的，这意味着你可以在另一线程执行槽函数时添加或移除槽函数，但不保证槽函数运行的线程安全性
    /// @tparam Args 信号参数类型
    /// @ingroup 糖衣工具
    template<typename... Args>
    class Signal {
        using Slot = std::function<void(Args...)>;
        using Slots = std::unordered_map<SlotId<Args...>, Slot>;

        SlotId<Args...> id_ = 0ull;

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
            std::lock_guard<std::mutex> lock(mutex_);
            slots_[id_] = slot;
            return id_++;
        }
        /// @brief 将成员函数作为槽函数连接
        /// @tparam Derived 对象类类型
        /// @tparam Base 成员函数所在类类型
        /// @note 要求 Derived 必须是 Base 的派生类(子类)或 Base 本身
        /// @param object 成员函数所在类的实例
        /// @param method 成员函数指针
        /// @return 槽函数ID
        template<typename Derived, typename Base>
            requires std::derived_from<Derived, Base>
        SlotId<Args...> connect(Derived* object, void (Base::* method)(Args...)) {
            return connect([object, method](Args... args) {
                (dynamic_cast<Base*>(object)->*method)(std::forward<Args>(args)...);
            });
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
        void emit(Args... args) {
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
        void operator()(Args... args) {
            emit(std::forward<Args>(args)...);
        }
    };
    /// @addtogroup 基础设施库
    /// @{
    /// @addtogroup 糖衣工具
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

        SlotId<void> id_ = 0ull;

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
            std::lock_guard<std::mutex> lock(mutex_);
            slots_[id_] = slot;
            return id_++;
        }
        /// @brief 将成员函数作为槽函数连接
        /// @tparam Derived 对象类类型
        /// @tparam Base 成员函数所在类类型
        /// @note 要求 Derived 必须是 Base 的派生类(子类)或 Base 本身
        /// @param object 成员函数所在类的实例
        /// @param method 成员函数指针
        /// @return 槽函数ID
        template<typename Derived, typename Base>
            requires std::derived_from<Derived, Base>
        SlotId<void> connect(Derived* object, void (Base::* method)()) {
            return connect([object, method]() {
                (dynamic_cast<Base*>(object)->*method)();
            });
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