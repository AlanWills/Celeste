#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Input/KeyboardVisibilityScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Input/MockKeyboardVisibility.h"

#include "Input/Utils/GlfwKeyConverter.h"
#include "Screens/Screen.h"

#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste::Lua::Input::KeyboardVisibilityScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyboardVisibilityScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_KeyboardVisibilityUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_allocate_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["allocate"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["allocate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getVisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getVisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getVisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setVisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setVisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setVisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getInvisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getInvisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getInvisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setInvisibilityKey_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setInvisibilityKey"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setInvisibilityKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getInputMode_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getInputMode"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setInputMode_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setInputMode"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setInputMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_getTarget_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["getTarget"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["getTarget"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_setTarget_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["setTarget"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["setTarget"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_Initialize_Adds_as_ToKeyboardVisibilityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["KeyboardVisibility"]["as"].valid());

    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["KeyboardVisibility"]["as"].valid());
  }

#pragma endregion

#pragma region Get Visibility Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetVisibilityKey_KeySetTo_GLFW_KEY_UNKNOWN_ReturnsEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
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
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
    keyboardVisibility.setInputMode(InputMode::kToggle);

    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kToggle);

    auto result = state["KeyboardVisibility"]["setInputMode"].call(keyboardVisibility, "Continuous");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(keyboardVisibility.getInputMode() == InputMode::kContinuous);
  }

#pragma endregion

#pragma region Get Target Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetTarget_TargetNull_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    KeyboardVisibility keyboardVisibility;
    keyboardVisibility.setTarget(nullptr);

    Assert::IsNull(keyboardVisibility.getTarget());

    auto result = state["KeyboardVisibility"]["getTarget"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<GameObject*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_GetTarget_TargetNotNull_ReturnsCorrectGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    GAMEOBJECT(gameObject);

    KeyboardVisibility keyboardVisibility;
    keyboardVisibility.setTarget(&gameObject);

    Assert::IsTrue(&gameObject == keyboardVisibility.getTarget());

    auto result = state["KeyboardVisibility"]["getTarget"].call(keyboardVisibility);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(&gameObject == result.get<GameObject*>());
  }

#pragma endregion

#pragma region Set Target Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetTarget_EmptyString_SetsTargetToNull)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject->addComponent<KeyboardVisibility>();
    keyboardVisibility->setTarget(gameObject.get());

    Assert::IsTrue(gameObject.get() == keyboardVisibility->getTarget());

    auto result = state["KeyboardVisibility"]["setTarget"].call(*keyboardVisibility, "");

    Assert::IsTrue(result.valid());
    Assert::IsNull(keyboardVisibility->getTarget());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetTarget_NonExistentGameObjectName_SetsTargetToNull)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

    observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject->addComponent<KeyboardVisibility>();
    keyboardVisibility->setTarget(gameObject.get());

    Assert::IsTrue(gameObject.get() == keyboardVisibility->getTarget());
    Assert::IsNull(screen.findGameObject("WubbaLubbaDubDub"));

    auto result = state["KeyboardVisibility"]["setTarget"].call(*keyboardVisibility, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsNull(keyboardVisibility->getTarget());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_SetTarget_ExistentGameObjectName_SetsTargetToCorrectGameObject)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<GameObject> target = screen.allocateGameObject();
    target->setName("Target");

    observer_ptr<KeyboardVisibility> keyboardVisibility = gameObject->addComponent<KeyboardVisibility>();
    keyboardVisibility->setTarget(gameObject.get());

    Assert::IsTrue(gameObject.get() == keyboardVisibility->getTarget());
    Assert::IsTrue(target.get() == screen.findGameObject("Target"));

    auto result = state["KeyboardVisibility"]["setTarget"].call(*keyboardVisibility, "Target");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(target.get(), keyboardVisibility->getTarget());
  }

#pragma endregion

#pragma region KeyboardVisibility As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToKeyboardVisibilityType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "KeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockKeyboardVisibility : public Celeste::Input::KeyboardVisibility {};
    state.new_usertype<MockKeyboardVisibility>("MockKeyboardVisibility");

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "MockKeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibilityHandle_as_InputtingNullKeyboardVisibilityHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    KeyboardVisibility keyboardVisibility;
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardVisibility == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToKeyboardVisibilityType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    KeyboardVisibility keyboardVisibility;
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "KeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&keyboardVisibility == functionResult.get<KeyboardVisibility*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockKeyboardVisibility : public Celeste::Input::KeyboardVisibility {};
    state.new_usertype<MockKeyboardVisibility>("MockKeyboardVisibility");

    KeyboardVisibility keyboardVisibility;
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "MockKeyboardVisibility");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    KeyboardVisibility keyboardVisibility;
    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(&keyboardVisibility, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardVisibilityScriptCommands_KeyboardVisibility_as_InputtingNonNullKeyboardVisibility_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Input::KeyboardVisibilityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["KeyboardVisibility"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}