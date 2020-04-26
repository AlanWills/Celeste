#include "ScriptCommands/Maths/MathsScriptCommands.h"
#include "ScriptCommands/Maths/VectorScriptCommands.h"
#include "ScriptCommands/Maths/TransformScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Maths::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    VectorScriptCommands::initialize(state);
    TransformScriptCommands::initialize(state);
  }
}