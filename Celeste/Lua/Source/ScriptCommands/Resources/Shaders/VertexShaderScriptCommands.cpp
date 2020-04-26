#include "ScriptCommands/Resources/Shaders/VertexShaderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Shaders/VertexShader.h"

using VertexShader = Celeste::Resources::VertexShader;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::VertexShader> : std::false_type {};
}

namespace Celeste::Lua::Resources::VertexShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<VertexShader>(
      state,
      "VertexShader",
      sol::base_classes, sol::bases<Celeste::Resources::Resource, Object>());
  }
}