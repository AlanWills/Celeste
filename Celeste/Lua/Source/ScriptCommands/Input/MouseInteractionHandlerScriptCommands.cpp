#include "ScriptCommands/Input/MouseInteractionHandlerScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Input/MouseInteractionHandler.h"

using MouseInteractionHandler = Celeste::Input::MouseInteractionHandler;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Input::MouseInteractionHandler> : std::false_type {};
}

namespace Celeste::Lua::Input::MouseInteractionHandlerScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnLeftButtonClickedCallback(
      MouseInteractionHandler& handler, 
      sol::protected_function function,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Celeste::Input::GameObjectEvent, GameObject&>(handler.getOnLeftButtonUpEvent(), function, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnRightButtonClickedCallback(
      MouseInteractionHandler& handler,
      sol::protected_function function,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Celeste::Input::GameObjectEvent, GameObject&>(handler.getOnRightButtonUpEvent(), function, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnEnterCallback(
      MouseInteractionHandler& handler, 
      sol::protected_function function,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Celeste::Input::GameObjectEvent, GameObject&>(handler.getOnEnterEvent(), function, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnLeaveCallback(
      MouseInteractionHandler& handler, 
      sol::protected_function function, 
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Celeste::Input::GameObjectEvent, GameObject&>(handler.getOnLeaveEvent(), function, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<MouseInteractionHandler>(
      state,
      "MouseInteractionHandler",
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "subscribeOnLeftButtonUpCallback", &Internals::subscribeOnLeftButtonClickedCallback,
      "subscribeOnRightButtonUpCallback", &Internals::subscribeOnRightButtonClickedCallback,
      "subscribeOnEnterCallback", &Internals::subscribeOnEnterCallback,
      "subscribeOnLeaveCallback", &Internals::subscribeOnLeaveCallback);
  }
}