#include "ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "ScriptCommands/Settings/GameSettingsScriptCommands.h"
#include "ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "Lua/LuaState.h"

#include "Settings/GameSettings.h"
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
    void deleteScriptableObject(std::unique_ptr<ScriptableObject>& scriptableObject)
    {
      scriptableObject.release();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<ScriptableObject>(
      "ScriptableObject",
      "load", sol::factories(&Internals::loadScriptableObject),
      "delete", &Internals::deleteScriptableObject,
      "getName", &ScriptableObject::getName);

    Settings::GameSettingsScriptCommands::initialize(state);
    Settings::WindowSettingsScriptCommands::initialize(state);
  }
}