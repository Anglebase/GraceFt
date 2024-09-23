#pragma once

#include <queue>
#include <mutex>
#include <thread>

namespace GFt {
    /// @brief 通道模板类
    /// @tparam T 通道中元素的类型
    /// @ingroup 糖衣工具
    /// @note 此类是线程安全的，可用于多线程环境下的数据交换
    template<typename T>
    class Channel {
        std::queue<T> queue_;
        std::mutex mutex_;

        std::size_t capacity_;

        Channel(const Channel&) = delete;
        Channel& operator=(const Channel&) = delete;
        Channel(Channel&&) = delete;
        Channel& operator=(Channel&&) = delete;
    public:
        /// @brief 构造函数
        /// @param capacity 通道的容量，默认为1
        Channel(std::size_t capacity = 1ull) : capacity_(capacity <= 0? 1 : capacity) {}
        ~Channel() = default;

        /// @brief 发送数据到通道
        /// @param data 要发送的数据
        /// @details 若通道已满，则线程会被阻塞，直到有空余位置
        void send(const T& data) {
            while (queue_.size() >= capacity_)
                std::this_thread::yield();
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(data);
        }
        /// @brief 发送数据到通道
        /// @param data 要发送的数据
        /// @see send()
        void send(T&& data) {
            while (queue_.size() >= capacity_)
                std::this_thread::yield();
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(data));
        }
        /// @brief 尝试发送数据到通道
        /// @param data 要发送的数据
        /// @return 若成功发送，则返回true，否则返回false
        /// @details 若通道已满，则不会发送数据，并返回false
        bool try_send(const T& data) {
            if (queue_.size() >= capacity_)
                return false;
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(data);
            return true;
        }
        /// @brief 尝试发送数据到通道
        /// @param data 要发送的数据
        /// @return 若成功发送，则返回true，否则返回false
        /// @see try_send()
        bool try_send(T&& data) {
            if (queue_.size() >= capacity_)
                return false;
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(data));
            return true;
        }
        /// @brief 从通道接收数据
        /// @return 接收到的数据
        /// @details 若通道为空，则线程会被阻塞，直到有数据到来
        T recv() {
            while (queue_.empty())
                std::this_thread::yield();
            std::lock_guard<std::mutex> lock(mutex_);
            T data = queue_.front();
            queue_.pop();
            return data;
        }
        /// @brief 尝试从通道接收数据
        /// @param data 接收到的数据
        /// @return 若成功接收，则返回true，否则返回false
        /// @details 若通道为空，则不会接收数据，并返回false
        bool try_recv(T& data) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (queue_.empty())
                return false;
            data = queue_.front();
            queue_.pop();
            return true;
        }
    };
}