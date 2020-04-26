#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "TestResources/TestResources.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using SpriteRenderer = Celeste::Rendering::SpriteRenderer;

using namespace Celeste;


namespace TestCelesteLua::Lua::Rendering::SpriteRendererScriptCommands
{
  CELESTE_TEST_CLASS(TestSpriteRendererScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_SpriteRendererUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_getDimensions_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["getDimensions"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"]["getDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_setDimensions_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["setDimensions"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"]["setDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_setTexture_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["setTexture"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"]["setTexture"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_setColour_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["setColour"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"]["setColour"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_Initialize_Adds_as_ToSpriteRendererTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["SpriteRenderer"]["as"].valid());

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["SpriteRenderer"]["as"].valid());
  }

#pragma endregion

#pragma region Get Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_getDimensions_ReturnsCorrectDimensions)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    spriteRenderer.setDimensions(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), spriteRenderer.getDimensions());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["getDimensions"].get<sol::protected_function>().call(spriteRenderer);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec2(100, 200), result.get<glm::vec2>());
  }

#pragma endregion

#pragma region Set Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setDimensions_UpdatesDimensions)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    spriteRenderer.setDimensions(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), spriteRenderer.getDimensions());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["setDimensions"].get<sol::protected_function>().call(spriteRenderer, 300, 400);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec2(300, 400), spriteRenderer.getDimensions());
  }

#pragma endregion

#pragma region Set Texture Tests

#pragma region Texture Handle Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_TextureOverload_InputtingNullptrTexture_SetsTextureToNullptr)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, observer_ptr<Resources::Texture2D>());

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_TextureHandleOverload_InputtingNonNullTextureHandle_SetsTextureToInputtedValue)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);
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
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingValidPathToInvalidTexture_SetsTextureToNullptr)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    spriteRenderer.setTexture(texture);

    Assert::AreEqual(texture, spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, TestResources::getArialTtfRelativePath());

    Assert::IsTrue(result.valid());
    Assert::IsNull(spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingValidRelativePathToValidTexture_SetsTextureToCorrectValue)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);
    observer_ptr<Resources::Texture2D> texture = Resources::getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());

    auto result = state[SpriteRenderer::type_name()]["setTexture"].get<sol::protected_function>().call(spriteRenderer, TestResources::getBlockPngRelativePath());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(texture, spriteRenderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_setTexture_StringOverload_InputtingFullPathToValidTexture_SetsTextureToCorrectValue)
  {
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);

    Assert::IsNull(spriteRenderer.getTexture());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);
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
    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    spriteRenderer.setColour(0.5f, 0.5f, 0.5f, 0.5f);

    Assert::AreEqual(glm::vec4(0.5f, 0.5f, 0.5f, 0.5f), spriteRenderer.getColour());

    sol::state& state = LuaState::instance();
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto result = state[SpriteRenderer::type_name()]["setColour"].get<sol::protected_function>().call(spriteRenderer, 0.2f, 0.2f, 0.2f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec4(0.2f, 0.2f, 0.2f, 0.5f), spriteRenderer.getColour());
  }

#pragma endregion

#pragma region SpriteRenderer As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToSpriteRendererType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "SpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer {};
    state.new_usertype<MockSpriteRenderer>("MockSpriteRenderer");

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "MockSpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRendererHandle_as_InputtingNullSpriteRendererHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&spriteRenderer == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToSpriteRendererType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "SpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&spriteRenderer == functionResult.get<SpriteRenderer*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer {};
    state.new_usertype<MockSpriteRenderer>("MockSpriteRenderer");

    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "MockSpriteRenderer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    SpriteRenderer spriteRenderer(gameObject);
    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(&spriteRenderer, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererScriptCommands_SpriteRenderer_as_InputtingNonNullSpriteRenderer_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Rendering::SpriteRendererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["SpriteRenderer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}