#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Maths/TransformScriptCommands.h"
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

    Celeste::Lua::Maths::TransformScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Transform"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_Initialize_Adds_translate_ToTransformTable)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsFalse(state.globals()["Transform"]["translate"].valid());

    Celeste::Lua::Maths::TransformScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Transform"]["translate"].valid());
  }

#pragma endregion

#pragma region Translate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransformScriptCommands_translate_AdjustsTransformX_AndYTranslation_ByInputtedValues)
  {
    Celeste::Transform transform;
    Celeste::Lua::Maths::TransformScriptCommands::initialize();
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::AreEqual(0.0f, transform.getTranslation().x);
    Assert::AreEqual(0.0f, transform.getTranslation().y);

    auto result = state["Transform"]["translate"].get<sol::protected_function>().call(transform, 5, -1.234f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(5.0f, transform.getTranslation().x);
    Assert::AreEqual(-1.234f, transform.getTranslation().y);
  }

#pragma endregion
  
  };
}