#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Viewport::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool isWindowed()
    {
      return getWindow().getWindowMode() == OpenGLWindow::WindowMode::kWindowed;
    }

    //------------------------------------------------------------------------------------------------
    void setWindowed(bool windowed)
    {
      return getWindow().setWindowMode(windowed ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);
    }

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
      "isWindowed", &Internals::isWindowed,
      "setWindowed", &Internals::setWindowed,
      "getContentArea", &Internals::getContentArea);
  }
}