#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/CoreScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestCoreScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(CoreScriptCommands_Initialize_Adds_assert_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["assert"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_assertFail_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["assertFail"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_assertFailMessage_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["assertFailMessage"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_log_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["log"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_logWarning_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["logWarning"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_logError_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["logError"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_Adds_exit_ScriptCommand_ToGlobalTable)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["exit"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CoreScriptCommands_Initialize_RequiresLuaPathModule)
  {
    Celeste::Lua::Core::ScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["Core.FileSystem.Path"].valid());
  }

#pragma endregion

  };
}