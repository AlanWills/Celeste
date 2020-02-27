#pragma once

#include "CelesteDllExport.h"
#include "Objects/Script.h"
#include "Event.h"


namespace Celeste
{
  class EventTriggerer : public Script
  {
    DECLARE_SCRIPT(EventTriggerer, CelesteDllExport)

    public:
      using GameObjectEvent = Event<GameObject&>;
      using Condition = std::function<bool(GameObject&)>;

      enum class TriggerMode
      {
        kOnce,
        kUnlimited
      };

      inline TriggerMode getTriggerMode() const { return m_triggerMode; }
      inline void setTriggerMode(TriggerMode triggerMode) { m_triggerMode = triggerMode; }

      inline const GameObjectEvent& getEvent() const { return m_event; }
      inline void setCondition(const Condition& condition) { m_condition = condition; }

      void update(float elapsedGameTime) override;

    private:
      using Inherited = Script;
      using GameObjectEvent = Event<GameObject&>;

      TriggerMode m_triggerMode;

      Event<GameObject&> m_event;
      Condition m_condition;
  };
}