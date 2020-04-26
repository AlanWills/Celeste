#include "ScriptCommands/Input/MouseScriptCommands.h"
#include "sol/sol.hpp"

#include "Input/Mouse.h"
#include "Input/InputUtils.h"


namespace Celeste::Lua::Input::MouseScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setCursor(const std::string& path)
    {
      Celeste::Input::getMouse().setCursor(path);
    }

    //------------------------------------------------------------------------------------------------
    void setCursor_CursorHotSpot(const std::string& path, glm::vec2 cursorHotSpot)
    {
      Celeste::Input::getMouse().setCursor(path, cursorHotSpot);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.create_named_table(
      "Mouse",
      "setCursor", sol::overload(&Internals::setCursor, &Internals::setCursor_CursorHotSpot));
  }
}