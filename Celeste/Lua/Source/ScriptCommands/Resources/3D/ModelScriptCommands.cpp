#include "ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Resources/3D/Model.h"

using Model = Celeste::Resources::Model;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::Model> : std::false_type {};
}

namespace Celeste::Lua::Resources::ModelScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Model>(
      state,
      "Model",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}