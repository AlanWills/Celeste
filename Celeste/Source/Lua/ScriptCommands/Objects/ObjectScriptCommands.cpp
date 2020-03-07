#include "Lua/ScriptCommands/Objects/ObjectScriptCommands.h"
#include "Lua/ScriptCommands/Objects/EntityScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Objects/Object.h"


namespace Celeste::Lua::Objects::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Object>("Object");

    ScriptableObjectScriptCommands::initialize();
    EntityScriptCommands::initialize();
    ComponentScriptCommands::initialize();
    GameObjectScriptCommands::initialize();
  }
}