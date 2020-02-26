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

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> allocateGameObject_NoParent(Screen& screen)
    {
      return screen.allocateGameObject();
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> allocateGameObject_WithParent(Screen& screen, Transform& transform)
    {
      return screen.allocateGameObject(transform);
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findGameObject_StringOverload(Screen& screen, const std::string& gameObjectName)
    {
      return screen.findGameObject(gameObjectName);
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<GameObject> findGameObject_StringIdOverload(Screen& screen, StringId gameObjectName)
    {
      return screen.findGameObject(gameObjectName);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Screen>(
      "Screen",
      sol::base_classes, sol::bases<Entity, Object>(),
      "load", sol::factories(Internals::load),
      "getName", &Internals::getName,
      "allocateGameObject", sol::overload(&Internals::allocateGameObject_NoParent, &Internals::allocateGameObject_WithParent),
      "deallocateGameObject", &Screen::deallocateGameObject,
      "findGameObject", sol::overload(&Internals::findGameObject_StringOverload, &Internals::findGameObject_StringIdOverload));
  }
}