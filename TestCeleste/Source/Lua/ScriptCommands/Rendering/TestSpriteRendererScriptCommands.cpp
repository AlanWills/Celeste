#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Resources/TestResources.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using SpriteRenderer = Celeste::Rendering::SpriteRenderer;

using namespace Celeste;


namespace TestCeleste::Lua::Rendering::SpriteRendererScriptCommands
{
  CELESTE_TEST_CLASS(TestSpriteRendererScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_SpriteRendererUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["SpriteRenderer"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_allocate_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["allocate"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["SpriteRenderer"]["allocate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_setTexture_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["setTexture"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["SpriteRenderer"]["setTexture"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_setColour_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["setColour"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["SpriteRenderer"]["setColour"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_as_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["as"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    Assert::IsTrue(state.globals()["SpriteRenderer"]["as"].valid());
  }

#pragma endregion

#pragma region Set Texture Tests

#pragma region Texture Handle Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_TextureOverload_InputtingNullptrTexture_SetsTextureToNullptr)
  {
    SpriteRenderer spriteRenderer;
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, observer_ptr<Resources::Texture2D>());

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_TextureHandleOverload_InputtingNonNullTextureHandle_SetsTextureToInputtedValue)
  {
    SpriteRenderer spriteRenderer;

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, texture);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(texture, spriteRenderer.getTexture());
  }

#pragma endregion

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingInvalidPath_SetsTextureToNullptr)
  {
    SpriteRenderer spriteRenderer;
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingValidPathToInvalidTexture_SetsTextureToNullptr)
  {
    SpriteRenderer spriteRenderer;
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, TestResources::getArialTtfRelativePath());

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingValidRelativePathToValidTexture_SetsTextureToCorrectValue)
  {
    SpriteRenderer spriteRenderer;

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, TestResources::getBlockPngRelativePath());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(texture, spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingFullPathToValidTexture_SetsTextureToCorrectValue)
  {
    SpriteRenderer spriteRenderer;

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngFullPath());

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, TestResources::getBlockPngFullPath().as_string());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(texture, spriteRenderer.getTexture());
  }

#pragma endregion

#pragma endregion

#pragma region Set Colour Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setColour_InputtingThreeFloats_UpdatesSpriteRendererColour)
  {
    SpriteRenderer spriteRenderer;
    spriteRenderer.setColour(0.5f, 0.5f, 0.5f, 0.5f);

    Assert::AreEqual(glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), spriteRenderer.getColour());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    auto result = state[SpriteRenderer::type_name()]["setColour"].get<sol::protected_function>().call(spriteRenderer, 0.2f, 0.2f, 0.2f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec4(0.2f, 0.2f, 0.2f, 0.5f), spriteRenderer.getColour());
  }

#pragma endregion

#pragma region SpriteRenderer As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToSpriteRendererType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "SpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer {};
    state.new_usertype<MockSpriteRenderer>("MockSpriteRenderer");

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "MockSpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRendererHandle_as_InputtingNullSpriteRendererHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    SpriteRenderer spriteRenderer;
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&spriteRenderer == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToSpriteRendererType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    SpriteRenderer spriteRenderer;
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "SpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&spriteRenderer == functionResult.get<SpriteRenderer*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer {};
    state.new_usertype<MockSpriteRenderer>("MockSpriteRenderer");

    SpriteRenderer spriteRenderer;
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "MockSpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    SpriteRenderer spriteRenderer;
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}