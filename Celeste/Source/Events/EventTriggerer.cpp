#include "Events/EventTriggerer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/InputUtils.h"
#include "Input/Keyboard.h"


namespace Celeste::Events
{
  REGISTER_UNMANAGED_COMPONENT(EventTriggerer, 10)

  //------------------------------------------------------------------------------------------------
  EventTriggerer::EventTriggerer(GameObject& gameObject) :
    Inherited(gameObject),
    m_event(),
    m_triggerCondition(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  void EventTriggerer::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    m_currentTriggerTimer += elapsedGameTime;

    if ((m_triggerCondition && m_triggerCondition(*getGameObject())) ||
        Input::getKeyboard().isKeyTapped(m_triggerKey) ||
        (m_currentTriggerTimer >= m_triggerDelay))
    {
      invokeEvent();
    }
  }

  //------------------------------------------------------------------------------------------------
  void EventTriggerer::invokeEvent()
  {
    m_currentTriggerTimer = 0;

    GameObject* gameObject = getGameObject();
    if (m_triggerMode == TriggerMode::kOnce)
    {
      gameObject->removeComponent(this);
    }

    m_event.invoke(*gameObject);
  }
}