#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/InputScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestInputScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestInputScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize(LuaState::instance());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InputScriptCommands_Initialize_InitializesMouseScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Mouse"].valid());

    Celeste::Lua::Input::ScriptCommands::initialize(state);

    Assert::IsTrue(state["Mouse"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InputScriptCommands_Initialize_InitializesKeyboardActivatorScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state["KeyboardActivator"].valid());

    Celeste::Lua::Input::ScriptCommands::initialize(state);

    Assert::IsTrue(state["KeyboardActivator"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InputScriptCommands_Initialize_InitializesKeyboardVisibilityScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state["KeyboardVisibility"].valid());

    Celeste::Lua::Input::ScriptCommands::initialize(state);

    Assert::IsTrue(state["KeyboardVisibility"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InputScriptCommands_Initialize_InitializesMouseInteractionHandlerScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state["MouseInteractionHandler"].valid());

    Celeste::Lua::Input::ScriptCommands::initialize(state);

    Assert::IsTrue(state["MouseInteractionHandler"].valid());
  }

#pragma endregion

  };
}