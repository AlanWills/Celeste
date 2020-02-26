#include "Resources/3D/Mesh.h"
#include "OpenGL/ManagedGLBuffer.h"
#include "OpenGL/GL.h"


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    Mesh::Mesh() :
      m_vertices(),
      m_indices(),
      m_textures(),
      m_vao(0)
    {
    }

    //------------------------------------------------------------------------------------------------
    void Mesh::load(
      const std::vector<Vertex>& vertices,
      const std::vector<unsigned int>& indices,
      const std::vector<Texture>& textures)
    {
      m_vertices.assign(vertices.begin(), vertices.end());
      m_indices.assign(indices.begin(), indices.end());
      m_textures.assign(textures.begin(), textures.end());

      GLUtility::ManagedGLBuffer vbo;
      if (!vbo.allocate())
      {
        ASSERT_FAIL();
        return;
      }

      GLUtility::ManagedGLBuffer ebo;
      if (!ebo.allocate())
      {
        ASSERT_FAIL();
        return;
      }
      
      if (!GL::genVertexArray(m_vao))
      {
        ASSERT_FAIL();
        return;
      }

      glBindVertexArray(m_vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo.getBuffer());

      glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.getBuffer());
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

      // Vertex positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

      // Vertex normals
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));

      // Vertex texture coords
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texCoords));

      glBindVertexArray(0);
    }

    //------------------------------------------------------------------------------------------------
    void Mesh::unload()
    {
      if (GL::isVertexArray(m_vao))
      {
        GL::deleteVertexArray(m_vao);
        m_vao = 0;
      }

      m_vertices.clear();
      m_indices.clear();
      m_textures.clear();
    }

    //------------------------------------------------------------------------------------------------
    void Mesh::bind(const Program& program) const
    {
      unsigned int diffuseN = 1;
      unsigned int specularN = 1;

      for (size_t i = 0; i < m_textures.size(); ++i)
      {
        glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i));

        std::string number;
        const std::string& name = m_textures[i].m_type;

        if (name == "texture_diffuse")
        {
          number = std::to_string(diffuseN++);
        }
        else if (name == "texture_specular")
        {
          number = std::to_string(specularN++);
        }

        program.setInteger((name /*+ number*/).c_str(), static_cast<GLint>(i));
        glBindTexture(GL_TEXTURE_2D, m_textures[i].m_id);
      }

      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(m_vao);
    }

    //------------------------------------------------------------------------------------------------
    void Mesh::unbind() const
    {
      glBindVertexArray(0);
    }
  }
}