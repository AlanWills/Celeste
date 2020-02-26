#include "Lua/ScriptCommands/Resources/Shaders/VertexShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Shaders/VertexShader.h"

using VertexShader = Celeste::Resources::VertexShader;


namespace Celeste::Lua::Resources::VertexShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<VertexShader>("VertexShader");
  }
}