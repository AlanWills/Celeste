#include "Rendering/RenderUtils.h"
#include "Rendering/RenderManager.h"
#include "Game/Game.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  RenderManager& getRenderManager()
  {
    return *Game::current().getSystem<Rendering::RenderManager>();
  }
}