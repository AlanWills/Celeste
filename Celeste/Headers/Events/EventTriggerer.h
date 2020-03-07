#pragma once

#include "CelesteDllExport.h"
#include "Objects/Component.h"
#include "Events/TriggerMode.h"
#include "Event.h"
#include "Input/Key.h"


namespace Celeste::Events
{
  class EventTriggerer : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(EventTriggerer, CelesteDllExport)

    public:
      using GameObjectEvent = Event<GameObject&>;
      using Condition = std::function<bool(GameObject&)>;

      inline const GameObjectEvent& getEvent() const { return m_event; }
      inline float getCurrentTriggerTimer() const { return m_currentTriggerTimer; }

      inline float getTriggerDelay() const { return m_triggerDelay; }
      inline void setTriggerDelay(float triggerDelay) { m_triggerDelay = triggerDelay; }

      inline int getTriggerKey() const { return m_triggerKey; }
      inline void setTriggerKey(int triggerKey) { m_triggerKey = triggerKey; }

      inline TriggerMode getTriggerMode() const { return m_triggerMode; }
      inline void setTriggerMode(TriggerMode triggerMode) { m_triggerMode = triggerMode; }

      inline void setTriggerCondition(const Condition& triggerCondition) { m_triggerCondition = triggerCondition; }

      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = Component;
      using GameObjectEvent = Event<GameObject&>;

      void invokeEvent();

      Event<GameObject&> m_event;

      TriggerMode m_triggerMode = TriggerMode::kOnce;
      Condition m_triggerCondition;
      float m_triggerDelay = FLT_MAX;
      float m_currentTriggerTimer = 0;
      int m_triggerKey = GLFW_KEY_UNKNOWN;
  };
}