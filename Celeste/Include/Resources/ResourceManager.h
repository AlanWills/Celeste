#pragma once

#include <GL/glew.h>

#include "ResourceLoader.h"
#include "Shaders/VertexShader.h"
#include "Shaders/FragmentShader.h"
#include "2D/Texture2D.h"
#include "Fonts/Font.h"
#include "Audio/Sound.h"
#include "Data/Data.h"
#include "Data/Prefab.h"
#include "3D/Model.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "UID/StringId.h"
#include "Objects/Entity.h"
#include "ResourceUtils.h"


namespace Celeste::Resources
{
  class ResourceManager : public Entity
  {
    public:
      CelesteDllExport ResourceManager(const std::string& resourceDirectory);
      CelesteDllExport ResourceManager(const Path& resourceDirectory) : ResourceManager(resourceDirectory.as_string()) { }
      CelesteDllExport ~ResourceManager() override;

      /// Delete these - we should not allow copy construction as it will really screw with the singlar ownership of this class with it's resources
      ResourceManager(const ResourceManager&) = delete;
      ResourceManager& operator=(const ResourceManager&) = delete;

      /// The full path to the root directory which we can load resources relative from.
      const Path& getResourcesDirectory() const { return m_resourcesDirectory; }

      /// Set the full path to the root directory which we can load resources relative from.
      CelesteDllExport void setResourcesDirectory(const Path& resourcesDirectory);

      template <typename T>
      bool isLoaded(const Path& relativeOrFullPath) const;

      template <typename T>
      T* load(const Path& relativeOrFullPath);

      template <typename T>
      void unload(const Path& relativeOrFullPath);

      template <typename T>
      void unloadAll();

      /// Frees the resources from the resource manager's memory
      CelesteDllExport void unloadAllResources();

    protected:
  #define DEFINE_RESOURCE(ResourceType, LoaderMemberName) \
        public: \
          \
          template <> \
          bool isLoaded<##ResourceType##>(const Path& relativeOrFullPath) const { return LoaderMemberName.isResourceLoaded(relativeOrFullPath); } \
          \
          template <> \
          ResourceType##* load<##ResourceType##>(const Path& relativeOrFullPath) { return LoaderMemberName.loadResource(relativeOrFullPath); } \
          \
          template <> \
          void unload<##ResourceType##>(const Path& relativeOrFullPath) { LoaderMemberName.unloadResource(relativeOrFullPath); } \
          \
          template <> \
          void unloadAll<##ResourceType##>() { LoaderMemberName.unloadAllResources(); } \
          \
          using ResourceType##Loader = ResourceLoader<##ResourceType##>; \
          \
        protected: \
          ResourceType##Loader LoaderMemberName;

      // Have directory tree filesystem thing, where it will update all child nodes too?
      DEFINE_RESOURCE(VertexShader, m_vertexShaders)
      DEFINE_RESOURCE(FragmentShader, m_fragmentShaders)
      DEFINE_RESOURCE(Sound, m_sounds)
      DEFINE_RESOURCE(Data, m_data)
      DEFINE_RESOURCE(Texture2D, m_textures)
      DEFINE_RESOURCE(Font, m_fonts)
      DEFINE_RESOURCE(Prefab, m_prefabs)
      DEFINE_RESOURCE(Model, m_models)

    private:
      using Inherited = Entity;

      Path m_resourcesDirectory;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ResourceManager::isLoaded(const Path& relativeOrFullPath) const
  {
    STATIC_ASSERT_FAIL("Is Loaded not implemented for inputted type.");
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T* ResourceManager::load(const Path& relativeOrFullPath)
  {
    STATIC_ASSERT_FAIL("Load not implemented for inputted type.");
    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceManager::unload(const Path& relativeOrFullPath)
  {
    STATIC_ASSERT_FAIL("Unload not implemented for inputted type.");
    return;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceManager::unloadAll()
  {
    STATIC_ASSERT_FAIL("UnloadAll not implemented for inputted type.");
    return;
  }
}