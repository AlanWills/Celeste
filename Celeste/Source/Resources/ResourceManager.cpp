#include "Resources/ResourceManager.h"
#include "Game/Game.h"


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

  //------------------------------------------------------------------------------------------------
  Data* ResourceManager::create(const Path& relativeOrFullPath)
  {
    if (relativeOrFullPath.as_string().empty())
    {
      ASSERT_FAIL();
      return nullptr;
    }

    Path savePath;

    if (!getResourcesDirectory().isAncestorOf(relativeOrFullPath))
    {
      // A fairly vague attempt at handling relative and absolute paths
      // This currently enforces data must be saved within resources
      // as we see if the path we have is a full path relative to the resources directory
      // or does not contain the resources directory path
      savePath.combine(getResourcesDirectory(), relativeOrFullPath);
    }
    else
    {
      savePath.combine(relativeOrFullPath);
    }

    if (File::exists(savePath))
    {
      ASSERT_FAIL();
      return load<Data>(savePath);
    }

    // Create the data file here
    XMLDocument document;
    document.InsertFirstChild(document.NewDeclaration());

    // Ensures all parent directories are created too
    File(savePath).create();

    tinyxml2::XMLError error = document.SaveFile(savePath.c_str());
    if (error != tinyxml2::XMLError::XML_SUCCESS)
    {
      Celeste::Log::error(error);
      ASSERT_FAIL();
      return nullptr;
    }

    Data* data = getResourceManager().load<Data>(savePath);
    ASSERT_NOT_NULL(data);
    return data;
  }
}