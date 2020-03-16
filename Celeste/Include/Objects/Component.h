#pragma once

#include "Entity.h"
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
      CelesteDllExport Component(GameObject& gameObject);
      CelesteDllExport ~Component() override;

      virtual void collisionEnter(Physics::Collider& /*collider*/) { }
      virtual void collision(Physics::Collider& /*collider*/) { }
      virtual void collisionExit(Physics::Collider& /*collider*/) { }
      virtual void triggerEnter(Physics::Collider& /*collider*/) { }
      virtual void trigger(Physics::Collider& /*collider*/) { }
      virtual void triggerExit(Physics::Collider& /*collider*/) { }

      inline GameObject* getGameObject() { return m_gameObject; }
      inline CelesteDllExport const GameObject* getGameObject() const { return const_cast<Component*>(this)->getGameObject(); }

      inline CelesteDllExport Transform* getTransform();
      inline CelesteDllExport const Transform* getTransform() const { return const_cast<Component*>(this)->getTransform(); }

    private:
      using Inherited = Entity;

      GameObject* m_gameObject = nullptr;
  };
}