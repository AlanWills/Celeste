#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Maths/MathsScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::Maths::ScriptCommands
{
  CELESTE_TEST_CLASS(TestMathsScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MathsScriptCommands_Initialize_InitializesVectorScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["uvec2"].valid());

    Celeste::Lua::Maths::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["uvec2"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MathsScriptCommands_Initialize_InitializesTransformScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"].valid());

    Celeste::Lua::Maths::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"].valid());
  }

#pragma endregion

  };
}