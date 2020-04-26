#include "ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Shaders/FragmentShader.h"

using FragmentShader = Celeste::Resources::FragmentShader;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Resources::FragmentShader> : std::false_type {};
}

namespace Celeste::Lua::Resources::FragmentShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<FragmentShader>(
      state,
      "FragmentShader",
      sol::base_classes, sol::bases<Celeste::Resources::Shader, Celeste::Resources::Resource, Object>());
  }
}