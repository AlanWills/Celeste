#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Maths/TransformScriptCommands.h"
#include "Lua/LuaState.h"

#include "Maths/Transform.h"

using namespace Celeste::Lua;


namespace TestCeleste::Lua::Maths::TransformScriptCommands
{
  CELESTE_TEST_CLASS(TestTransformScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_AddsTransform_ToGlobalTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_setTranslation_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["setTranslation"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"]["setTranslation"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_getWorldTranslation_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["getWorldTranslation"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"]["getWorldTranslation"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_setWorldTranslation_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["setWorldTranslation"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"]["setWorldTranslation"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_translate_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["translate"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"]["translate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_setScale_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["setScale"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Transform"]["setScale"].valid());
  }

#pragma endregion

#pragma region Set Translation Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_setTranslation_InputtingTwoFloats_SetsXYComponentsOfTranslationCorrectly)
  {
    Celeste::Transform transform;
    transform.setTranslation(-3, -6, -9);

    sol::state& state = Celeste::Lua::LuaState::instance();
    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::AreEqual(glm::vec3(-3, -6, -9), transform.getTranslation());

    auto result = state["Transform"]["setTranslation"].get<sol::protected_function>().call(transform, 12.0f, 11.0f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(12, 11, -9), transform.getTranslation());
  }

#pragma endregion

#pragma region Get World Translation Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_getWorldTranslation_ReturnsCorrectWorldTranslation)
  {
    Celeste::Transform parent;
    Celeste::Transform transform;
    parent.setTranslation(1, 2, 3);
    transform.setTranslation(-3, -6, -9);
    transform.setParent(&parent);

    sol::state& state = Celeste::Lua::LuaState::instance();
    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::AreEqual(-2.0f, transform.getWorldTranslation().x);
    Assert::AreEqual(-4.0f, transform.getWorldTranslation().y);
    Assert::AreEqual(-6.0f, transform.getWorldTranslation().z);

    auto result = state["Transform"]["getWorldTranslation"].get<sol::protected_function>().call(transform);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(-2, -4, -6), result.get<glm::vec3>());
  }

#pragma endregion

#pragma region Set World Translation Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_setWorldTranslation_SetsCorrectWorldTranslation)
  {
    Celeste::Transform parent;
    Celeste::Transform transform;
    parent.setTranslation(1, 2, 3);
    transform.setTranslation(-3, -6, -9);
    transform.setParent(&parent);

    sol::state& state = Celeste::Lua::LuaState::instance();
    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::AreEqual(glm::vec3(-2, -4, -6), transform.getWorldTranslation());

    auto result = state["Transform"]["setWorldTranslation"].get<sol::protected_function>().call(transform, glm::vec3(12, 11, 10));

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(12, 11, 10), transform.getWorldTranslation());
  }

#pragma endregion

#pragma region Translate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_translate_AdjustsTransformX_AndYTranslation_ByInputtedValues)
  {
    Celeste::Transform transform;
    sol::state& state = Celeste::Lua::LuaState::instance();
    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::AreEqual(0.0f, transform.getTranslation().x);
    Assert::AreEqual(0.0f, transform.getTranslation().y);

    auto result = state["Transform"]["translate"].get<sol::protected_function>().call(transform, 5, -1.234f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(5.0f, transform.getTranslation().x);
    Assert::AreEqual(-1.234f, transform.getTranslation().y);
  }

#pragma endregion

#pragma region Set Scale Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_setScale_InputtingTwoFloats_SetsXYComponentsOfScaleCorrectly)
  {
    Celeste::Transform transform;
    transform.setScale(-3, -6, -9);

    sol::state& state = Celeste::Lua::LuaState::instance();
    Celeste::Lua::Maths::TransformScriptCommands::initialize(state);

    Assert::AreEqual(glm::vec3(-3, -6, -9), transform.getScale());

    auto result = state["Transform"]["setScale"].get<sol::protected_function>().call(transform, 12.0f, 11.0f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(12, 11, -9), transform.getScale());
  }

#pragma endregion

  };
}