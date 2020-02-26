#include "Lua/ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Shaders/VertexShaderScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"


namespace Celeste::Lua::Resources::ShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    VertexShaderScriptCommands::initialize();
    FragmentShaderScriptCommands::initialize();
  }
}