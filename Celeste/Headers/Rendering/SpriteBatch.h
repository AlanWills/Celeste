#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Resources/Shaders/Program.h"

#include <set>


namespace Celeste::Rendering
{
  class Renderer;

  struct ZComparison
  {	
    typedef std::pair<Renderer*, glm::mat4> ArgType;

    bool operator()(const ArgType& lhs, const ArgType& rhs) const { return lhs.second[3].z < rhs.second[3].z; }
  };

  class SpriteBatch
  {
    public:
      CelesteDllExport SpriteBatch();

      CelesteDllExport void initialize();
      CelesteDllExport void destroy();

      CelesteDllExport void begin(const glm::mat4& cameraProjectionMatrix, const glm::mat4& cameraViewMatrix);
      CelesteDllExport void end();

      CelesteDllExport void render(Renderer& renderer, const glm::mat4& renderMatrix);
      CelesteDllExport void render(Renderer& renderer, const glm::vec3& translation, float rotation, const glm::vec3& scale);

    protected:
      size_t renderers_size() const { return m_renderers.size(); }

    private:
      using RenderPair = std::pair<Renderer*, glm::mat4>;

      void bindVertexArray() const
      {
        glCheckError();
        glBindVertexArray(m_vao);
        glCheckError();
      }

      void unbindVertexArray() const
      {
        glCheckError();
        glBindVertexArray(0);
        glCheckError();
      }

      glm::mat4 m_cameraProjectionMatrix;
      glm::mat4 m_cameraViewMatrix;

      // Maybe use a vector and sort before rendering - will need to check profiling
      // Set is good because it does spread load to insertion rather than rendering
      std::multiset<RenderPair, ZComparison> m_renderers;

      Resources::Program m_program;
      GLuint m_vao;
  };
}