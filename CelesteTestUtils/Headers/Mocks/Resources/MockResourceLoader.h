#pragma once

#include "Resources/ResourceLoader.h"
#include "Resources/TestResources.h"

using namespace Celeste;


namespace CelesteTestUtils
{
  template <typename T>
  class MockResourceLoader : public Celeste::Resources::ResourceLoader<T>
  {
    public:
      MockResourceLoader(size_t length) : Celeste::Resources::ResourceLoader<T>(length, TestResources::getMockResourcesDirectory()) { }
      MockResourceLoader(size_t length, const Path& directory) : ResourceLoader<T>(length, directory) { }
      ~MockResourceLoader() { }

      const Map& getMap() const { return m_map; }
      const Pool& getPool() const { return m_pool; }

      bool inMapRelative(const Path& relativePath) { return getMap().end() != getMap().find(internString(Path(getResourceDirectoryPath(), relativePath).as_string())); }

      bool inMapFull(const Path& fullPath) { return getMap().end() != getMap().find(internString(fullPath.as_string())); }
  };
}