#include "TestUtils/TestUtils.h"
#include "ScriptCommands/System/SystemScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestSystem::Lua::ScriptCommands
{
  TEST_UTILS_TEST_CLASS(TestSystemScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SystemScriptCommands_initialize_AddsSystemTable_ToGlobalTable)
  {
    sol::state state;

    Assert::IsFalse(state["System"].valid());

    Celeste::Lua::System::ScriptCommands::initialize(state);

    Assert::IsTrue(state["System"].valid());
  }

#pragma endregion

};
}