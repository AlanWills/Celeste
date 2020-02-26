#include "Lua/ScriptCommands/XML/XMLScriptCommands.h"
#include "Lua/ScriptCommands/XML/XMLObjectScriptCommands.h"
#include "Lua/ScriptCommands/XML/AttributeScriptCommands.h"
#include "Lua/ScriptCommands/XML/ElementScriptCommands.h"
#include "Lua/ScriptCommands/XML/tinyxml2ScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::XML::XMLScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    tinyxml2ScriptCommands::initialize();
    XMLObjectScriptCommands::initialize();
    AttributeScriptCommands::initialize();
    ElementScriptCommands::initialize();
  }
}