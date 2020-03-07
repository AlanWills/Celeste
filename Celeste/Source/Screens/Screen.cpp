#include "Screens/Screen.h"
#include "Screens/ScreenManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  CUSTOM_MEMORY_CREATION(Screen, 10)

  //------------------------------------------------------------------------------------------------
  Screen::Screen() :
    m_name(0),
    m_gameObjectQueue()
  {
  }

  //------------------------------------------------------------------------------------------------
  Screen::~Screen() = default;

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput()
  {
    Inherited::handleInput();

    ASSERT(m_gameObjectQueue.empty());

    // Screen root has no game object so we have to do this part manually outside of the loop
    for (Transform* child : m_screenRoot)
    {
      GameObject* gameObject = child->getGameObject();

      if (gameObject->isActive())
      {
        m_gameObjectQueue.push(gameObject);
      }
    }

    while (!m_gameObjectQueue.empty())
    {
      GameObject* gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop();

      if (gameObject->isActive())
      {
        // Do another check here because sibling elements could have changed the activation status in their update call
        gameObject->handleInput();

        for (GameObject* child : *gameObject)
        {
          if (gameObject->isActive())
          {
            m_gameObjectQueue.push(child);
          }
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Screen::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    ASSERT(m_gameObjectQueue.empty());

    // Screen root has no game object so we have to do this part manually outside of the loop
    for (Transform* child : m_screenRoot)
    {
      GameObject* gameObject = child->getGameObject();
      
      if (gameObject->isActive())
      {
        m_gameObjectQueue.push(gameObject);
      }
    }

    while (!m_gameObjectQueue.empty())
    {
      GameObject* gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop();

      // Do another check here because sibling elements could have changed the activation status in their update call
      if (gameObject->isActive())
      {
        gameObject->update(elapsedGameTime);

        for (GameObject* child : *gameObject)
        {
          if (gameObject->isActive())
          {
            m_gameObjectQueue.push(child);
          }
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Screen::setActive(bool isActive)
  {
    Inherited::setActive(isActive);

    for (Transform* transform : m_screenRoot)
    {
      transform->getGameObject()->setActive(isActive);
    }
  }
}