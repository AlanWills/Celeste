#pragma once

#include "CelesteDllExport.h"
#include "UID/StringId.h"
#include "glm/glm.hpp"

#include <string>


namespace Celeste
{
  class SceneManager;
  class OpenGLWindow;

  //------------------------------------------------------------------------------------------------
  CelesteDllExport SceneManager& getSceneManager();
  CelesteDllExport OpenGLWindow& getWindow();
  CelesteDllExport glm::vec2 getViewportDimensions();
  CelesteDllExport void setViewportDimensions(const glm::vec2& viewportDimensions);
}