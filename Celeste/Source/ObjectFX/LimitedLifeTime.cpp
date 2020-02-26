#include "ObjectFX/LimitedLifeTime.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/InputManager.h"


namespace Celeste
{
  REGISTER_SCRIPT(LimitedLifeTime, 10)

  //------------------------------------------------------------------------------------------------
  LimitedLifeTime::LimitedLifeTime() :
    m_onDeathEvent()
  {
    Input::getKeyboard().getKeyReleasedEvent().subscribe(
      [this](int key)
      {
        onKeyUp(key);
      });
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTime::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    m_currentTimeAlive += elapsedGameTime;
    if (m_currentTimeAlive >= m_lifeTime)
    {
      observer_ptr<GameObject> gameObject = getGameObject();
      ASSERT_NOT_NULL(gameObject);

      if (gameObject)
      {
        getGameObject()->die();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTime::onDeath()
  {
    m_onDeathEvent.invoke(*getGameObject());

    Inherited::onDeath();

    Input::getKeyboard().getKeyReleasedEvent().unsubscribe(m_keyUpEvent);

    m_currentTimeAlive = 0;
    m_lifeTime = 0;
    m_triggerKey = -1;
    m_keyUpEvent = 0;
    m_onDeathEvent.unsubscribeAll();
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTime::onKeyUp(int key)
  {
    if (isActive() && key == m_triggerKey)
    {
      observer_ptr<GameObject> gameObject = getGameObject();
      ASSERT_NOT_NULL(gameObject);

      if (gameObject)
      {
        getGameObject()->die();
      }
    }
  }
}