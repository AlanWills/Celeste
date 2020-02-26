#include "Lua/ScriptCommands/Lua/Components/LuaComponentManifestRegistryScriptCommands.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::LuaComponentManifestRegistryScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = LuaState::instance();
    state.set_function("registerComponent", &Celeste::Lua::LuaComponentManifestRegistry::registerComponent);
  }
}