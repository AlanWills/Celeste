#pragma once

#include "CelesteDllExport.h"
#include "Resources/Shaders/Program.h"
#include "Resources/Resource.h"
#include "Mesh.h"
#include "FileSystem/Directory.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>


namespace Celeste::Resources
{
  class Model : public Resource
  {
    public:
      CelesteDllExport Model();

      const std::vector<Mesh>& getMeshes() const { return m_meshes; }

    protected:
      CelesteDllExport bool doLoadFromFile(const Path& filePath) override;
      CelesteDllExport void doUnload() override;

    private:
      using Inherited = Resource;

      void processNode(
        aiNode* node,
        const aiScene* scene,
        const Directory& parentDirectory,
        std::unordered_map<std::string, Texture>& textureCache);

      Mesh processMesh(
        aiMesh* mesh,
        const aiScene* scene,
        const Directory& parentDirectory,
        std::unordered_map<std::string, Texture>& textureCache);

      std::vector<Texture> loadMaterialTextures(
        aiMaterial* mat,
        aiTextureType type,
        const std::string& typeName,
        const Directory& parentDirectory,
        std::unordered_map<std::string, Texture>& textureCache);

      unsigned int textureFromFile(const Path& path, bool gamma = false);

      std::vector<Mesh> m_meshes;
  };
}