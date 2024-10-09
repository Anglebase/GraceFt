#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <cmath>
#include <mutex>
#include <GraceFt/Signal.hpp>

namespace GFt {
    /// @defgroup 动画支持库
    /// @ingroup 基础设施库

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    using TransFunc = std::function<float(float)>;
    template<typename Type>
    concept Animatable = requires(Type v) { { v + (v - v) * 1.f } -> std::convertible_to<Type>; };
    template<typename Type>
    using Setter = std::function<void(const Type&)>;

    /// @brief 动画状态类型
    /// @ingroup 动画支持库
    enum class AnimationStateType {
        Stop,   ///< 停止状态
        Play,   ///< 播放状态
        Pause   ///< 暂停状态
    };

    class AnimationAbstract;
    /// @brief 动画状态基类
    /// @ingroup 动画支持库
    class AnimationState {
    protected:
        AnimationAbstract* owner_;

    public:
        AnimationState(AnimationAbstract* owner);
        virtual void update(const TimePoint& now) = 0;
    };
    /// @brief 动画抽象基类
    /// @ingroup 动画支持库
    class AnimationAbstract {
        friend class AnimationManager;
        friend class AnimationState;
        friend class AnimationStop;
        friend class AnimationPlay;
        friend class AnimationPause;
        template<typename Type> requires Animatable<Type> friend class Animation;

        TimePoint start_time_;
        std::chrono::milliseconds finished_;
        float duration_ms_;
        TransFunc trans_func_;
        AnimationState* state_ = nullptr;

    protected:
        virtual void playingUpdate(const TimePoint& now) = 0;

    public:
        AnimationAbstract(const TimePoint& start_time, float ms, const TransFunc& trans_func);
        ~AnimationAbstract();
        void update(const TimePoint& now);

        /// @brief 设置动画状态为停止
        void setStop();
        /// @brief 设置动画状态为播放
        void setPlay();
        /// @brief 设置动画状态为暂停
        void setPause();
        /// @brief 判断动画是否处于播放状态
        bool isPlaying() const;
        /// @brief 判断动画是否处于暂停状态
        bool isPaused() const;
        /// @brief 判断动画是否处于停止状态
        bool isStopped() const;

        Signal<AnimationStateType, AnimationStateType> onStateChanged;  ///< 动画状态改变信号
        Signal<void> onFinished;  ///< 动画进度改变信号
    };
    /// @brief 停止状态
    /// @ingroup 动画支持库
    class AnimationStop : public AnimationState {
    public:
        AnimationStop(AnimationAbstract* owner);
        void update(const TimePoint& now) override;
    };
    /// @brief 播放状态
    /// @ingroup 动画支持库
    class AnimationPlay : public AnimationState {
    public:
        AnimationPlay(AnimationAbstract* owner);
        void update(const TimePoint& now) override;
    };
    /// @brief 暂停状态
    /// @ingroup 动画支持库
    class AnimationPause : public AnimationState {
    public:
        AnimationPause(AnimationAbstract* owner);
        void update(const TimePoint& now) override;
    };
    /// @brief 动画参数结构体
    /// @ingroup 动画支持库
    template<typename Type>
        requires Animatable<Type>
    struct AnimationParams {
        const Setter<Type>& setter;     ///< 动画值的 setter 方法
        const Type& initial;            ///< 动画初始值
        const Type& target;             ///< 动画目标值
        const float& duration;          ///< 动画持续时间（毫秒）
        TransFunc trans_func;           ///< 动画过渡函数
    };
    /// @brief 动画模板类
    /// @tparam Type 动画值类型
    /// @ingroup 动画支持库
    template<typename Type>
        requires Animatable<Type>
    class Animation : public AnimationAbstract {
        Type start_value_;
        Type end_value_;

        Setter<Type> setter_;
    protected:
        void playingUpdate(const TimePoint& now) override {
            using namespace std::chrono;
            finished_ = duration_cast<milliseconds>(now - start_time_);
            auto elapsed_ns = duration_cast<nanoseconds>(finished_).count();
            auto progress = elapsed_ns * 1e-6f / duration_ms_;
            if (progress > 1.f) {
                setStop();
                onFinished();
                return;
            }
            setter_(start_value_ + (end_value_ - start_value_) * trans_func_(progress));
        }
    public:
        /// @brief 构造函数
        /// @param params 动画参数结构体
        Animation(const AnimationParams<Type>& params)
            : setter_(params.setter), start_value_(params.initial), end_value_(params.target),
            AnimationAbstract(TimePoint(), params.duration, params.trans_func) {}
    };
    /// @brief 动画管理器
    /// @details 此类是线程安全的
    /// @ingroup 动画支持库
    class AnimationManager {
        std::list<AnimationAbstract*> animations_;
        std::mutex mutex_;

        AnimationManager() = default;
        AnimationManager(const AnimationManager&) = delete;
        AnimationManager(AnimationManager&&) = delete;
        AnimationManager& operator=(const AnimationManager&) = delete;
        AnimationManager& operator=(AnimationManager&&) = delete;
    public:
        /// @brief 注册动画对象
        /// @param animation 动画对象
        void registerAnimation(AnimationAbstract* animation);
        /// @brief 注销动画对象
        /// @param animation 动画对象
        void unregisterAnimation(AnimationAbstract* animation);
        /// @brief 更新所有动画对象
        /// @param now 当前时间
        void updateAll(const TimePoint& now);

        /// @brief 获取动画管理器实例
        static AnimationManager& getInstance();
    };

    /// @brief 过渡函数集合
    /// @details 此命名空间包含了一些常用的过渡函数，并给出了它们的曲线图像
    /// @note 自定义过渡函数要求：
    /// - 函数类型为 `float(float)`
    /// - 需要保证函数的定义域包含 [0, 1] 区间
    /// @ingroup 动画支持库
    namespace TransFuncs {
        /// @brief 线性过渡函数(默认函数)
        /// @image html "transfunc/linear.png" "linear 过渡变换曲线"
        inline float linear(float x) { return x; }
        /// @image html "transfunc/exp2.png" "exp2 过渡变换曲线"
        inline float exp2(float x) { return ::std::pow(x, 2.f); }
        /// @image html "transfunc/exp3.png" "exp3 过渡变换曲线"
        inline float exp3(float x) { return ::std::pow(x, 3.f); }
        /// @image html "transfunc/exp4.png" "exp4 过渡变换曲线"
        inline float exp4(float x) { return ::std::pow(x, 4.f); }
        /// @image html "transfunc/bezier.png" "bezier 过渡变换曲线"
        inline float bezier(float x) { return 3.f * x * x - 2.f * x * x * x; }
        /// @image html "transfunc/easeIn.png" "easeIn 过渡变换曲线"
        inline float easeIn(float x) { return 1.f - ::std::pow(1.f - x, 2.f); }
    }
}