#include "ScriptCommands/Lua/Components/LuaComponentManifestRegistryScriptCommands.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::LuaComponentManifestRegistryScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.set_function("registerComponent", &Celeste::Lua::LuaComponentManifestRegistry::registerComponent);
  }
}