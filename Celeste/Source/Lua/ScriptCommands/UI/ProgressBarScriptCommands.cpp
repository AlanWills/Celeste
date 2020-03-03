#include "Lua/ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/ProgressBar.h"


namespace Celeste::Lua::UI::ProgressBarScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using ProgressBar = Celeste::UI::ProgressBar;

    sol::state& state = Lua::LuaState::instance();
    registerUserType<ProgressBar>(
      ProgressBar::type_name(),
      "getProgress", &ProgressBar::getProgress,
      "setProgress", &ProgressBar::setProgress);
  }
}