#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Layout/LayoutScriptCommands.h"
#include "Lua/LuaState.h"

#include "Layout/ResolutionScaler.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;


namespace TestCeleste::Lua::Layout
{
  CELESTE_TEST_CLASS(TestLayoutScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutScriptCommands_Initialize_InitializesLayoutSystemScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["LayoutSystem"].valid());

    Celeste::Lua::Layout::ScriptCommands::initialize(state);

    Assert::IsTrue(state["LayoutSystem"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutScriptCommands_Initialize_InitializesResolutionScalerScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Celeste::Layout::ResolutionScaler::type_name()].valid());

    Celeste::Lua::Layout::ScriptCommands::initialize(state);

    Assert::IsTrue(state[Celeste::Layout::ResolutionScaler::type_name()].valid());
  }

#pragma endregion

  };
}