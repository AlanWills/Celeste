#include "Lua/ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "Lua/ScriptCommands/Settings/GameSettingsScriptCommands.h"
#include "Lua/ScriptCommands/Settings/WindowSettingsScriptCommands.h"
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
  void initialize()
  {
    Lua::LuaState::instance().new_usertype<ScriptableObject>(
      "ScriptableObject",
      "load", sol::factories(&Internals::loadScriptableObject),
      "delete", &Internals::deleteScriptableObject,
      "getName", &ScriptableObject::getName);

    Settings::GameSettingsScriptCommands::initialize();
    Settings::WindowSettingsScriptCommands::initialize();
  }
}