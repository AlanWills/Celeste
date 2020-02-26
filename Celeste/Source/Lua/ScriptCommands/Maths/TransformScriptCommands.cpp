#include "Lua/ScriptCommands/Maths/TransformScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Maths/Transform.h"


namespace Celeste::Lua::Maths::TransformScriptCommands
{
  namespace Internals
  {
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
      "allocate", sol::factories(&Transform::allocate),
      "translate", &Internals::translate_TwoFloatsOverload);
  }
}