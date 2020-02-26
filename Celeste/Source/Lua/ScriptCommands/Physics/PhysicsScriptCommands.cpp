#include "Lua/ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "Lua/ScriptCommands/Physics/EllipseColliderScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Physics::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    EllipseColliderScriptCommands::initialize();
  }
}