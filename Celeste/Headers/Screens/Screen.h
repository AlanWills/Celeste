#pragma once

#include "FileSystem/Path.h"
#include "Objects/Entity.h"
#include "Objects/GameObject.h"
#include "Memory/Allocators/EntityAllocator.h"

#include <queue>


namespace Celeste
{
  class GameObject;

  class Screen : public Entity
  {
    COMPONENT_MEMORY(Screen)

    public:
      using FindGameObjectPredicate = std::function<bool(const GameObject&)>;

      CelesteDllExport static Screen* allocate() { return m_componentAllocator.allocate(); }
      CelesteDllExport static void deallocate(Screen& screen);

      CelesteDllExport Screen();
      Screen(const Screen&) = delete;
      CelesteDllExport ~Screen() = default;

      Screen& operator=(const Screen&) = delete;

      CelesteDllExport bool deallocate();
      CelesteDllExport bool deallocateGameObject(GameObject& gameObject);

      inline StringId getName() const { return m_name; }
      inline void setName(StringId name) { m_name = name; }
      inline void setName(const std::string& name) { m_name = internString(name); }

      CelesteDllExport void setActive(bool isActive) override;

      inline EntityAllocatorIterator<const GameObject> begin() const { return m_gameObjectAllocator.cbegin(); }
      inline EntityAllocatorIterator<const GameObject> end() const { return m_gameObjectAllocator.cend(); }
      
      inline const Transform& getScreenRoot() const { return m_screenRoot; }

      /// Allocates a new game object and sets its owner screen to be this instance
      CelesteDllExport GameObject* allocateGameObject();

      /// Allocates a new game object and sets its owner screen and transform parent to be this instance and the inputted transform
      CelesteDllExport GameObject* allocateGameObject(Transform& parentTransform);

      //------------------------------------------------------------------------------------------------
      /// Find Game Object
      GameObject* findGameObject(const FindGameObjectPredicate& predicate) { return m_gameObjectAllocator.find(predicate); }
      const GameObject* findGameObject(const FindGameObjectPredicate& predicate) const { return const_cast<Screen*>(this)->findGameObject(predicate); }

      //------------------------------------------------------------------------------------------------
      /// Find Game Object With Name
      CelesteDllExport GameObject* findGameObject(StringId name);
      GameObject* findGameObject(const std::string& name) { return findGameObject(internString(name)); }
      CelesteDllExport const GameObject* findGameObject(StringId name) const { return const_cast<Screen*>(this)->findGameObject(name); }
      const GameObject* findGameObject(const std::string& name) const { return findGameObject(internString(name)); }

      //------------------------------------------------------------------------------------------------
      /// Find Game Object With Tag
      CelesteDllExport GameObject* findGameObjectWithTag(StringId tag);
      GameObject* findGameObjectWithTag(const std::string& tag) { return findGameObjectWithTag(internString(tag)); }
      CelesteDllExport const GameObject* findGameObjectWithTag(StringId tag) const { return const_cast<Screen*>(this)->findGameObjectWithTag(tag); }
      const GameObject* findGameObjectWithTag(const std::string& tag) const { return findGameObjectWithTag(internString(tag)); }

      //------------------------------------------------------------------------------------------------
      /// Find Game Objects
      inline void findGameObjects(const FindGameObjectPredicate& predicate, std::vector<std::reference_wrapper<GameObject>>& foundGameObjects) { m_gameObjectAllocator.findAll(predicate, foundGameObjects); }
      std::vector<std::reference_wrapper<GameObject>> findGameObjects(const FindGameObjectPredicate& predicate)
      {
        std::vector<std::reference_wrapper<GameObject>> foundGO;
        findGameObjects(predicate, foundGO);
        return foundGO;
      }

      inline void findGameObjects(const FindGameObjectPredicate& predicate, std::vector<std::reference_wrapper<const GameObject>>& foundGameObjects) const { m_gameObjectAllocator.findAll(predicate, foundGameObjects); }
      std::vector<std::reference_wrapper<const GameObject>> findGameObjects(const FindGameObjectPredicate& predicate) const
      {
        std::vector<std::reference_wrapper<const GameObject>> foundGO;
        findGameObjects(predicate, foundGO);
        return foundGO;
      }

      //------------------------------------------------------------------------------------------------
      /// Find Game Objects With Tag
      CelesteDllExport void findGameObjectsWithTag(StringId tag, std::vector<std::reference_wrapper<GameObject>>& foundGameObjects);
      void findGameObjectsWithTag(const std::string& tag, std::vector<std::reference_wrapper<GameObject>>& foundGameObjects)
      {
        findGameObjectsWithTag(internString(tag), foundGameObjects);
      }

      std::vector<std::reference_wrapper<GameObject>> findGameObjectsWithTag(const std::string tag) { return findGameObjectsWithTag(internString(tag)); }
      std::vector<std::reference_wrapper<GameObject>> findGameObjectsWithTag(StringId tag)
      {
        std::vector<std::reference_wrapper<GameObject>> foundGO;
        findGameObjectsWithTag(tag, foundGO);
        return foundGO;
      }

      CelesteDllExport void findGameObjectsWithTag(StringId tag, std::vector<std::reference_wrapper<const GameObject>>& foundGameObjects) const;
      void findGameObjectsWithTag(const std::string& tag, std::vector<std::reference_wrapper<const GameObject>>& foundGameObjects) const
      {
        findGameObjectsWithTag(internString(tag), foundGameObjects);
      }

      std::vector<std::reference_wrapper<const GameObject>> findGameObjectsWithTag(const std::string tag) const { return findGameObjectsWithTag(internString(tag)); }
      std::vector<std::reference_wrapper<const GameObject>> findGameObjectsWithTag(StringId tag) const
      {
        std::vector<std::reference_wrapper<const GameObject>> foundGO;
        findGameObjectsWithTag(tag, foundGO);
        return foundGO;
      }
      //------------------------------------------------------------------------------------------------

    protected:
      CelesteDllExport void onHandleInput() override;
      CelesteDllExport void onUpdate(float elapsedGameTime) override;
      CelesteDllExport void onDeath() override;

    private:
      using Inherited = Entity;
      using GameObjectAllocator = EntityAllocator<GameObject>;

      GameObjectAllocator m_gameObjectAllocator;

      StringId m_name;
      Transform m_screenRoot;

      std::queue<GameObject*> m_gameObjectQueue;
      
      friend class ScreenManager;
  };
}