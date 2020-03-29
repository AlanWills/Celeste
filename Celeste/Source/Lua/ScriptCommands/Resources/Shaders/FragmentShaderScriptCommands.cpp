#include "Lua/ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

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
  void initialize()
  {
    registerUserType<FragmentShader>(
      "FragmentShader",
      sol::base_classes, sol::bases<Celeste::Resources::Shader, Celeste::Resources::Resource, Object>());
  }
}