#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/XML/tinyxml2ScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(Testtinyxml2ScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(tinyxml2ScriptCommands_Initialize_AddsXMLDocumentUserTypeToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLDocument"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLDocument"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_new_ToXMLDocumentTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLDocument"]["new"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLDocument"]["new"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_insertFirstChild_ToXMLDocumentTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLDocument"]["insertFirstChild"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLDocument"]["insertFirstChild"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_newElement_ToXMLDocumentTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLDocument"]["newElement"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLDocument"]["newElement"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_saveFile_ToXMLDocumentTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLDocument"]["saveFile"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLDocument"]["saveFile"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_AddsXMLNodeUserTypeToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLNode"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLNode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_AddsXMLElementUserTypeToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLElement"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLElement"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_findAttribute_ToXMLElementTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLElement"]["findAttribute"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLElement"]["findAttribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_setAttribute_ToXMLElementTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLElement"]["setAttribute"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLElement"]["setAttribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_AddsXMLAttributeUserTypeToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLAttribute"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLAttribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_asString_ToXMLAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLAttribute"]["asString"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLAttribute"]["asString"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(tinyxml2ScriptCommands_Initialize_Adds_asFloat_ToXMLAttributeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["XMLAttribute"]["asFloat"].valid());

    Celeste::Lua::XML::tinyxml2ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["XMLAttribute"]["asFloat"].valid());
  }

#pragma endregion

  };
}