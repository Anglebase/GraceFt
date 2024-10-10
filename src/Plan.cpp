#include "Plan.h"
#include <Application.h>

namespace GFt {
    void PlanEvent::executePlanEvents() {
        for (auto& planEvent : planEvents_)
            planEvent();
        planEvents_.clear();
    }

    void PlanEvent::addPlanEvent(const PlanFunc& planEvent) {
        planEvents_.push_back(planEvent);
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