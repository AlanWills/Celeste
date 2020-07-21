#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/KeyScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsMouseTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEscape_ToMouseTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Escape"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Escape"].valid());
  }

#pragma endregion

  };
}