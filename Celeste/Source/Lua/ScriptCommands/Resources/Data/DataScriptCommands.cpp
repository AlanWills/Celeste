#include "Lua/ScriptCommands/Resources/Data/DataScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Data/Data.h"

using Data = Celeste::Resources::Data;


namespace Celeste::Lua::Resources::DataScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Data>("Data");
  }
}