#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Input/KeyboardVisibilityScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Input/KeyboardVisibility.h"
#include "Input/Utils/GlfwKeyConverter.h"

#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCelesteLua::Lua::Input::KeyboardVisibilityScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyboardVisibilityScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_KeyboardVisibilityUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getVisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getVisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getVisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setVisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setVisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setVisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getInvisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getInvisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getInvisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setInvisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setInvisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setInvisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getInputMode_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getInputMode"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setInputMode_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setInputMode"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_as_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["as"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["as"].valid());
  }

#pragma endregion

#pragma region Get Visibility Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetVisibilityKey_KeySetTo_GLFW_KEY_UNKNOWN_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setVisibilityKey(GLFW_KEY_UNKNOWN);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardVisibility.getVisibilityKey());

    auto result = state["KeyboardVisibility"]["getVisibilityKey"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetVisibilityKey_KeySetTo_ValidKey_ReturnsCorrectKeyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setVisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());

    auto result = state["KeyboardVisibility"]["getVisibilityKey"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("A", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Visibility Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetVisibilityKey_EmptyString_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setVisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());

    auto result = state["KeyboardVisibility"]["setVisibilityKey"].call(keyboardVisibility, "");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetVisibilityKey_InvalidKeyName_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setVisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());

    auto result = state["KeyboardVisibility"]["setVisibilityKey"].call(keyboardVisibility, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetVisibilityKey_ValidKeyName_SetsKeyToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setVisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getVisibilityKey());

    std::string keyName = Celeste::Input::GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_B);
    auto result = state["KeyboardVisibility"]["setVisibilityKey"].call(keyboardVisibility, keyName);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_B, keyboardVisibility.getVisibilityKey());
  }

#pragma endregion

#pragma region Get Invisibility Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetInvisibilityKey_KeySetTo_GLFW_KEY_UNKNOWN_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInvisibilityKey(GLFW_KEY_UNKNOWN);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardVisibility.getInvisibilityKey());

    auto result = state["KeyboardVisibility"]["getInvisibilityKey"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetInvisibilityKey_KeySetTo_ValidKey_ReturnsCorrectKeyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInvisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());

    auto result = state["KeyboardVisibility"]["getInvisibilityKey"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("A", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Invisibility Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInvisibilityKey_EmptyString_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInvisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());

    auto result = state["KeyboardVisibility"]["setInvisibilityKey"].call(keyboardVisibility, "");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInvisibilityKey_InvalidKeyName_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInvisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());

    auto result = state["KeyboardVisibility"]["setInvisibilityKey"].call(keyboardVisibility, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInvisibilityKey_ValidKeyName_SetsKeyToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInvisibilityKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardVisibility.getInvisibilityKey());

    std::string keyName = Celeste::Input::GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_B);
    auto result = state["KeyboardVisibility"]["setInvisibilityKey"].call(keyboardVisibility, keyName);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_B, keyboardVisibility.getInvisibilityKey());
  }

#pragma endregion

#pragma region Get Input Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetInputMode_kToggle_ReturnsToggle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardVisibility"]["getInputMode"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Toggle", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetInputMode_kContinuous_ReturnsContinuous)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInputMode(InputMode::kContinuous);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kContinuous);

    auto result = state["KeyboardVisibility"]["getInputMode"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Continuous", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set InputMode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInputMode_EmptyString_DoestNotChangeInputMode)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardVisibility"]["setInputMode"].call(keyboardVisibility, "");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInputMode_InvalidInputModeName_DoestNotChangeInputMode)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardVisibility"]["setInputMode"].call(keyboardVisibility, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetInputMode_ValidInputModeName_SetsInputModeToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    keyboardVisibility.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardVisibility"]["setInputMode"].call(keyboardVisibility, "Continuous");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kContinuous);
  }

#pragma endregion

#pragma region KeyboardVisibility As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToKeyboardVisibilityType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "KeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    class MockKeyboardVisibility : public Celeste::Input::KeyboardVisibility {};
    state.new_usertype<MockKeyboardVisibility>("MockKeyboardVisibility");

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "MockKeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibilityHandle_as_InputtingNullKeyboardVisibilityHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardVisibility == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToKeyboardVisibilityType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "KeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardVisibility == functionResult.get<KeyboardVisibility*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    class MockKeyboardVisibility : public Celeste::Input::KeyboardVisibility {};
    state.new_usertype<MockKeyboardVisibility>("MockKeyboardVisibility");

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "MockKeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    KeyboardVisibility keyboardVisibility(gameObject);
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}