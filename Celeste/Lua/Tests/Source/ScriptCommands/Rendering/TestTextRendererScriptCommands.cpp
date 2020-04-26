#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Rendering/MockTextRenderer.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using TextRenderer = Celeste::Rendering::TextRenderer;

using namespace Celeste;


namespace TestCelesteLua::Lua::Rendering::TextRendererScriptCommands
{
  CELESTE_TEST_CLASS(TestTextRendererScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_TextRendererUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["TextRenderer"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_setText_ToTextRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"]["setText"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["TextRenderer"]["setText"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_Initialize_Adds_as_ToTextRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["TextRenderer"]["as"].valid());

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["TextRenderer"]["as"].valid());
  }

#pragma endregion

#pragma region Set Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingEmptyString_SetsTextToEmptyString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.setText("Test");

    Assert::AreEqual("Test", textRenderer.getText().c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("", textRenderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingSingleLineString_SetsTextToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);
    
    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.setText("Test");

    Assert::AreEqual("Test", textRenderer.getText().c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "Another Test");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("Another Test", textRenderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_setText_InputtingMultipleLineString_SetsTextToCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);
    
    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    textRenderer.setText("Text");

    Assert::AreEqual("Text", textRenderer.getText().c_str());

    auto functionResult = state.globals()["TextRenderer"]["setText"].get<sol::protected_function>().call(textRenderer, "Another\nTest");

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("Another\nTest", textRenderer.getText().c_str());
  }

#pragma endregion

#pragma region TextRenderer As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToTextRendererType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "TextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    class MockTextRenderer : public Celeste::Rendering::TextRenderer {};
    state.new_usertype<MockTextRenderer>("MockTextRenderer");

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "MockTextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRendererHandle_as_InputtingNullTextRendererHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    GameObject gameObject;
    TextRenderer textRenderer(gameObject);
    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(&textRenderer, "TextRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&textRenderer == functionResult.get<TextRenderer*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererScriptCommands_TextRenderer_as_InputtingNonNullTextRenderer_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::TextRendererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["TextRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}