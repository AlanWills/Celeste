#include "Scene/SceneUtils.h"
#include "Scene/SceneManager.h"
#include "Game/Game.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  SceneManager& getSceneManager()
  {
    return *Game::current().getSystem<SceneManager>();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow& getWindow()
  {
    return Game::current().getWindow();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 getViewportDimensions()
  {
    return getWindow().getViewportDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void setViewportDimensions(const glm::vec2& viewportDimensions)
  {
    getWindow().setViewportDimensions(viewportDimensions);
  }
}