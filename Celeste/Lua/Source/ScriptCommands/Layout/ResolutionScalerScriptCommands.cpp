#include "ScriptCommands/Layout/ResolutionScalerScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Layout/ResolutionScaler.h"

using ResolutionScaler = Celeste::Layout::ResolutionScaler;


namespace sol
{
  template <>
  struct is_to_stringable<ResolutionScaler> : std::false_type {};
}

namespace Celeste::Lua::Layout::ResolutionScalerScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<ResolutionScaler>(
      state,
      ResolutionScaler::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "setTargetResolution", &ResolutionScaler::setTargetResolution);
  }
}