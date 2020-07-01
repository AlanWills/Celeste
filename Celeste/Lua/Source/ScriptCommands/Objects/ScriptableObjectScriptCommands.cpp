#include "ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "ScriptCommands/Settings/GameSettingsScriptCommands.h"
#include "Lua/LuaState.h"

#include "Registries/ScriptableObjectRegistry.h"


namespace Celeste::Lua::ScriptableObjectScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    sol::object loadScriptableObject(const std::string& pathToFile)
    {
      return sol::make_object(LuaState::instance(), ScriptableObject::load(pathToFile));
    }

    //------------------------------------------------------------------------------------------------
    void destroyScriptableObject(std::unique_ptr<ScriptableObject>& scriptableObject)
    {
      scriptableObject.reset();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<ScriptableObject>(
      "ScriptableObject",
      "load", sol::factories(&Internals::loadScriptableObject),
      "destroy", &Internals::destroyScriptableObject,
      "getName", &ScriptableObject::getName);

    Settings::GameSettingsScriptCommands::initialize(state);
  }
}