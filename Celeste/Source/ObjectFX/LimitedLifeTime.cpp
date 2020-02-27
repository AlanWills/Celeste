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
  LimitedLifeTime::~LimitedLifeTime()
  {
    m_onDeathEvent.invoke(*getGameObject());
    Input::getKeyboard().getKeyReleasedEvent().unsubscribe(m_keyUpEvent);
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTime::update(GLfloat elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    m_currentTimeAlive += elapsedGameTime;
    if (m_currentTimeAlive >= m_lifeTime)
    {
      observer_ptr<GameObject> gameObject = getGameObject();
      ASSERT_NOT_NULL(gameObject);

      if (gameObject != nullptr)
      {
        getGameObject()->deallocate();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTime::onKeyUp(int key)
  {
    if (isActive() && key == m_triggerKey)
    {
      observer_ptr<GameObject> gameObject = getGameObject();
      ASSERT_NOT_NULL(gameObject);

      if (gameObject != nullptr)
      {
        getGameObject()->deallocate();
      }
    }
  }
}