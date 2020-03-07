#include "Lua/ScriptCommands/Objects/EntityScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Objects/Entity.h"


namespace Celeste::Lua::EntityScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void destroy(Entity& entity)
    {
      delete& entity;
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Entity>("Entity",
      sol::base_classes, sol::bases<Object>(),
      "destroy", &Internals::destroy,
      "isActive", &Entity::isActive,
      "setActive", &Entity::setActive);
  }
}