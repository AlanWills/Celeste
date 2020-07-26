#pragma once

#include "Resources/ResourceLoader.h"
#include "TestResources/TestResources.h"


namespace CelesteMocks
{
  template <typename T>
  class MockResourceLoader : public Celeste::Resources::ResourceLoader<T>
  {
    public:
      MockResourceLoader(size_t length) : Celeste::Resources::ResourceLoader<T>(length, TestResources::getMockResourcesDirectory()) { }
      MockResourceLoader(size_t length, const Celeste::Path& directory) : Celeste::Resources::ResourceLoader<T>(length, directory) { }
      ~MockResourceLoader() { }

      const typename Celeste::Resources::ResourceLoader<T>::Map& getMap() const { return Celeste::Resources::ResourceLoader<T>::m_map; }
      const typename Celeste::Resources::ResourceLoader<T>::Memory& getMemory() const { return Celeste::Resources::ResourceLoader<T>::m_memory; }

      bool inMapRelative(const Celeste::Path& relativePath) { return getMap().end() != getMap().find(string_id(Celeste::Path(Celeste::Resources::ResourceLoader<T>::getResourceDirectoryPath(), relativePath).as_string())); }

      bool inMapFull(const Celeste::Path& fullPath) { return getMap().end() != getMap().find(string_id(fullPath.as_string())); }
  };
}