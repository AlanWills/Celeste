#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/KeyScriptCommands.h"
#include "Lua/LuaState.h"
#include "GLFW/glfw3.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsMouseTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_Adds_isNumber_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["isNumber"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["isNumber"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_Adds_getNumber_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["getNumber"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["getNumber"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEscape_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Escape"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Escape"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsN_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["N"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["N"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum1_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num1"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num1"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum2_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num2"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num2"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum3_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num3"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num3"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum4_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num4"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num4"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum5_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num5"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num5"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum6_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num6"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num6"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum7_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num7"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num7"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum8_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num8"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num8"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum9_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num9"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num9"].valid());
  }

#pragma endregion

#pragma region Is Number Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingInvalidNumberKey_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    auto result = state["Key"]["isNumber"].get<sol::protected_function>().call(GLFW_KEY_A);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());

    result = state["Key"]["isNumber"].get<sol::protected_function>().call(GLFW_KEY_ESCAPE);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingValidNumberKey_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    for (size_t i = 0; i < 10; ++i)
    {
      auto result = state["Key"]["isNumber"].get<sol::protected_function>().call(static_cast<int>(GLFW_KEY_0 + i));

      Assert::IsTrue(result.valid());
      Assert::IsTrue(result.get<bool>());
    }
  }

#pragma endregion

#pragma region Get Number Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_getNumber_InputtingInvalidNumberKey_ReturnsMinusOne)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    auto result = state["Key"]["getNumber"].get<sol::protected_function>().call(GLFW_KEY_A);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-1, result.get<int>());

    result = state["Key"]["getNumber"].get<sol::protected_function>().call(GLFW_KEY_ESCAPE);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-1, result.get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingValidNumberKey_ReturnsCorrectNumber)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    for (size_t i = 0; i < 10; ++i)
    {
      auto result = state["Key"]["getNumber"].get<sol::protected_function>().call(static_cast<int>(GLFW_KEY_0 + i));

      Assert::IsTrue(result.valid());
      Assert::AreEqual(static_cast<int>(i), result.get<int>());
    }
  }

#pragma endregion

  };
}