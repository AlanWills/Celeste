#include "Lua/ScriptCommands/Maths/TransformScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Maths/Transform.h"


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
  void initialize()
  {
    registerUserType<Transform>(
      Transform::type_name(),
      sol::base_classes, sol::bases<Object>(),
      "getWorldTranslation", &Transform::getWorldTranslation,
      "setWorldTranslation", &Internals::setWorldTranslation_vec3Overload,
      "translate", &Internals::translate_TwoFloatsOverload);
  }
}