#include "Callbacks/ExecuteLuaScript.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Resources/ResourceUtils.h"
#include "Lua/LuaState.h"
#include "FileSystem/File.h"
#include "Debug/Log.h"
#include "Debug/Assert.h"


namespace Celeste
{
  REGISTER_CALLBACK(ExecuteLuaScript)

  //------------------------------------------------------------------------------------------------
  void ExecuteLuaScript::operator()(GameObject& gameObject, const std::string& arg)
  {
    File file(arg);
    if (file.exists())
    {
      Celeste::Lua::LuaState::scriptFile(arg);
    }
    else
    {
      Path fullPathAttempt(Resources::getResourcesDirectory(), arg);
      file = File(fullPathAttempt);
      
      if (file.exists())
      {
        Celeste::Lua::LuaState::scriptFile(fullPathAttempt);
      }
      else
      {
        LOG("Script file " + arg + " could not be found.");
        ASSERT_FAIL();
      }
    }
  }
}