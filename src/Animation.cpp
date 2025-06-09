#include "GraceFt/Animation.hpp"
#include <GraceFt/Application.h>

namespace GFt {
    AnimationState::AnimationState(AnimationAbstract* owner) : owner_(owner) {}
    AnimationAbstract::AnimationAbstract(
        const TimePoint& start_time,
        float ms,
        const TransFunc& trans_func)
        : start_time_(start_time),
        duration_ms_(ms),
        trans_func_(trans_func ? trans_func : [](float x)->float { return x; }) {
        state_ = new AnimationStop(this);
    }
    AnimationAbstract::~AnimationAbstract() {
        delete state_;
    }
    void AnimationAbstract::update(const TimePoint& now) { if (state_) state_->update(now); }
    /// @details 若处于停止状态，则此函数无效
    void AnimationAbstract::setStop() {
        if (isStopped()) return;
        if (isPlaying())
            onStateChanged(AnimationStateType::Play, AnimationStateType::Stop);
        else if (isPaused())
            onStateChanged(AnimationStateType::Pause, AnimationStateType::Stop);
        delete state_;
        state_ = new AnimationStop(this);
    }
    /// @details 若处于播放状态，则此函数无效
    void AnimationAbstract::setPlay() {
        if (isPlaying()) return;
        if (isPaused())
            onStateChanged(AnimationStateType::Pause, AnimationStateType::Play);
        else if (isStopped())
            onStateChanged(AnimationStateType::Stop, AnimationStateType::Play);
        delete state_;
        state_ = new AnimationPlay(this);
        hadSetPlay();
    }
    /// @details 不允许从停止状态直接切换到暂停状态，必须先切换到播放状态再切换到暂停状态
    ///          若处于停止状态或暂停状态，则此函数无效
    void AnimationAbstract::setPause() {
        if (isPaused() || isStopped()) return;
        if (isPlaying())
            onStateChanged(AnimationStateType::Play, AnimationStateType::Pause);
        delete state_;
        state_ = new AnimationPause(this);
    }
    bool AnimationAbstract::isPlaying() const {
        return dynamic_cast<AnimationPlay*>(state_) != nullptr;
    }
    bool AnimationAbstract::isPaused() const {
        return dynamic_cast<AnimationPause*>(state_) != nullptr;
    }
    bool AnimationAbstract::isStopped() const {
        return dynamic_cast<AnimationStop*>(state_) != nullptr;
    }
    void AnimationAbstract::setTransFunc(const TransFunc& trans_func) { trans_func_ = trans_func; }
    void AnimationAbstract::setDuration(float ms) { duration_ms_ = ms; }
    const TransFunc& AnimationAbstract::getTransFunc() const { return trans_func_; }
    float AnimationAbstract::getDuration() const { return duration_ms_; }
    AnimationStop::AnimationStop(AnimationAbstract* owner) : AnimationState(owner) {}
    void AnimationStop::update(const TimePoint& now) { owner_->start_time_ = now; }
    AnimationPlay::AnimationPlay(AnimationAbstract* owner) : AnimationState(owner) {}
    void AnimationPlay::update(const TimePoint& now) { owner_->playingUpdate(now); }
    AnimationPause::AnimationPause(AnimationAbstract* owner) : AnimationState(owner) {}
    void AnimationPause::update(const TimePoint& now) { owner_->start_time_ = now - owner_->finished_; }
    void AnimationManager::registerAnimation(AnimationAbstract* animation) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (std::find(animations_.begin(), animations_.end(), animation) == animations_.end())
            animations_.push_back(animation);
    }
    void AnimationManager::unregisterAnimation(AnimationAbstract* animation) {
        std::lock_guard<std::mutex> lock(mutex_);
        using Iter = std::list<AnimationAbstract*>::iterator;
        Iter it = std::remove_if(animations_.begin(), animations_.end(),
            [animation](AnimationAbstract* a) { return a == animation; });
        animations_.erase(it, animations_.end());
    }
    void AnimationManager::updateAll(const TimePoint& now) {
        for (auto animation : animations_)
            animation->update(now);
    }
    AnimationManager& AnimationManager::getInstance() {
        static AnimationManager instance;
        static bool initialized = false;
        if (!initialized) {
            initialized = true;
            Application::onEventCall.connect([] {
                using namespace std::chrono;
                AnimationManager::getInstance().updateAll(steady_clock::now());
                });
        }
        return instance;
    }
}