#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/MouseInteractionHandlerScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Input/MouseInteractionHandler.h"

#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;
using namespace Celeste::Input;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestMouseInteractionHandlerScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_MouseInteractionHandlerUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnLeftButtonUpCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnRightButtonUpCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnEnterCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnEnterCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnEnterCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_subscribeOnLeaveCallback_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["subscribeOnLeaveCallback"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["subscribeOnLeaveCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_Initialize_Adds_as_ToMouseInteractionHandlerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["MouseInteractionHandler"]["as"].valid());

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["MouseInteractionHandler"]["as"].valid());
  }

#pragma endregion

#pragma region Subscribe On Left Button Up Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_subscribeOnLeftButtonUpCallback_InputtingInvalidFunction_DoesNotRegisterCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function;
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function = state["MouseInteractionHandler"]["subscribeOnLeftButtonUpCallback"].get<sol::function>();
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function;
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function = state["MouseInteractionHandler"]["subscribeOnRightButtonUpCallback"].get<sol::function>();
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function;
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function = state["MouseInteractionHandler"]["subscribeOnEnterCallback"].get<sol::function>();
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function;
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    sol::function function = state["MouseInteractionHandler"]["subscribeOnLeaveCallback"].get<sol::function>();
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.addComponent<MouseInteractionHandler>();

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToMouseInteractionHandlerType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "MouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    class MockMouseInteractionHandler : public Celeste::Input::MouseInteractionHandler {};
    state.new_usertype<MockMouseInteractionHandler>("MockMouseInteractionHandler");

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "MockMouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandlerHandle_as_InputtingNullMouseInteractionHandlerHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    MouseInteractionHandler mouseInteractionHandler(gameObject);
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mouseInteractionHandler == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToMouseInteractionHandlerType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    GameObject gameObject;
    MouseInteractionHandler mouseInteractionHandler(gameObject);
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "MouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mouseInteractionHandler == functionResult.get<MouseInteractionHandler*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    class MockMouseInteractionHandler : public Celeste::Input::MouseInteractionHandler {};
    state.new_usertype<MockMouseInteractionHandler>("MockMouseInteractionHandler");

    GameObject gameObject;
    MouseInteractionHandler mouseInteractionHandler(gameObject);
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "MockMouseInteractionHandler");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    MouseInteractionHandler mouseInteractionHandler(gameObject);
    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(&mouseInteractionHandler, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandlerScriptCommands_MouseInteractionHandler_as_InputtingNonNullMouseInteractionHandler_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Input::MouseInteractionHandlerScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["MouseInteractionHandler"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}