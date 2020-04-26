#include "ScriptCommands/Maths/TransformScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
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
    void setWorldTranslation_vec3Overload(Transform& transform, const glm::vec3& worldTranslation)
    {
      transform.setWorldTranslation(worldTranslation);
    }

    //------------------------------------------------------------------------------------------------
    void translate_TwoFloatsOverload(Transform& transform, float xTranslation, float yTranslation)
    {
      transform.translate(xTranslation, yTranslation);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Transform>(
      state,
      Transform::type_name(),
      sol::base_classes, sol::bases<Object>(),
      "getWorldTranslation", &Transform::getWorldTranslation,
      "setWorldTranslation", &Internals::setWorldTranslation_vec3Overload,
      "translate", &Internals::translate_TwoFloatsOverload);
  }
}