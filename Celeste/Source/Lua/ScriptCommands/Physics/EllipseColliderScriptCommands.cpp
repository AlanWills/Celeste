#include "Lua/ScriptCommands/Physics/EllipseColliderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Physics/EllipseCollider.h"

using EllipseCollider = Celeste::Physics::EllipseCollider;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Physics::EllipseCollider> : std::false_type {};
}

namespace Celeste::Lua::Physics::EllipseColliderScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setDimensions_SingleRadius(Celeste::Physics::EllipseCollider& collider, float radius)
    {
      collider.setDimensions(radius);
    }

    //------------------------------------------------------------------------------------------------
    void setDimensions_XAndYSeparateFloatComponents(Celeste::Physics::EllipseCollider& collider, float xComponent, float yComponent)
    {
      collider.setDimensions(xComponent, yComponent);
    }

    //------------------------------------------------------------------------------------------------
    void setDimensions_Vec2Components(Celeste::Physics::EllipseCollider& collider, const glm::vec2& dimensions)
    {
      collider.setDimensions(dimensions);
    }

    //------------------------------------------------------------------------------------------------
    void setOffset_XAndYSeparateFloatComponents(Celeste::Physics::EllipseCollider& collider, float xOffset, float yOffset)
    {
      collider.setOffset(xOffset, yOffset);
    }

    //------------------------------------------------------------------------------------------------
    void setOffset_Vec2Components(Celeste::Physics::EllipseCollider& collider, const glm::vec2& offset)
    {
      collider.setOffset(offset);
    }

    //------------------------------------------------------------------------------------------------
    bool getIsTrigger(Celeste::Physics::EllipseCollider& ellipseCollider)
    {
      return ellipseCollider.getColliderType() == Celeste::Physics::ColliderType::kTrigger;
    }

    //------------------------------------------------------------------------------------------------
    void setIsTrigger(Celeste::Physics::EllipseCollider& ellipseCollider, bool isTrigger)
    {
      using ColliderType = Celeste::Physics::ColliderType;

      return ellipseCollider.setColliderType(isTrigger ? ColliderType::kTrigger : ColliderType::kCollider);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<EllipseCollider>(
      EllipseCollider::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getDimensions", &EllipseCollider::getDimensions,
      "setDimensions", sol::overload(
        &Internals::setDimensions_SingleRadius,
        &Internals::setDimensions_XAndYSeparateFloatComponents,
        &Internals::setDimensions_Vec2Components),
      "getOffset", &EllipseCollider::getOffset,
      "setOffset", sol::overload(
        &Internals::setOffset_XAndYSeparateFloatComponents,
        &Internals::setOffset_Vec2Components),
      "getIsTrigger", &Internals::getIsTrigger,
      "setIsTrigger", &Internals::setIsTrigger);
  }
}