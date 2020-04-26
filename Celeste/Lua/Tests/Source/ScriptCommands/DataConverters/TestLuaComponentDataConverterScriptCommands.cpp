#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/DataConverters/LuaComponentDataConverterScriptCommands.h"
#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"
#include "Lua/LuaState.h"

#include "AssertExt.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestLuaComponentDataConverterScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentDataConverterScriptCommands::testInitialize()
  {
    LuaComponentDataConverterRegistry::clear();
  }

  //------------------------------------------------------------------------------------------------
  void TestLuaComponentDataConverterScriptCommands::testCleanup()
  {
    LuaComponentDataConverterRegistry::clear();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterScriptCommands_Initialize_AddsLuaComponentDataConverterUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LuaComponentDataConverter"].valid());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterScriptCommands_Initialize_Adds_register_ToLuaComponentDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LuaComponentDataConverter"]["register"].valid());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"]["register"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterScriptCommands_Initialize_Adds_hasConverter_ToLuaComponentDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LuaComponentDataConverter"]["hasConverter"].valid());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"]["hasConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterScriptCommands_Initialize_Adds_getConverter_ToLuaComponentDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LuaComponentDataConverter"]["getConverter"].valid());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"]["getConverter"].valid());
  }

#pragma endregion

#pragma region Register Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Register_InputtingNonExistentName_ValidTable_AddsComponentToRegistry)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);
    state.globals()["LuaComponentDataConverter"]["register"]("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_Register_InputtingExistentName_ValidTable_DoesNothing)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);
    state.globals()["LuaComponentDataConverter"]["register"]("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());

    state.globals()["LuaComponentDataConverter"]["register"]("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

#pragma endregion

#pragma region Has Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_HasConverter_InputtingExistentName_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"]["hasConverter"]("Test").valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_HasConverter_InputtingNonExistentName_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"]["hasConverter"]("Test").valid());
  }

#pragma endregion

#pragma region Get Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_GetConverter_InputtingExistentName_CreatesInstanceOfConverter)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    Assert::IsNotNull(state.globals()["LuaComponentDataConverter"]["getConverter"]("Test").get<ComponentDataConverter*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverter_GetConverter_InputtingNonExistentName_DoesNothing)
  {
    sol::state& state = LuaState::instance();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    Celeste::Lua::LuaComponentDataConverterScriptCommands::initialize(state);

    auto result = state.globals()["LuaComponentDataConverter"]["getConverter"]("Test");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<void*>());
  }

#pragma endregion

  };
}