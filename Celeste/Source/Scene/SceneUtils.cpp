#include "Scene/SceneUtils.h"
#include "Game/Game.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  SceneManager& getSceneManager()
  {
    return Game::getSceneManager();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow& getWindow()
  {
    return Game::getWindow();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 getViewportDimensions()
  {
    return getWindow().getViewportDimensions();
  }
}