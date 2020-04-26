#include "ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "ScriptCommands/Physics/EllipseColliderScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Physics::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    EllipseColliderScriptCommands::initialize(state);
  }
}