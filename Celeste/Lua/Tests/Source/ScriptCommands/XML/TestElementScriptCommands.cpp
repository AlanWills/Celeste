#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/XML/ElementScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestElementScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ElementScriptCommands_Initialize_AddsElementUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Element"].valid());

    Celeste::Lua::XML::ElementScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Element"].valid());
  }

#pragma endregion

  };
}