#include "Scene/SceneManager.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  SceneManager::SceneManager() = default;

  //------------------------------------------------------------------------------------------------
  SceneManager::~SceneManager()
  {
    GameObject::m_allocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void SceneManager::update(float /*elapsedGameTime*/)
  {
    for (GameObject& gameObject : getRootGameObjects())
    {
      updateGameObjectHierarchy(gameObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  void SceneManager::updateGameObjectHierarchy(GameObject& gameObject)
  {
    if (gameObject.isActive())
    {
      gameObject.update();

      for (size_t i = 0; i < gameObject.getChildCount(); ++i)
      {
        updateGameObjectHierarchy(*gameObject.getChild(i));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  GameObject* SceneManager::find(const FindGameObjectPredicate& predicate)
  {
    for (auto& gameObject : GameObject::m_allocator)
    {
      if (predicate(gameObject))
      {
        return &gameObject;
      }
    }

    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  GameObject* SceneManager::findWithTag(StringId tag)
  {
    return find([tag](const GameObject& gameObject)
      {
        return gameObject.getTag() == tag;
      });
  }

  //------------------------------------------------------------------------------------------------
  GameObject* SceneManager::find(StringId name)
  {
    return find([name](const GameObject& gameObject)
      {
        return gameObject.getName() == name;
      });
  }

  //------------------------------------------------------------------------------------------------
  std::vector<std::reference_wrapper<GameObject>> SceneManager::getRootGameObjects()
  {
    std::vector<std::reference_wrapper<GameObject>> rootGameObjects;

    for (GameObject& gameObject : GameObject::m_allocator)
    {
      if (gameObject.getParentTransform() == nullptr)
      {
        rootGameObjects.emplace_back(gameObject);
      }
    }

    return rootGameObjects;
  }

  //------------------------------------------------------------------------------------------------
  std::vector<std::reference_wrapper<const GameObject>> SceneManager::getRootGameObjects() const
  {
    std::vector<std::reference_wrapper<const GameObject>> rootGameObjects;

    for (const GameObject& gameObject : GameObject::m_allocator)
    {
      if (gameObject.getParentTransform() == nullptr)
      {
        rootGameObjects.emplace_back(gameObject);
      }
    }

    return rootGameObjects;
  }
}