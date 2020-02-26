#include "Events/EventTriggerer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste
{
  REGISTER_SCRIPT(EventTriggerer, 10)

  //------------------------------------------------------------------------------------------------
  EventTriggerer::EventTriggerer() :
    m_triggerMode(TriggerMode::kOnce),
    m_condition(nullptr),
    m_event()
  {
  }

  //------------------------------------------------------------------------------------------------
  void EventTriggerer::onUpdate(float elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    if (m_condition && m_condition(*getGameObject()))
    {
      m_event.invoke(*getGameObject());

      if (m_triggerMode == TriggerMode::kOnce)
      {
        die();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void EventTriggerer::onDeath()
  {
    Inherited::onDeath();

    m_triggerMode = TriggerMode::kOnce;
    m_condition = nullptr;
    m_event.unsubscribeAll();
  }
}