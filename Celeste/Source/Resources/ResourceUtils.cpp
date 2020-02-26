#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"
#include "Game/Game.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  ResourceManager& getResourceManager()
  {
    return Game::getResourceManager();
  }

  //------------------------------------------------------------------------------------------------
  const Path& getResourcesDirectory()
  {
    return getResourceManager().getResourcesDirectory();
  }
}