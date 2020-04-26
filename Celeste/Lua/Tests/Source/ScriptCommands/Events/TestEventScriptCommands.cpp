#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestEventScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsScriptCommands_Initialize_InitializesEventTriggererScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()["EventTriggerer"].valid());

    Celeste::Lua::Events::ScriptCommands::initialize(LuaState::instance());

    Assert::IsTrue(LuaState::instance()["EventTriggerer"].valid());
  }

#pragma endregion

  };
}