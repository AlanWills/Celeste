#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Registries/ComponentRegistry.h"
#include "Objects/Component.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Component> : std::false_type {};
}

namespace Celeste::Lua::ComponentScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Component>(
      "Component",
      sol::base_classes, sol::bases<Entity, Object>());
  }
}