#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Layout/LayoutSystemScriptCommands.h"
#include "Lua/LuaState.h"

#include "Layout/LayoutSystem.h"

using LuaState = Celeste::Lua::LuaState;
using LayoutSystem = Celeste::Layout::LayoutSystem;

using namespace Celeste;


namespace TestCeleste::Lua::Layout
{
  CELESTE_TEST_CLASS(TestLayoutSystemScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystemScriptCommands_Initialize_Adds_getLayoutSystem_ToSystemTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["System"]["getLayoutSystem"].valid());

    Celeste::Lua::Layout::LayoutSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["System"]["getLayoutSystem"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystemScriptCommands_Initialize_Adds_LayoutSystemTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["LayoutSystem"].valid());

    Celeste::Lua::Layout::LayoutSystemScriptCommands::initialize(state);

    Assert::IsTrue(state["LayoutSystem"].valid());
  }

#pragma endregion

  };
}