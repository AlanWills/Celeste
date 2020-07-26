#include "ScriptCommands/Input/KeyboardScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Input/Keyboard.h"
#include "Input/InputUtils.h"

using namespace Celeste::Input;


namespace Celeste::Lua::Input::KeyboardScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    EventHandle subscribeOnKeyPressedCallback(sol::protected_function function, sol::object extraArgs)
    {
      return Celeste::Lua::subscribeToEvent<int>(getKeyboard().getKeyPressedEvent(), function, extraArgs);
    }

    //------------------------------------------------------------------------------------------------
    void unsubscribeOnKeyPressedCallback(EventHandle eventHandle)
    {
      getKeyboard().getKeyPressedEvent().unsubscribe(eventHandle);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.create_named_table(
      "Keyboard",
      "subscribeOnKeyPressedCallback", &Internals::subscribeOnKeyPressedCallback,
      "unsubscribeOnKeyPressedCallback", &Internals::unsubscribeOnKeyPressedCallback);
  }
}