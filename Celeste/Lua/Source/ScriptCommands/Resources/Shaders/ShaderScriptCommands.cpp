#include "ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "ScriptCommands/Resources/Shaders/VertexShaderScriptCommands.h"
#include "ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"


namespace Celeste::Lua::Resources::ShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    VertexShaderScriptCommands::initialize(state);
    FragmentShaderScriptCommands::initialize(state);
  }
}