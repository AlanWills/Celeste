#include "Rendering/SpriteBatch.h"
#include "Resources/ResourceManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "OpenGL/GL.h"
#include "OpenGL/ManagedGLBuffer.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  SpriteBatch::SpriteBatch() :
    m_cameraProjectionMatrix(),
    m_cameraViewMatrix(),
    m_program(),
    m_vao(static_cast<GLuint>(0))
  {
  }

  //------------------------------------------------------------------------------------------------
  SpriteBatch::~SpriteBatch()
  {
    destroy();
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::initialize()
  {
    std::string spriteVertexShaderCode(
      "#version 140 \n \
        attribute vec2 position; \n \
        attribute vec2 texCoord; \n \
        \n \
        out vec2 TexCoord; \n \
        \n \
        uniform mat4 projection; \n \
        uniform mat4 view_model; \n \
        \n \
        void main() \n \
        { \n \
          TexCoord = texCoord; \n \
          gl_Position = projection * view_model * vec4(position.xy, 0.0f, 1.0f); \n \
        }");

    std::string spriteFragmentShaderCode(
      "#version 140 \n \
        in vec2 TexCoord; \n \
        \n \
        out vec4 color; \n \
        \n \
        // Texture samplers \n \
        uniform sampler2D sprite; \n \
        uniform vec4 colour; \n \
        \n \
        void main() \n \
        { \n \
          color = colour * texture(sprite, TexCoord); \n \
        }");

    m_program.createFromCode(spriteVertexShaderCode, spriteFragmentShaderCode);

    GLfloat vertices[24] = {
      0, 0, 0, 1,
      0, 1, 0, 0,
      1, 1, 1, 0,
      0, 0, 0, 1,
      1, 1, 1, 0,
      1, 0, 1, 1,
    };

    // This object will take care of delete the temporary VBO when it goes out of scope
    GLUtility::ManagedGLBuffer managedVBO;
    if (!managedVBO.allocate())
    {
      ASSERT_FAIL();
      return;
    }

    // Generate the vertex attribute array for the text rendering
    if (!GL::genVertexArray(m_vao))
    {
      ASSERT_FAIL();
      return;
    }

    bindVertexArray();
    glBindBuffer(GL_ARRAY_BUFFER, managedVBO.getBuffer());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(m_program.getAttributeLocation("position"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(m_program.getAttributeLocation("texCoord"), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unbindVertexArray();
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::destroy()
  {
    if (GL::isVertexArray(m_vao))
    {
      GL::deleteVertexArray(m_vao);
    }

    m_vao = 0;
    m_program.destroy();
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::begin(const glm::mat4& cameraProjectionMatrix, const glm::mat4& cameraViewMatrix)
  {
    m_cameraProjectionMatrix = cameraProjectionMatrix;
    m_cameraViewMatrix = cameraViewMatrix;
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::end()
  {
    if (GL::isVertexArray(m_vao))
    {
      m_program.bind();
      m_program.setMatrix4("projection", m_cameraProjectionMatrix);

      glActiveTexture(GL_TEXTURE0);
      bindVertexArray();

      for (const RenderPair& renderPair : m_renderers)
      {
        renderPair.first->render(m_program, m_cameraViewMatrix * renderPair.second);
      }

      unbindVertexArray();
      glBindTexture(GL_TEXTURE_2D, 0);

      m_renderers.clear();
      m_program.unbind();
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::render(Renderer& renderer, const glm::mat4& renderMatrix)
  {
    m_renderers.insert(std::make_pair(&renderer, renderMatrix));
  }

  //------------------------------------------------------------------------------------------------
  void SpriteBatch::render(Renderer& renderer, const glm::vec3& translation, float rotation, const glm::vec3& scale)
  {
    m_renderers.insert(std::make_pair(&renderer, createMatrix(translation, rotation, scale)));
  }
}