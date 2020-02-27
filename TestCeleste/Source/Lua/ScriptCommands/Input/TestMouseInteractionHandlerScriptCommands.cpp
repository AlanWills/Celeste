#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Input/MouseInteractionHandlerScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Screens/Screen.h"
#include "Input/MouseInteractionHandler.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;
using namespace Celeste::Input;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestMouseInteractionHandlerScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_MouseInteractionHandlerUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_allocate_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["allocate"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["allocate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnLeftButtonUpCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnRightButtonUpCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnEnterCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnEnterCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnEnterCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnLeaveCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnLeaveCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnLeaveCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_as_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["as"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["as"].valid());
  }

#pragma endregion

#pragma region Subscribe On Left Button Up Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnLeftButtonUpCallback_InputtingInvalidFunction_DoesNotRegisterCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function;
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsFalse(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeftButtonUpEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeftButtonUpEvent().getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnLeftButtonUpCallback_InputtingValidFunction_RegistersCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function = state["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].get<sol::function>();
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsTrue(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeftButtonUpEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), mouseInteractionHandler->getOnLeftButtonUpEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Subscribe On Right Button Up Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnRightButtonUpCallback_InputtingInvalidFunction_DoesNotRegisterCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function;
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsFalse(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnRightButtonUpEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnRightButtonUpEvent().getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnRightButtonUpCallback_InputtingValidFunction_RegistersCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function = state["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].get<sol::function>();
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsTrue(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnRightButtonUpEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), mouseInteractionHandler->getOnRightButtonUpEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Subscribe On Enter Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnEnterCallback_InputtingInvalidFunction_DoesNotRegisterCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function;
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsFalse(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnEnterEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnEnterCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnEnterEvent().getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnEnterCallback_InputtingValidFunction_RegistersCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function = state["MouseInteractionHandler"]["subscribeOnEnterCallback"].get<sol::function>();
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsTrue(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnEnterEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnEnterCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    sol::error error = result;

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), mouseInteractionHandler->getOnEnterEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region SubscribeOnLeaveCallback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnLeaveCallback_InputtingInvalidFunction_DoesNotRegisterCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function;
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsFalse(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeaveEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnLeaveCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeaveEvent().getSubscriberCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnLeaveCallback_InputtingValidFunction_RegistersCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::function function = state["MouseInteractionHandler"]["subscribeOnLeaveCallback"].get<sol::function>();
    GameObject gameObject;
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

    Assert::IsTrue(function.valid());
    Assert::AreEqual(static_cast<size_t>(0), mouseInteractionHandler->getOnLeaveEvent().getSubscriberCount());

    auto result = state["MouseInteractionHandler"]["subscribeOnLeaveCallback"].
      get<sol::protected_function>().call(*mouseInteractionHandler, function);

    sol::error error = result;

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), mouseInteractionHandler->getOnLeaveEvent().getSubscriberCount());
  }

#pragma endregion 

#pragma region MouseInteractionHandler As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToMouseInteractionHandlerType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "MouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockMouseInteractionHandler : public Celeste::Input::MouseInteractionHandler {};
    state.new_usertype<MockMouseInteractionHandler>("MockMouseInteractionHandler");

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "MockMouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandlerHandle_as_InputtingNullMouseInteractionHandlerHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    MouseInteractionHandler mouseInteractionHandler;
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mouseInteractionHandler == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToMouseInteractionHandlerType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    MouseInteractionHandler mouseInteractionHandler;
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "MouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mouseInteractionHandler == functionResult.get<MouseInteractionHandler*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockMouseInteractionHandler : public Celeste::Input::MouseInteractionHandler {};
    state.new_usertype<MockMouseInteractionHandler>("MockMouseInteractionHandler");

    MouseInteractionHandler mouseInteractionHandler;
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "MockMouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    MouseInteractionHandler mouseInteractionHandler;
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}