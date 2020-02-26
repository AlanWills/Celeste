#include "Lua/ScriptCommands/Objects/EntityScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Objects/Entity.h"


namespace Celeste::Lua::EntityScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Entity>("Entity",
      sol::base_classes, sol::bases<Object>(),
      "isActive", &Entity::isActive,
      "setActive", &Entity::setActive,
      "die", &Entity::die);
  }
}