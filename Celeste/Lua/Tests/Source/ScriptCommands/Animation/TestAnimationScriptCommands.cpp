#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Animation/AnimationScriptCommands.h"
#include "Lua/LuaState.h"

#include "Animation/Animator.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestAnimationScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationScriptCommands_Initialize_Adds_AnimatorUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()[Animation::Animator::type_name()].valid());

    Celeste::Lua::Animation::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()[Animation::Animator::type_name()].valid());
  }

#pragma endregion

  };
}