#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Viewport::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    glm::vec2 getContentArea()
    {
      return getWindow().getContentArea();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table viewportTable = state.create_named_table(
      "Viewport",
      "getResolution", &getResolution,
      "setResolution", &setResolution,
      "getContentArea", &Internals::getContentArea);
  }
}