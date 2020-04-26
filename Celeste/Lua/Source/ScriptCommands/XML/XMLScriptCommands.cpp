#include "ScriptCommands/XML/XMLScriptCommands.h"
#include "ScriptCommands/XML/XMLObjectScriptCommands.h"
#include "ScriptCommands/XML/AttributeScriptCommands.h"
#include "ScriptCommands/XML/ElementScriptCommands.h"
#include "ScriptCommands/XML/tinyxml2ScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::XML::XMLScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    tinyxml2ScriptCommands::initialize(state);
    XMLObjectScriptCommands::initialize(state);
    AttributeScriptCommands::initialize(state);
    ElementScriptCommands::initialize(state);
  }
}