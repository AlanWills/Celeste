#include "Lua/ScriptCommands/Screens/ScreenScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "Screens/Screen.h"
#include "Screens/Loading/ScreenLoader.h"

#include "Objects/GameObject.h"
#include "Maths/Transform.h"



namespace Celeste::Lua::ScreenScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    observer_ptr<Screen> load(const std::string& screenPath)
    {
      return ScreenLoader::load(screenPath);
    }

    //------------------------------------------------------------------------------------------------
    std::string getName(Screen& screen)
    {
      return deinternString(screen.getName());
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Screen>(
      "Screen",
      sol::base_classes, sol::bases<Entity, Object>(),
      "load", sol::factories(Internals::load),
      "getName", &Internals::getName);
  }
}