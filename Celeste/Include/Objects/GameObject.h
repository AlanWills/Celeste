#pragma once

#include "Entity.h"
#include "StringId/string_id.h"
#include "Maths/Transform.h"
#include "Memory/Iterators/GameObjectIterator.h"
#include "UtilityMacros/CustomMemoryMacros.h"
#include "Templates/ComponentTypeTraits.h"

#include <vector>
#include <functional>


namespace Celeste
{
  class Component;

  namespace Physics
  {
    class Collider;
  }

  namespace Rendering
  {
    class SpriteBatch;
  }

  class GameObject : public Entity
  {
    CUSTOM_MEMORY_DECLARATION(GameObject, CelesteDllExport);

    public:
      CelesteDllExport GameObject();
      CelesteDllExport ~GameObject() override;

      /// Submit this gameobject for rendering into the inputted spritebatch
      CelesteDllExport void render(Rendering::SpriteBatch& spriteBatch, float lag);

      /// Called when a collider on the gameobject collides with a collider it was not in collision with last frame
      CelesteDllExport void collisionEnter(Physics::Collider& collider);

      /// Called when a collider on the gameobject collides with another collider this frame
      CelesteDllExport void collision(Physics::Collider& collider);

      /// Called when a collider on the gameobject has not collided with a collider it was in collision with last frame
      CelesteDllExport void collisionExit(Physics::Collider& collider);

      /// Called when a collider on the gameobject collides with a trigger it was not in collision with last frame
      CelesteDllExport void triggerEnter(Physics::Collider& collider);

      /// Called when a collider on the gameobject collides with another trigger this frame
      CelesteDllExport void trigger(Physics::Collider& collider);

      /// Called when a collider on the gameobject has not collided with a trigger it was in collision with last frame
      CelesteDllExport void triggerExit(Physics::Collider& collider);

      inline observer_ptr<Transform> getTransform() { return m_transform.get(); }
      inline observer_ptr<const Transform> getTransform() const { return const_cast<GameObject*>(this)->getTransform(); }

      inline observer_ptr<Transform> getParentTransform() { return m_transform->getParent(); }
      inline observer_ptr<const Transform> getParentTransform() const { return const_cast<GameObject*>(this)->getParentTransform(); }
      inline void setParentTransform(Transform* transform) { m_transform->setParent(transform); }
    
      inline CelesteDllExport GameObject* getParent()
      {
        Transform* transform = getParentTransform();
        return transform != nullptr ? transform->getGameObject() : nullptr;
      }
      inline CelesteDllExport const GameObject* getParent() const { return const_cast<GameObject*>(this)->getParent(); }
      inline void setParent(GameObject* gameObject) { setParentTransform(gameObject != nullptr ? gameObject->getTransform() : nullptr); }

      CelesteDllExport void setActive(bool isActive) override;

      inline void setName(const std::string& name) { m_name = string_id(name); }
      inline void setName(string_id name) { m_name = std::move(name); }
      inline string_id getName() const { return m_name; }

      inline size_t getChildCount() const { return m_transform != nullptr ? m_transform->getChildCount() : 0; }
      inline GameObject* getChild(size_t index) { return m_transform != nullptr ? m_transform->getChildGameObject(index) : nullptr; }
    
      CelesteDllExport GameObject* findChild(string_id name);
      GameObject* findChild(const std::string& name) { return findChild(string_id(name)); }

      inline GameObjectIterator begin() const { return m_transform != nullptr ? m_transform->begin() : GameObjectIterator(std::vector<Transform*>::const_iterator()); }
      inline GameObjectIterator end() const { return m_transform != nullptr ? m_transform->end() : GameObjectIterator(std::vector<Transform*>::const_iterator()); }

      /// Allocates and inserts the inputted component into the components associated with this game object
      /// If the component could not be allocated, it returns a null handle and the game object remains unchanged
      template <typename T>
      T* addComponent();

      /// Does not edit this instance, but allows us to enforce constness of handles by making this non-const
      template <typename T>
      T* findComponent();

      template <typename T>
      const T* findComponent() const { return const_cast<GameObject*>(this)->findComponent<T>(); }

      template <typename T>
      bool hasComponent() const;

      CelesteDllExport void removeComponent(Component* component);

      inline size_t getComponentCount() const { return m_unmanagedComponents.size() + m_managedComponents.size(); }
      CelesteDllExport Component* getComponent(size_t index);
      CelesteDllExport const Component* getConstComponent(size_t index) const { return const_cast<GameObject*>(this)->getComponent(index); }

      CelesteDllExport void update();

    private:
      using Inherited = Entity;

      std::unique_ptr<Transform> m_transform;

      string_id m_name;

      std::vector<Component*> m_managedComponents;
      std::vector<Component*> m_unmanagedComponents;

      friend class SceneManager;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T* GameObject::addComponent()
  {
    STATIC_ASSERT((std::is_base_of<Component, T>::value), "Inputted type does not derive from component");
    T* component = new T(*this);
  
#if _DEBUG
    if (component == nullptr)
    {
      ASSERT_FAIL_MSG("Component is nullptr");
      return component;
    }
#endif

    if constexpr (Celeste::is_managed_component<T>::value)
    {
      m_managedComponents.push_back(component);
    }
    else
    {
      m_unmanagedComponents.push_back(component);
    }

    return component;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T* GameObject::findComponent()
  {
    STATIC_ASSERT((std::is_base_of<Component, T>::value), "Inputted argument does not have component has an ancestor.");

    if constexpr (Celeste::is_managed_component<T>::value)
    {
      for (Component* managedComponent : m_managedComponents)
      {
        if (dynamic_cast<T*>(managedComponent) != nullptr)
        {
          return reinterpret_cast<T*>(managedComponent);
        }
      }
    }
    else
    {
      for (Component* unmanagedComponent : m_unmanagedComponents)
      {
        if (dynamic_cast<T*>(unmanagedComponent) != nullptr)
        {
          return reinterpret_cast<T*>(unmanagedComponent);
        }
      }
    }

    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool GameObject::hasComponent() const
  {
    if constexpr (Celeste::is_managed_component<T>::value)
    {
      for (Component* managedComponent : m_managedComponents)
      {
        if (dynamic_cast<T*>(managedComponent) != nullptr)
        {
          return true;
        }
      }
    }
    else
    {
      for (Component* unmanagedComponents : m_unmanagedComponents)
      {
        if (dynamic_cast<T*>(unmanagedComponents) != nullptr)
        {
          return true;
        }
      }
    }

    return false;
  }
}