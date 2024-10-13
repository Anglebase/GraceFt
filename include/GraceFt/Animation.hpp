#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <cmath>
#include <mutex>
#include <variant>
#include <GraceFt/Signal.hpp>

namespace GFt {
    /// @defgroup 动画支持库
    /// @ingroup 基础设施库

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    using TransFunc = std::function<float(float)>;

    /// @brief 此概念约束类型 Type 必须支持线性插值运算
    /// @details 即对于 Type 类型的值 a 和 b，其表达式 a + (b - a) * t (t 为浮点数) 必须是合法的，
    ///          且返回值类型必须可以隐式转换为 Type 类型
    template<typename Type>
    concept Animatable = requires(Type v) { { v + (v - v) * 1.f } -> std::convertible_to<Type>; };

    template<typename Type>
    using Setter = std::function<void(const Type&)>;
    template<typename Type>
    using Getter = std::function<Type()>;
    template<typename Type>
    using Initial = std::variant<Type, Getter<Type>>;

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
        virtual void hadSetPlay() = 0;
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
        /// @brief 设置动画过渡变换函数
        /// @param trans_func 过渡变换函数
        void setTransFunc(const TransFunc& trans_func);
        /// @brief 设置动画持续时间
        /// @param ms 持续时间（毫秒）
        void setDuration(float ms);
        /// @brief 获取动画的过渡变换函数
        /// @return 动画的过渡变换函数
        const TransFunc& getTransFunc() const;
        /// @brief 获取动画的持续时间
        /// @return 动画的持续时间（毫秒）
        float getDuration() const;

        using AType = AnimationStateType;
        Signal<AType, AType> onStateChanged;    ///< 动画状态改变信号
        Signal<void> onFinished;                ///< 动画进度改变信号
        Signal<void> onUpdated;                 ///< 动画值更新信号
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
        const Initial<Type>& initial;   ///< 动画初始值，可以是值或 getter 方法，若为 getter 方法则在动画开始时调用并作为初始值
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

        Getter<Type> getter_;
        Setter<Type> setter_;
    protected:
        void hadSetPlay() override {
            if (getter_)
                start_value_ = getter_();
        }
        void playingUpdate(const TimePoint& now) override {
            using namespace std::chrono;
            finished_ = duration_cast<milliseconds>(now - start_time_);
            auto elapsed_ns = duration_cast<nanoseconds>(finished_).count();
            auto progress = elapsed_ns * 1e-6f / duration_ms_;
            if (progress > 1.f) {
                setStop();
                onFinished();
                start_time_ = now;
                return;
            }
            setter_(start_value_ + (end_value_ - start_value_) * trans_func_(progress));
            onUpdated();
        }
    public:
        /// @brief 构造函数
        /// @param params 动画参数结构体
        Animation(const AnimationParams<Type>& params)
            : setter_(params.setter), end_value_(params.target),
            AnimationAbstract(TimePoint(), params.duration, params.trans_func) {
            setInitial(params.initial);
        }
        /// @brief 设置动画初始化值
        /// @param initial 动画初始值，可以是值或 getter 方法
        /// @details 若为 getter 方法则在动画开始时调用并作为初始值
        ///          若为值则直接作为初始值
        void setInitial(const Initial<Type>& initial) {
            auto ptr = std::get_if<Type>(&initial);
            ptr ? start_value_ = *ptr, getter_ = Getter<Type>()
                : getter_ = std::get<Getter<Type>>(initial);
        }
        /// @brief 设置动画目标值
        /// @param target 动画目标值
        void setTarget(const Type& target) { end_value_ = target; }
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
    /// - 函数应当经过点 (0, 0) 和 点(1, 1)
    /// @ingroup 动画支持库
    namespace TransFuncs {
        /// @brief 线性过渡函数(默认函数)
        constexpr float linear(float x) { return x; }
        /// @brief 幂函数生成器
        /// @param power 幂指数
        /// @return 幂函数
        constexpr auto power(float power) {
            return [power](float k)->float {
                return ::std::pow(k, power);
                };
        }
        /// @brief 贝塞尔过渡
        constexpr float bezier(float x) { return 3.f * x * x - 2.f * x * x * x; }
        /// @brief 柔性过渡
        constexpr float smoothInOut(float x) {
            constexpr auto tao = 2 * ::std::numbers::pi;
            auto y = x * tao;
            return (y - ::std::sin(y)) / tao;
        }
        /// @brief 过阻尼衰减函数生成器
        /// @param damping 等效阻尼因数，值越大越快地达到目标值，此值不能为零
        /// @return 过阻尼衰减函数
        constexpr auto overDamped(float damping) {
            return [damping](float x)-> float {
                return (1.f - ::std::exp(-damping * x * x)) * (1 / (1 - ::std::exp(-damping)));
                };
        }
        /// @brief 欠阻尼衰减函数生成器
        /// @param damping 等效阻尼因数，值越大超调震荡频率越高
        /// @return 欠阻尼衰减函数
        constexpr auto underDamped(float damping) {
            return [damping](float x)-> float { return 1.f - (1.f - x) * ::std::cos(x * damping); };
        }
    }
}