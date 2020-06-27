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
  glm::vec2 getResolution()
  {
    return getWindow().getResolution();
  }

  //------------------------------------------------------------------------------------------------
  void setResolution(const glm::vec2& resolution)
  {
    getWindow().setResolution(resolution);
  }
}