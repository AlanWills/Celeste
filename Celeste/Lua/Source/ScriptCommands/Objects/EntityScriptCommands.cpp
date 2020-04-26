#include "ScriptCommands/Objects/EntityScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Objects/Entity.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Entity> : std::false_type {};
}

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
  void initialize(sol::state& state)
  {
    registerUserType<Entity>(
      state,
      "Entity",
      sol::base_classes, sol::bases<Object>(),
      "destroy", &Internals::destroy,
      "isActive", &Entity::isActive,
      "setActive", &Entity::setActive);
  }
}