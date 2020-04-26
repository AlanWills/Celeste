#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

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
  void initialize(sol::state& state)
  {
    registerUserType<Component>(
      state,
      "Component",
      sol::base_classes, sol::bases<Entity, Object>());
  }
}