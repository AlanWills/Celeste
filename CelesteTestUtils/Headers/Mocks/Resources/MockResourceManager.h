#pragma once

#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"

using namespace Celeste;


namespace CelesteTestUtils
{
  class MockResourceManager : public Celeste::Resources::ResourceManager
  {
    public:
      MockResourceManager() : Celeste::Resources::ResourceManager(Celeste::Resources::getResourcesDirectory()) { }
      ~MockResourceManager() { }

      const VertexShaderLoader& getVertexShaderLoader() const { return m_vertexShaders; }
      const FragmentShaderLoader& getFragmentShaderLoader() const { return m_fragmentShaders; }
      const Texture2DLoader& getTexture2DLoader() const { return m_textures; }
      const FontLoader& getFontLoader() const { return m_fonts; }
      const SoundLoader& getSoundLoader() const { return m_sounds; }
      const DataLoader& getDataLoader() const { return m_data; }
      const PrefabLoader& getPrefabLoader() const { return m_prefabs; }
      const ModelLoader& getModelLoader() const { return m_models; }
  };
}