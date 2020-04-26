#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Rendering/Canvas.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using Canvas = Celeste::Rendering::Canvas;

using namespace Celeste;


namespace TestCelesteLua::Lua::Rendering::CanvasScriptCommands
{
  CELESTE_TEST_CLASS(TestCanvasScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Initialize_Adds_CanvasUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Canvas"].valid());

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Canvas"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Initialize_Adds_as_ToCanvasTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Canvas"]["as"].valid());

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Canvas"]["as"].valid());
  }

#pragma endregion

#pragma region Canvas As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToCanvasType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "Canvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    class MockCanvas : public Celeste::Rendering::Canvas {};
    state.new_usertype<MockCanvas>("MockCanvas");

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "MockCanvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_CanvasHandle_as_InputtingNullCanvasHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    Canvas canvas(gameObject);
    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(&canvas, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&canvas == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToCanvasType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    GameObject gameObject;
    Canvas canvas(gameObject);
    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(&canvas, "Canvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&canvas == functionResult.get<Canvas*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    class MockCanvas : public Celeste::Rendering::Canvas {};
    state.new_usertype<MockCanvas>("MockCanvas");

    GameObject gameObject;
    Canvas canvas(gameObject);
    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(&canvas, "MockCanvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    Canvas canvas(gameObject);
    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(&canvas, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}