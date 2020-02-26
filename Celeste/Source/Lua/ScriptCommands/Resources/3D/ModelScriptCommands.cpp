#include "Lua/ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Resources/3D/Model.h"

using Model = Celeste::Resources::Model;


namespace Celeste::Lua::Resources::ModelScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Model>("Model");
  }
}