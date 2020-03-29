#include "Lua/ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/ProgressBar.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::UI::ProgressBar> : std::false_type {};
}

namespace Celeste::Lua::UI::ProgressBarScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using ProgressBar = Celeste::UI::ProgressBar;

    registerUserType<ProgressBar>(
      ProgressBar::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getProgress", &ProgressBar::getProgress,
      "setProgress", &ProgressBar::setProgress);
  }
}