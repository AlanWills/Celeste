#include "ScriptCommands/Scene/SceneScriptCommands.h"
#include "Scene/SceneLoader.h"
#include "FileSystem/Path.h"
#include "sol/sol.hpp"


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
  void initialize(sol::state& state)
  {
    state.create_named_table(
      "Scene", 
      "load", sol::factories(Internals::load));
  }
}