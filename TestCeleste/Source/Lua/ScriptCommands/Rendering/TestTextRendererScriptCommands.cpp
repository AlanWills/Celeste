#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Rendering/MockTextRenderer.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using TextRenderer = Celeste::Rendering::TextRenderer;

using namespace Celeste;


namespace TestCeleste::Lua::Rendering::TextRendererScriptCommands
{
  CELESTE_TEST_CLASS(TestTextRendererScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_TextRendererUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["TextRenderer"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_setText_ToTextRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"]["setText"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["TextRenderer"]["setText"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_as_ToTextRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"]["as"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["TextRenderer"]["as"].valid());
  }

#pragma endregion

#pragma region Set Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingEmptyString_SetsTextToEmptyString)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    Assert::AreEqual(static_cast<size_t>(1), textRenderer.getLineCount());
    Assert::AreEqual("Test", textRenderer.getLine(0).c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(static_cast<size_t>(0), textRenderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingSingleLineString_SetsTextToCorrectValue)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();
    sol::state& state = LuaState::instance();
    
    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    Assert::AreEqual(static_cast<size_t>(1), textRenderer.getLineCount());
    Assert::AreEqual("Test", textRenderer.getLine(0).c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "Another Test");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(static_cast<size_t>(1), textRenderer.getLineCount());
    Assert::AreEqual("Another Test", textRenderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingMultipleLineString_SetsTextToCorrectValue)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();
    sol::state& state = LuaState::instance();
    
    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.addLine("Text");

    Assert::AreEqual(static_cast<size_t>(1), textRenderer.getLineCount());
    Assert::AreEqual("Text", textRenderer.getLine(0).c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "Another\nTest");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual(static_cast<size_t>(2), textRenderer.getLineCount());
    Assert::AreEqual("Another", textRenderer.getLine(0).c_str());
    Assert::AreEqual("Test", textRenderer.getLine(1).c_str());
  }

#pragma endregion

#pragma region TextRenderer As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToTextRendererType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "TextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockTextRenderer : public Celeste::Rendering::TextRenderer {};
    state.new_usertype<MockTextRenderer>("MockTextRenderer");

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "MockTextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRendererHandle_as_InputtingNullTextRendererHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(&textRenderer, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&textRenderer == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToTextRendererType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(&textRenderer, "TextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&textRenderer == functionResult.get<TextRenderer*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockTextRenderer : public Celeste::Rendering::TextRenderer {};
    state.new_usertype<MockTextRenderer>("MockTextRenderer");

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(&textRenderer, "MockTextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(&textRenderer, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}