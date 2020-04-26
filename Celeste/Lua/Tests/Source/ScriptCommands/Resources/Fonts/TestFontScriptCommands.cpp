#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Fonts/MockFont.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestFontScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Initialize_Adds_FontUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Font"].valid());

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Font"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Initialize_Adds_as_ToFontTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Font"]["as"].valid());

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Font"]["as"].valid());
  }

#pragma endregion

#pragma region Font As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNull_CastingToFontType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "Font");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    class MockFont : public Celeste::Resources::Font {};
    state.new_usertype<MockFont>("MockFont");

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "MockFont");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_FontHandle_as_InputtingNullFontHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNonNullFont_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    Font font;
    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(&font, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&font == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNonNullFont_CastingToFontType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Font font;
    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(&font, "Font");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&font == functionResult.get<Font*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNonNullFont_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    class MockFont : public Celeste::Resources::Font {};
    state.new_usertype<MockFont>("MockFont");

    Font font;
    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(&font, "MockFont");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNonNullFont_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Font font;
    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(&font, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FontScriptCommands_Font_as_InputtingNonNullFont_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FontScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Font"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}