#include "Lua/ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Data/Prefab.h"

using Prefab = Celeste::Resources::Prefab;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Prefab> : std::false_type {};
}

namespace Celeste::Lua::Resources::PrefabScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Prefab>(
      "Prefab",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>(),
      "instantiate", &Prefab::instantiate);
  }
}