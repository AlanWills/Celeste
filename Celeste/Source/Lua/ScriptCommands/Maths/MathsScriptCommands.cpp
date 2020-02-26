#include "Lua/ScriptCommands/Maths/MathsScriptCommands.h"
#include "Lua/ScriptCommands/Maths/VectorScriptCommands.h"
#include "Lua/ScriptCommands/Maths/TransformScriptCommands.h"


namespace Celeste::Lua::Maths::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    VectorScriptCommands::initialize();
    TransformScriptCommands::initialize();
  }
}