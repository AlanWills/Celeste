#include "ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "UI/ProgressBar.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::UI::ProgressBar> : std::false_type {};
}

namespace Celeste::Lua::UI::ProgressBarScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using ProgressBar = Celeste::UI::ProgressBar;

    registerUserType<ProgressBar>(
      state,
      ProgressBar::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getProgress", &ProgressBar::getProgress,
      "setProgress", &ProgressBar::setProgress);
  }
}