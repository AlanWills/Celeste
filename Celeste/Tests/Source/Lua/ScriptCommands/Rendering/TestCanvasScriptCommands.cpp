#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Rendering/Canvas.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using Canvas = Celeste::Rendering::Canvas;

using namespace Celeste;


namespace TestCeleste::Lua::Rendering::CanvasScriptCommands
{
  CELESTE_TEST_CLASS(TestCanvasScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Initialize_Adds_CanvasUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Canvas"].valid());

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Canvas"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Initialize_Adds_as_ToCanvasTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Canvas"]["as"].valid());

    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Canvas"]["as"].valid());
  }

#pragma endregion

#pragma region Canvas As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToCanvasType_ReturnsNil)
  {
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "Canvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockCanvas : public Celeste::Rendering::Canvas {};
    state.new_usertype<MockCanvas>("MockCanvas");

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "MockCanvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_CanvasHandle_as_InputtingNullCanvasHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

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
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    GameObject gameObject;
    Canvas canvas(gameObject);
    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(&canvas, "Canvas");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&canvas == functionResult.get<Canvas*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CanvasScriptCommands_Canvas_as_InputtingNonNullCanvas_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

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
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

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
    Celeste::Lua::Rendering::CanvasScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Canvas"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}