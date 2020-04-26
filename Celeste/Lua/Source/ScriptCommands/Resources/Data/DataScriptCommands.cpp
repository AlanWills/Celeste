#include "ScriptCommands/Resources/Data/DataScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Data/Data.h"

using Data = Celeste::Resources::Data;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Data> : std::false_type {};
}

namespace Celeste::Lua::Resources::DataScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Data>(
      state,
      "Data",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}