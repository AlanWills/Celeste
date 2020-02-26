#include "Lua/ScriptCommands/ObjectFX/ObjectFXScriptCommands.h"
#include "Lua/ScriptCommands/ObjectFX/LimitedLifeTimeScriptCommands.h"


namespace Celeste::Lua::ObjectFXScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();
  }
}