#pragma once

#include "Vertex.h"
#include "Texture.h"
#include "CelesteDllExport.h"
#include "Resources/Shaders/Program.h"

#include <vector>


namespace Celeste
{
  namespace Resources
  {
    class Mesh
    {
      public:
        CelesteDllExport Mesh();

        const std::vector<Vertex>& getVertices() const { return m_vertices; }
        const std::vector<unsigned int> getIndices() const { return m_indices; }
        const std::vector<Texture> getTextures() const { return m_textures; }

        CelesteDllExport void load(
          const std::vector<Vertex>& vertices,
          const std::vector<unsigned int>& indices,
          const std::vector<Texture>& textures);
        CelesteDllExport void unload();

        CelesteDllExport void bind(const Program& program) const;
        CelesteDllExport void unbind() const;

      private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<Texture> m_textures;

        unsigned int m_vao;
    };
  }
}