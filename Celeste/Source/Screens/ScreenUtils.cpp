#include "Screens/ScreenUtils.h"
#include "Screens/Screen.h"
#include "Game/Game.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  ScreenManager& getScreenManager()
  {
    return Game::getScreenManager();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow* getWindow()
  {
    return Game::getScreenManager().getWindow();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 getViewportDimensions()
  {
    OpenGLWindow* window = getWindow();
    return window != nullptr ? getWindow()->getViewportDimensions() : glm::vec2();
  }
}