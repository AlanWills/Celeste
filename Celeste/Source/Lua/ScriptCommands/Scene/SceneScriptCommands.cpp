#include "Lua/ScriptCommands/Scene/SceneScriptCommands.h"
#include "Lua/LuaState.h"
#include "Scene/SceneLoader.h"


namespace Celeste::Lua::Scene::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool load(const std::string& screenPath)
    {
      return std::get<0>(SceneLoader::load(screenPath));
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Celeste::Lua::LuaState::instance();
    state.create_named_table(
      "Scene", 
      "load", sol::factories(Internals::load));
  }
}