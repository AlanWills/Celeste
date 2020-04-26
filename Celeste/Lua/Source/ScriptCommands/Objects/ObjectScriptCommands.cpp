#include "ScriptCommands/Objects/ObjectScriptCommands.h"
#include "ScriptCommands/Objects/EntityScriptCommands.h"
#include "ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Objects/Object.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Objects::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Object>(state, "Object");

    ScriptableObjectScriptCommands::initialize(state);
    EntityScriptCommands::initialize(state);
    ComponentScriptCommands::initialize(state);
    GameObjectScriptCommands::initialize(state);
  }
}