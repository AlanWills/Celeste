#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/UI/UIScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "UI/StackPanel.h"
#include "UI/ProgressBar.h"
#include "UI/Slider.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::UI
{
  CELESTE_TEST_CLASS(TestUIScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestUIScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize(LuaState::instance());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIScriptCommands_Initialize_InitializesStackPanelScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Celeste::UI::StackPanel::type_name()].valid());

    Celeste::Lua::UI::ScriptCommands::initialize(state);

    Assert::IsTrue(state[Celeste::UI::StackPanel::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIScriptCommands_Initialize_InitializesProgressBarScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Celeste::UI::ProgressBar::type_name()].valid());

    Celeste::Lua::UI::ScriptCommands::initialize(state);

    Assert::IsTrue(state[Celeste::UI::ProgressBar::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIScriptCommands_Initialize_InitializesSliderScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Celeste::UI::Slider::type_name()].valid());

    Celeste::Lua::UI::ScriptCommands::initialize(state);

    Assert::IsTrue(state[Celeste::UI::Slider::type_name()].valid());
  }

#pragma endregion

  };
}