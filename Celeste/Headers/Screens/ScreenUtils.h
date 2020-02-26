#pragma once

#include "CelesteDllExport.h"
#include "UID/StringId.h"
#include "glm/glm.hpp"

#include <string>


namespace Celeste
{
  class ScreenManager;
  class OpenGLWindow;

  //------------------------------------------------------------------------------------------------
  CelesteDllExport ScreenManager& getScreenManager();
  CelesteDllExport OpenGLWindow* getWindow();
  CelesteDllExport glm::vec2 getViewportDimensions();
}