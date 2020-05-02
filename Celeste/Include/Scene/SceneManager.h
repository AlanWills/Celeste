#pragma once

#include "CelesteStl/Memory/ObserverPtr.h"
#include "UID/StringId.h"
#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "System/ISystem.h"

#include <functional>


namespace Celeste
{
  class GameObject;

  class SceneManager : public System::ISystem
  {
    public:
      using FindGameObjectPredicate = std::function<bool(const GameObject&)>;

      CelesteDllExport SceneManager();
      CelesteDllExport ~SceneManager() override;

      // Do not want to allow copying of this object
      SceneManager(const SceneManager&) = delete;
      SceneManager& operator=(const SceneManager&) = delete;

      CelesteDllExport void update(float elapsedGameTime) override;

      CelesteDllExport observer_ptr<GameObject> find(const FindGameObjectPredicate& predicate);
      CelesteDllExport observer_ptr<GameObject> find(StringId name);
      observer_ptr<GameObject> find(const std::string& name) { return find(internString(name)); }
      CelesteDllExport observer_ptr<GameObject> findWithTag(StringId tag);
      observer_ptr<GameObject> findWithTag(const std::string& tag) { return findWithTag(internString(tag)); }

      CelesteDllExport std::vector<std::reference_wrapper<const GameObject>> getRootGameObjects() const;
      CelesteDllExport std::vector<std::reference_wrapper<GameObject>> getRootGameObjects();

    private:
      using Inherited = System::ISystem;

      void updateGameObjectHierarchy(GameObject& gameObject, float elapsedGameTime);
  };
}