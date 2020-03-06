#include "Events/EventTriggerer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste
{
  REGISTER_UNMANAGED_COMPONENT(EventTriggerer, 10)

  //------------------------------------------------------------------------------------------------
  EventTriggerer::EventTriggerer(GameObject& gameObject) :
    Inherited(gameObject),
    m_triggerMode(TriggerMode::kOnce),
    m_condition(nullptr),
    m_event()
  {
  }

  //------------------------------------------------------------------------------------------------
  void EventTriggerer::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    if (m_condition && m_condition(*getGameObject()))
    {
      m_event.invoke(*getGameObject());

      if (m_triggerMode == TriggerMode::kOnce)
      {
        getGameObject()->removeComponent(this);
      }
    }
  }
}