#include "Plan.h"
#include <Application.h>

namespace GFt {
    std::size_t PlanEvent::nextId_ = 0;
    void PlanEvent::executePlanEvents() {
        std::unordered_map<std::size_t, PlanFunc> calls;
        calls.swap(planEvents_);
        planEvents_.clear();
        for (auto& [_, planEvent] : calls)
            planEvent();
    }

    std::size_t PlanEvent::add(const PlanFunc& planEvent) {
        return getInstance().addPlanEvent_(planEvent);
    }

    std::size_t PlanEvent::addPlanEvent_(const PlanFunc& planEvent) {
        planEvents_[nextId_] = planEvent;
        return nextId_++;
    }

    std::size_t PlanEvent::addPlanEvent_(const std::function<bool()>& condition, const PlanFunc& planEvent) {
        auto id = addPlanEvent_(planEvent);
        remove(id);
        std::function<void()>* func = new std::function<void()>();
        *func = [=, this] {
            condition()
                ? planEvent(), delete func
                : (void)getInstance().reAddPlanEvent_(id, *func);
            };
        return getInstance().reAddPlanEvent_(id, *func);
    }

    std::size_t PlanEvent::reAddPlanEvent_(std::size_t id, const PlanFunc& planEvent) {
        planEvents_[id] = planEvent;
        return id;
    }

    void PlanEvent::removePlanEvent_(std::size_t id) {
        planEvents_.erase(id);
    }

    std::size_t PlanEvent::addPlanEvent_(float after_ms, const PlanFunc& planEvent) {
        auto delay = std::chrono::milliseconds(static_cast<int>(after_ms));
        auto target = std::chrono::steady_clock::now() + delay;
        std::size_t id = addPlanEvent_(planEvent);
        remove(id);
        std::function<void()>* func = new std::function<void()>();
        *func = [=, this] {
            std::chrono::steady_clock::now() >= target
                ? planEvent(), delete func
                : (void)getInstance().reAddPlanEvent_(id, *func);
            };
        return getInstance().reAddPlanEvent_(id, *func);
    }

    std::size_t PlanEvent::add(float after, const PlanFunc& planEvent) {
        return getInstance().addPlanEvent_(after, planEvent);
    }

    std::size_t PlanEvent::add(const std::function<bool()>& condition, const PlanFunc& planEvent) {
        return getInstance().addPlanEvent_(condition, planEvent);
    }

    void PlanEvent::remove(std::size_t id) {
        getInstance().removePlanEvent_(id);
    }

    PlanEvent& PlanEvent::getInstance() {
        static PlanEvent instance;
        static bool initialized = false;
        if (!initialized) {
            initialized = true;
            Application::onEventCall.connect(&instance, &PlanEvent::executePlanEvents);
        }
        return instance;
    }

}