#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/XML/XMLScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestXMLScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(XMLScriptCommands_Initialize_InitializesXMLObjectScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLObject"].valid());

    Celeste::Lua::XML::XMLScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(XMLScriptCommands_Initialize_InitializesAttributeScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Attribute"].valid());

    Celeste::Lua::XML::XMLScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Attribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(XMLScriptCommands_Initialize_InitializesElementScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Element"].valid());

    Celeste::Lua::XML::XMLScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Element"].valid());
  }

#pragma endregion

  };
}