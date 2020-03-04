#pragma once

#include "Entity.h"
#include "UID/StringId.h"
#include "Component.h"
#include "Rendering/SpriteBatch.h"
#include "Maths/Transform.h"
#include "Memory/Iterators/GameObjectIterator.h"

#include <vector>
#include <functional>


namespace Celeste
{
  namespace Physics
  {
    class Collider;
  }

  class Screen;

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

      inline Transform* getTransform() { return m_transform; }
      inline const Transform* getTransform() const { return const_cast<GameObject*>(this)->getTransform(); }

      inline Transform* getParentTransform() { return m_transform != nullptr ? m_transform->getParent() : nullptr; }
      inline const Transform* getParentTransform() const { return const_cast<GameObject*>(this)->getParentTransform(); }
      inline void setParentTransform(Transform* transform) { if (m_transform != nullptr) { m_transform->setParent(transform); } }
    
      inline CelesteDllExport GameObject* getParent()
      {
        Transform* transform = getParentTransform();
        return transform != nullptr ? transform->getGameObject() : nullptr;
      }
      inline CelesteDllExport const GameObject* getParent() const { return const_cast<GameObject*>(this)->getParent(); }
      inline void setParent(GameObject* gameObject) { if (gameObject != nullptr) { setParentTransform(gameObject->getTransform()); } }

      CelesteDllExport void setActive(bool isActive) override;

      inline void setName(const std::string& name) { m_name = internString(name); }
      inline void setName(StringId name) { m_name = name; }
      inline StringId getName() const { return m_name; }

      inline void setTag(const std::string& tag) { m_tag = internString(tag); }
      inline void setTag(StringId tag) { m_tag = tag; }
      inline StringId getTag() const { return m_tag; }

      inline size_t getChildCount() const { return m_transform != nullptr ? m_transform->getChildCount() : 0; }
      inline Transform* getChildTransform(size_t index) { return m_transform != nullptr ? m_transform->getChildTransform(index) : nullptr; }
      inline GameObject* getChildGameObject(size_t index) { return m_transform != nullptr ? m_transform->getChildGameObject(index) : nullptr; }
    
      CelesteDllExport GameObject* findChildGameObject(StringId name);
      GameObject* findChildGameObject(const std::string& name) { return findChildGameObject(internString(name)); }

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

      /// Does not edit this instance, but allows us to enforce constness of handles by making this non-const
      template <typename T>
      T* findComponent(const std::function<bool(const T*)>& componentPredicate);

      template <typename T>
      const T* findComponent(const std::function<bool(const T*)>& componentPredicate) const { return const_cast<GameObject*>(this)->findComponent<T>(componentPredicate); }

      template <typename T>
      bool hasComponent() const;

      CelesteDllExport Component* removeComponent(Component* component);

      inline size_t getComponentCount() const { return getManagedComponentCount() + getUnmanagedComponentCount(); }
      CelesteDllExport Component* getComponent(size_t index);
      CelesteDllExport const Component* getConstComponent(size_t index) const { return const_cast<GameObject*>(this)->getComponent(index); }

      CelesteDllExport void handleInput();
      CelesteDllExport void update(GLfloat elapsedGameTime);

    protected:
      inline size_t getManagedComponentCount() const { return m_managedComponents.size(); }
      inline size_t getUnmanagedComponentCount() const { return m_unmanagedComponents.size(); }

    private:
      using Inherited = Entity;

      Transform* m_transform = nullptr;

      /// Name should be a unique identifier
      StringId m_name = 0;

      /// Tag can be applied to more than one game object for identifying a type of object
      StringId m_tag = 0;

      std::vector<Component*> m_managedComponents;
      std::vector<Component*> m_unmanagedComponents;
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

    if (Celeste::is_managed_component<T>::value)
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

    if (Celeste::is_managed_component<T>::value)
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
  T* GameObject::findComponent(const std::function<bool(const T*)>& componentPredicate)
  {
    STATIC_ASSERT((std::is_base_of<Component, T>::value), "Inputted argument does not have component has an ancestor.");

    if (Celeste::is_managed_component<T>::value)
    {
      for (Component* managedComponent : m_managedComponents)
      {
        if (dynamic_cast<T*>(managedComponent) != nullptr &&
          componentPredicate(reinterpret_cast<T*>(managedComponent)))
        {
          return reinterpret_cast<T*>(managedComponent);
        }
      }
    }
    else
    {
      for (Component* unmanagedComponent : m_unmanagedComponents)
      {
        if (dynamic_cast<T*>(unmanagedComponent) != nullptr &&
          componentPredicate(reinterpret_cast<T*>(unmanagedComponent)))
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
    if (Celeste::is_managed_component<T>::value)
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