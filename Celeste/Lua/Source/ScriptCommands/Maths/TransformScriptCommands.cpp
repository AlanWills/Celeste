#include "ScriptCommands/Maths/TransformScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Maths/Transform.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Transform> : std::false_type {};
}

namespace Celeste::Lua::Maths::TransformScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setTranslation_TwoFloatsOverload(Transform& transform, float xTranslation, float yTranslation)
    {
      transform.setTranslation(xTranslation, yTranslation);
    }
    //------------------------------------------------------------------------------------------------
    void setWorldTranslation_vec3Overload(Transform& transform, const glm::vec3& worldTranslation)
    {
      transform.setWorldTranslation(worldTranslation);
    }

    //------------------------------------------------------------------------------------------------
    void translate_TwoFloatsOverload(Transform& transform, float xTranslation, float yTranslation)
    {
      transform.translate(xTranslation, yTranslation);
    }

    //------------------------------------------------------------------------------------------------
    void setScale_TwoFloatsOverload(Transform& transform, float xScale, float yScale)
    {
      transform.setScale(xScale, yScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Transform>(
      state,
      Transform::type_name(),
      sol::base_classes, sol::bases<Object>(),
      "setTranslation", sol::overload(&Internals::setTranslation_TwoFloatsOverload),
      "getWorldTranslation", &Transform::getWorldTranslation,
      "setWorldTranslation", &Internals::setWorldTranslation_vec3Overload,
      "translate", &Internals::translate_TwoFloatsOverload,
      "setScale", sol::overload(&Internals::setScale_TwoFloatsOverload));
  }
}