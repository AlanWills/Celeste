#include "Rendering/RenderUtils.h"
#include "Game/Game.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  RenderManager& getRenderManager()
  {
    return Game::getRenderManager();
  }
}