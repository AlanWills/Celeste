#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/ObjectScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Objects/MockObject.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestObjectScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_Adds_ObjectUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Object"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Object"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_Adds_as_ToObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Object"]["as"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Object"]["as"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_InitializesScriptableObjectScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["ScriptableObject"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["ScriptableObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_InitializesEntityScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_InitializesComponentScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Component"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Component"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Initialize_InitializesGameObjectScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["GameObject"].valid());

    Celeste::Lua::ObjectScriptCommands::initialize();

    Assert::IsTrue(state.globals()["GameObject"].valid());
  }

#pragma endregion

#pragma region Object As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNull_CastingToObjectType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockObject : public Celeste::Object {};
    state.new_usertype<MockObject>("MockObject");

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "MockObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_ObjectHandle_as_InputtingNullObjectHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNonNullObject_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    Object object;
    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(&object, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&object == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNonNullObject_CastingToObjectType_ReturnsCorrectPtr)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Object object;
    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(&object, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&object == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNonNullObject_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockObject : public Celeste::Object {};
    state.new_usertype<MockObject>("MockObject");

    Object object;
    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(&object, "MockObject");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNonNullObject_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Object object;
    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(&object, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ObjectScriptCommands_Object_as_InputtingNonNullObject_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::ObjectScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Object"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}