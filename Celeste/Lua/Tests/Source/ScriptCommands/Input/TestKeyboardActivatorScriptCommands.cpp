#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Input/KeyboardActivatorScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Input/KeyboardActivator.h"
#include "Input/Utils/GlfwKeyConverter.h"

#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Input;


namespace TestCelesteLua::Lua::Input::KeyboardActivatorScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyboardActivatorScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_KeyboardActivatorUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_getActivationKey_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["getActivationKey"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["getActivationKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_setActivationKey_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["setActivationKey"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["setActivationKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_getDeactivationKey_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["getDeactivationKey"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["getDeactivationKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_setDeactivationKey_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["setDeactivationKey"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["setDeactivationKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_getInputMode_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["getInputMode"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["getInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_setInputMode_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["setInputMode"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["setInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_Initialize_Adds_as_ToKeyboardActivatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardActivator"]["as"].valid());

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["KeyboardActivator"]["as"].valid());
  }

#pragma endregion

#pragma region Get Activation Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetActivationKey_KeySetTo_GLFW_KEY_UNKNOWN_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setActivationKey(GLFW_KEY_UNKNOWN);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardActivator.getActivationKey());

    auto result = state["KeyboardActivator"]["getActivationKey"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetActivationKey_KeySetTo_ValidKey_ReturnsCorrectKeyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setActivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());

    auto result = state["KeyboardActivator"]["getActivationKey"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("A", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Activation Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetActivationKey_EmptyString_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setActivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());

    auto result = state["KeyboardActivator"]["setActivationKey"].call(keyboardActivator, "");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetActivationKey_InvalidKeyName_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setActivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());

    auto result = state["KeyboardActivator"]["setActivationKey"].call(keyboardActivator, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetActivationKey_ValidKeyName_SetsKeyToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setActivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getActivationKey());

    std::string keyName = Celeste::Input::GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_B);
    auto result = state["KeyboardActivator"]["setActivationKey"].call(keyboardActivator, keyName);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_B, keyboardActivator.getActivationKey());
  }

#pragma endregion

#pragma region Get Deactivation Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetDeactivationKey_KeySetTo_GLFW_KEY_UNKNOWN_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setDeactivationKey(GLFW_KEY_UNKNOWN);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, keyboardActivator.getDeactivationKey());

    auto result = state["KeyboardActivator"]["getDeactivationKey"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetDeactivationKey_KeySetTo_ValidKey_ReturnsCorrectKeyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setDeactivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());

    auto result = state["KeyboardActivator"]["getDeactivationKey"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("A", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Deactivation Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetDeactivationKey_EmptyString_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setDeactivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());

    auto result = state["KeyboardActivator"]["setDeactivationKey"].call(keyboardActivator, "");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetDeactivationKey_InvalidKeyName_DoestNotChangeKey)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setDeactivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());

    auto result = state["KeyboardActivator"]["setDeactivationKey"].call(keyboardActivator, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetDeactivationKey_ValidKeyName_SetsKeyToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setDeactivationKey(GLFW_KEY_A);

    Assert::AreEqual(GLFW_KEY_A, keyboardActivator.getDeactivationKey());

    std::string keyName = Celeste::Input::GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_B);
    auto result = state["KeyboardActivator"]["setDeactivationKey"].call(keyboardActivator, keyName);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_B, keyboardActivator.getDeactivationKey());
  }

#pragma endregion

#pragma region Get Input Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetInputMode_kToggle_ReturnsToggle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardActivator"]["getInputMode"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Toggle", result.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_GetInputMode_kContinuous_ReturnsContinuous)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setInputMode(InputMode::kContinuous);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kContinuous);

    auto result = state["KeyboardActivator"]["getInputMode"].call(keyboardActivator);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("Continuous", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set InputMode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetInputMode_EmptyString_DoestNotChangeInputMode)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardActivator"]["setInputMode"].call(keyboardActivator, "");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetInputMode_InvalidInputModeName_DoestNotChangeInputMode)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardActivator"]["setInputMode"].call(keyboardActivator, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_SetInputMode_ValidInputModeName_SetsInputModeToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    keyboardActivator.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardActivator"]["setInputMode"].call(keyboardActivator, "Continuous");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardActivator.getInputMode() == InputMode::kContinuous);
  }

#pragma endregion

#pragma region KeyboardActivator As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNull_CastingToKeyboardActivatorType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "KeyboardActivator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    class MockKeyboardActivator : public Celeste::Input::KeyboardActivator {};
    state.new_usertype<MockKeyboardActivator>("MockKeyboardActivator");

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "MockKeyboardActivator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivatorHandle_as_InputtingNullKeyboardActivatorHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNonNullKeyboardActivator_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(&keyboardActivator, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardActivator == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNonNullKeyboardActivator_CastingToKeyboardActivatorType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(&keyboardActivator, "KeyboardActivator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardActivator == functionResult.get<KeyboardActivator*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNonNullKeyboardActivator_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    class MockKeyboardActivator : public Celeste::Input::KeyboardActivator {};
    state.new_usertype<MockKeyboardActivator>("MockKeyboardActivator");

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(&keyboardActivator, "MockKeyboardActivator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNonNullKeyboardActivator_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    KeyboardActivator keyboardActivator(gameObject);
    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(&keyboardActivator, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardActivatorScriptCommands_KeyboardActivator_as_InputtingNonNullKeyboardActivator_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::KeyboardActivatorScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardActivator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}