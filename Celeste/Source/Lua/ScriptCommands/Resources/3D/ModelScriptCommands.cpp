#include "Lua/ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

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
  void initialize()
  {
    registerUserType<Model>(
      "Model",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}