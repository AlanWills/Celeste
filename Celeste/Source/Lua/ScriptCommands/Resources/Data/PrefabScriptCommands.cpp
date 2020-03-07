#include "Lua/ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Data/Prefab.h"

using Prefab = Celeste::Resources::Prefab;


namespace Celeste::Lua::Resources::PrefabScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Prefab>(
      "Prefab",
      "instantiate", &Prefab::instantiate);
  }
}