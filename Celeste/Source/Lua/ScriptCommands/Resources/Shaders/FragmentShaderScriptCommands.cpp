#include "Lua/ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/Shaders/FragmentShader.h"

using FragmentShader = Celeste::Resources::FragmentShader;


namespace Celeste::Lua::Resources::FragmentShaderScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<FragmentShader>("FragmentShader");
  }
}