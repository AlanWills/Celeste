#include "ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

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
  void initialize(sol::state& state)
  {
    registerUserType<Prefab>(
      state,
      "Prefab",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>(),
      "instantiate", &Prefab::instantiate);
  }
}