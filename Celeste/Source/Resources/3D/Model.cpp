#include "Resources/3D/Model.h"
#include "SOIL/SOIL.h"


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    Model::Model() :
      m_meshes()
    {
    }

    //------------------------------------------------------------------------------------------------
    bool Model::doLoadFromFile(const Path& path)
    {
      Assimp::Importer importer;
      const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

      if (scene == nullptr ||
          scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
          scene->mRootNode == nullptr)
      {
        ASSERT_FAIL_MSG(importer.GetErrorString());
        return false;
      }

      std::unordered_map<std::string, Texture> textureCache;
      Directory directory(path.getParentDirectory());
      processNode(scene->mRootNode, scene, directory, textureCache);

      return true;
    }

    //------------------------------------------------------------------------------------------------
    void Model::doUnload()
    {
      for (auto& mesh : m_meshes)
      {
        mesh.unload();
      }
    }

    //------------------------------------------------------------------------------------------------
    void Model::processNode(
      aiNode* node, 
      const aiScene* scene, 
      const Directory& parentDirectory,
      std::unordered_map<std::string, Texture>& textureCache)
    {
      // Process all the node's meshes
      for (unsigned int i = 0; i < node->mNumMeshes; ++i)
      {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(processMesh(mesh, scene, parentDirectory, textureCache));
      }

      // Then do the same for each child
      for (unsigned int i = 0; i < node->mNumChildren; ++i)
      {
        processNode(node->mChildren[i], scene, parentDirectory, textureCache);
      }
    }

    //------------------------------------------------------------------------------------------------
    Mesh Model::processMesh(
      aiMesh* mesh, 
      const aiScene* scene,
      const Directory& parentDirectory,
      std::unordered_map<std::string, Texture>& textureCache)
    {
      std::vector<Vertex> vertices;
      std::vector<unsigned int> indices;
      std::vector<Texture> textures;

      for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
      {
        Vertex vertex;

        // Process vertex positions, normals and texture coordinates
        vertex.m_position.x = mesh->mVertices[i].x;
        vertex.m_position.y = mesh->mVertices[i].y;
        vertex.m_position.z = mesh->mVertices[i].z;

        if (mesh->mNormals != nullptr)
        {
          vertex.m_normal.x = mesh->mNormals[i].x;
          vertex.m_normal.y = mesh->mNormals[i].y;
          vertex.m_normal.z = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0] != nullptr)
        {
          vertex.m_texCoords.x = mesh->mTextureCoords[0][i].x;
          vertex.m_texCoords.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back(vertex);
      }

      // Process indices
      for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
      {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
          indices.push_back(face.mIndices[j]);
        }
      }

      // Process material
      if (mesh->mMaterialIndex >= 0)
      {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(
          material, 
          aiTextureType_DIFFUSE, 
          "texture_diffuse", 
          parentDirectory,
          textureCache);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(
          material, 
          aiTextureType_SPECULAR, 
          "texture_specular", 
          parentDirectory,
          textureCache);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
      }

      Mesh createdMesh;
      createdMesh.load(vertices, indices, textures);

      return std::move(createdMesh);
    }

    //------------------------------------------------------------------------------------------------
    std::vector<Texture> Model::loadMaterialTextures(
      aiMaterial* mat,
      aiTextureType type,
      const std::string& typeName,
      const Directory& parentDirectory,
      std::unordered_map<std::string, Texture>& textureCache)
    {
      std::vector<Texture> textures;
      for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
      {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        if (textureCache.find(str.C_Str()) != textureCache.end())
        {
          textures.push_back(textureCache[str.C_Str()]);
        }
        else
        {
          Texture texture;
          texture.m_id = textureFromFile(Path(parentDirectory.getDirectoryPath(), str.C_Str()));
          texture.m_type = typeName;
          texture.m_path = str.C_Str();

          textures.push_back(texture);
          textureCache.emplace(str.C_Str(), texture);
        }
      }

      return textures;
    }

    //------------------------------------------------------------------------------------------------
    unsigned int Model::textureFromFile(const Path& path, bool gamma)
    {
      unsigned int textureID;
      glGenTextures(1, &textureID);

      int width, height, nrComponents;
      unsigned char *data = SOIL_load_image(path.c_str(), &width, &height, &nrComponents, 0);
      ASSERT_NOT_NULL(data);

      if (data != nullptr)
      {
        // Use engine texture resource loading for this?
        // RawImageLoader DEFINITELY

        GLenum format;
        if (nrComponents == 1)
          format = GL_RED;
        else if (nrComponents == 3)
          format = GL_RGB;
        else if (nrComponents == 4)
          format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
      }
      
      return textureID;
    }
  }
}