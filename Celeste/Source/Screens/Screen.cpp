#include "Screens/Screen.h"
#include "Screens/ScreenManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  // Declare static variables
  COMPONENT_MEMORY_CREATION(Screen, 10)

  //------------------------------------------------------------------------------------------------
  Screen::Screen() :
    m_name(0),
    m_gameObjectAllocator(30),
    m_screenRoot(),
    m_gameObjectQueue()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Screen::onHandleInput()
  {
    Inherited::onHandleInput();

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
  void Screen::onUpdate(float elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

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
  void Screen::onDeath()
  {
    Inherited::onDeath();

    m_name = 0;

    // Reset scene root transform (in case it's been changed)
    // Don't just assign a new transform here as we'll lose references to children
    m_screenRoot.setRotation(0);
    m_screenRoot.setTranslation(0, 0, 0);
    m_screenRoot.setScale(0, 0, 0);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::deallocate(Screen& screen)
  {
    if (m_componentAllocator.isAllocated(screen))
    {
      screen.deallocate();
    }
  }

  //------------------------------------------------------------------------------------------------
  bool Screen::deallocate()
  {
    // This also deallocates the game objects
    // Call this here rather than die, so that objects are not instantly killed when a screen dies
    // This allows us to kill screens using events
    m_gameObjectAllocator.die();

    ASSERT(m_gameObjectQueue.empty());
    return m_componentAllocator.deallocate(*this);
  }

  //------------------------------------------------------------------------------------------------
  bool Screen::deallocateGameObject(GameObject& gameObject)
  {
    return m_gameObjectAllocator.deallocate(gameObject);
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

  //------------------------------------------------------------------------------------------------
  GameObject* Screen::allocateGameObject()
  {
    GameObject* gameObject = m_gameObjectAllocator.allocate();
    gameObject->getTransform()->setParent(&m_screenRoot);
    gameObject->m_screen = this;
    
    return gameObject;
  }

  //------------------------------------------------------------------------------------------------
  GameObject* Screen::allocateGameObject(Transform& parentTransform)
  {
    GameObject* gameObject = allocateGameObject();

    ASSERT(gameObject->getTransform() != nullptr);
    gameObject->getTransform()->setParent(&parentTransform);

    return gameObject;
  }

  //------------------------------------------------------------------------------------------------
  GameObject* Screen::findGameObjectWithTag(StringId tag)
  {
    return findGameObject([tag](const GameObject& gameObject)
    {
      return gameObject.getTag() == tag;
    });
  }

  //------------------------------------------------------------------------------------------------
  GameObject* Screen::findGameObject(StringId name)
  {
    return findGameObject([name](const GameObject& gameObject)
    {
      return gameObject.getName() == name;
    });
  }

  //------------------------------------------------------------------------------------------------
  void Screen::findGameObjectsWithTag(StringId tag, std::vector<std::reference_wrapper<GameObject>>& foundGameObjects)
  {
    findGameObjects(
      [tag](const GameObject& gameObject)
      {
        return gameObject.getTag() == tag;
      }, foundGameObjects);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::findGameObjectsWithTag(StringId tag, std::vector<std::reference_wrapper<const GameObject>>& foundGameObjects) const
  {
    findGameObjects(
      [tag](const GameObject& gameObject)
    {
      return gameObject.getTag() == tag;
    }, foundGameObjects);
  }
}