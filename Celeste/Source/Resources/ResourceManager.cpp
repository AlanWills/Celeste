#include "Resources/ResourceManager.h"
#include "Game/Game.h"

#include <SOIL2/SOIL2.h>


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  ResourceManager::ResourceManager(const std::string& resourceDirectory) :
    m_vertexShaders(10, resourceDirectory),
    m_fragmentShaders(10, resourceDirectory),
    m_textures(100, resourceDirectory),
    m_fonts(10, resourceDirectory),
    m_sounds(20, resourceDirectory),
    m_data(150, resourceDirectory),
    m_prefabs(30, resourceDirectory),
    m_models(10, resourceDirectory),
    m_resourcesDirectory(resourceDirectory)
  {
  }

  //------------------------------------------------------------------------------------------------
  ResourceManager::~ResourceManager()
  {
    unloadAllResources();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::unloadAllResources()
  {
    m_vertexShaders.unloadAllResources();
    m_fragmentShaders.unloadAllResources();
    m_textures.unloadAllResources();
    m_fonts.unloadAllResources();
    m_sounds.unloadAllResources();
    m_data.unloadAllResources();
    m_prefabs.unloadAllResources();
    m_models.unloadAllResources();
  }

  //------------------------------------------------------------------------------------------------
  void ResourceManager::setResourcesDirectory(const Path& resourcesDirectory)
  {
    m_resourcesDirectory.reset(resourcesDirectory);
    m_vertexShaders.setResourceDirectoryPath(resourcesDirectory);
    m_fragmentShaders.setResourceDirectoryPath(resourcesDirectory);
    m_textures.setResourceDirectoryPath(resourcesDirectory);
    m_fonts.setResourceDirectoryPath(resourcesDirectory);
    m_sounds.setResourceDirectoryPath(resourcesDirectory);
    m_data.setResourceDirectoryPath(resourcesDirectory);
    m_prefabs.setResourceDirectoryPath(resourcesDirectory);
    m_models.setResourceDirectoryPath(resourcesDirectory);
  }
}