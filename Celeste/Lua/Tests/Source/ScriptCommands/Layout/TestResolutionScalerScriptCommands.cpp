#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Layout/ResolutionScalerScriptCommands.h"
#include "Lua/LuaState.h"

#include "Layout/ResolutionScaler.h"
#include "Objects/GameObject.h"

using LuaState = Celeste::Lua::LuaState;
using ResolutionScaler = Celeste::Layout::ResolutionScaler;

using namespace Celeste;


namespace TestCeleste::Lua::Layout
{
  CELESTE_TEST_CLASS(TestResolutionScalerScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScalerScriptCommands_Initialize_Adds_ResolutionScaler_ToSystemTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ResolutionScaler::type_name()].valid());

    Celeste::Lua::Layout::ResolutionScalerScriptCommands::initialize(state);

    Assert::IsTrue(state[ResolutionScaler::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScalerScriptCommands_Initialize_Adds_setTargetResolution_ToResolutionScalerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ResolutionScaler::type_name()]["setTargetResolution"].valid());

    Celeste::Lua::Layout::ResolutionScalerScriptCommands::initialize(state);

    Assert::IsTrue(state[ResolutionScaler::type_name()]["setTargetResolution"].valid());
  }

#pragma endregion

#pragma region Set Target Resolution Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScalerScriptCommands_setTargetResolution_SetsTargetResolutionToCorrectValue)
  {
    GameObject gameObject;
    ResolutionScaler resolutionScaler(gameObject);
    resolutionScaler.setTargetResolution(glm::vec2(400, 300));

    sol::state& state = LuaState::instance();
    Celeste::Lua::Layout::ResolutionScalerScriptCommands::initialize(state);

    Assert::AreEqual(glm::vec2(400, 300), resolutionScaler.getTargetResolution());

    auto result = state[ResolutionScaler::type_name()]["setTargetResolution"].get<sol::protected_function>().call(resolutionScaler, glm::vec2(100, 200));

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec2(100, 200), resolutionScaler.getTargetResolution());
  }

#pragma endregion

  };
}