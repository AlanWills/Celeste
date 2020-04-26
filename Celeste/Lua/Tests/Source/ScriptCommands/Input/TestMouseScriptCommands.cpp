#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/MouseScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestMouseScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseScriptCommands_Initialize_Adds_setCursor_ToMouseTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Mouse"]["setCursor"].valid());

    Celeste::Lua::Input::MouseScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Mouse"]["setCursor"].valid());
  }

#pragma endregion

  };
}