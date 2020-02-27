#pragma once

#include "Entity.h"
#include "Memory/Allocators/EntityAllocator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "UtilityMacros/ComponentMacros.h"


namespace Celeste
{
  namespace Physics
  {
    class Collider;
  }

  class GameObject;
  class Transform;

  class Component : public Entity
  {
    public:
      CelesteDllExport Component();
      CelesteDllExport ~Component() override;

      virtual void collisionEnter(Physics::Collider& collider) { }
      virtual void collision(Physics::Collider& collider) { }
      virtual void collisionExit(Physics::Collider& collider) { }
      virtual void triggerEnter(Physics::Collider& collider) { }
      virtual void trigger(Physics::Collider& collider) { }
      virtual void triggerExit(Physics::Collider& collider) { }
      virtual bool deallocate() = 0;

      inline GameObject* getGameObject() { return m_gameObject; }
      inline CelesteDllExport const GameObject* getGameObject() const { return const_cast<Component*>(this)->getGameObject(); }

      inline CelesteDllExport Transform* getTransform();
      inline CelesteDllExport const Transform* getTransform() const { return const_cast<Component*>(this)->getTransform(); }

    protected:
      // Don't like this, but can't think of an alternative right now
      CelesteDllExport void setGameObject(GameObject& gameObject);

      /// Called after the parent is successfully set
      virtual void onSetGameObject(GameObject& parent) { }

    private:
      using Inherited = Entity;

      /// The handle of the game object which owns this component
      /// (Only class which inherited from GameObject can have components)
      GameObject* m_gameObject = nullptr;
  };
}