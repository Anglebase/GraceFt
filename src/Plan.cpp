#include "Plan.h"
#include <Application.h>

namespace GFt {
    void PlanEvent::executePlanEvents() {
        std::list<PlanFunc> calls;
        calls.swap(planEvents_);
        planEvents_.clear();
        for (auto& planEvent : calls)
            planEvent();
    }

    void PlanEvent::addPlanEvent(const PlanFunc& planEvent) {
        planEvents_.push_back(planEvent);
    }

    void PlanEvent::addPlanEvent(float after_ms, const PlanFunc& planEvent) {
        auto delay = std::chrono::milliseconds(static_cast<int>(after_ms));
        auto target = std::chrono::steady_clock::now() + delay;
        std::function<void()>* func = new std::function<void()>();
        *func = [=, this] {
            std::chrono::steady_clock::now() >= target
                ? planEvent(), delete func
                : addPlanEvent(*func);
            };
        addPlanEvent(*func);
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