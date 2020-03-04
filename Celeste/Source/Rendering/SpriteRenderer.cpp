#include "Rendering/SpriteRenderer.h"
#include "Screens/ScreenManager.h"
#include "Resources/ResourceManager.h"
#include "UtilityHeaders/ComponentHeaders.h"

using namespace Celeste::Resources;


namespace Celeste::Rendering
{
  REGISTER_UNMANAGED_COMPONENT(SpriteRenderer, 50)

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer() :
    m_texture(nullptr),
    m_dimensions(),
    m_preserveAspectRatio(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::render(const Program& shaderProgram, const glm::mat4& viewModelMatrix) const
  {
    if (m_texture == nullptr)
    {
      return;
    }

    const Maths::Rectangle& rectangle = getScissorRectangle();
    const glm::vec2& getDimensions = rectangle.getDimensions();
    if (getDimensions != glm::vec2())
    {
      glEnable(GL_SCISSOR_TEST);
      glScissor(
        static_cast<GLint>(viewModelMatrix[3].x + rectangle.getLeft().x),
        static_cast<GLint>(viewModelMatrix[3].y + rectangle.getBottom().y),
        static_cast<GLsizei>(getDimensions.x),
        static_cast<GLsizei>(getDimensions.y));
    }

    shaderProgram.setVector4f("colour", getColour());
    shaderProgram.setMatrix4("view_model", viewModelMatrix * glm::translate(glm::mat4(), glm::vec3(-getOrigin(), 0)));

    m_texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_texture->unbind();

    glDisable(GL_SCISSOR_TEST);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setTexture(const Path& textureRelativeString)
  {
    setTexture(getResourceManager().load<Texture2D>(textureRelativeString));
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setTexture(Texture2D* texture)
  {
    // Make ready for the new texture
    m_texture = texture;

    if (texture != nullptr && m_dimensions == glm::vec2())
    {
      // Set the dimensions if they are unset
      // Do not need to call setDimensions, because setting to texture dimensions
      // will automatically preserve aspect ratio
      m_dimensions = m_texture->getDimensions();
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setDimensions(const glm::vec2& dimensions)
  {
    if (m_texture == nullptr || !m_preserveAspectRatio)
    {
      m_dimensions = dimensions;
      return;
    }

    const glm::vec2& imageDimensions = m_texture->getDimensions();
    ASSERT(imageDimensions.x > 0 && imageDimensions.y > 0);

    // We wish to maintain the aspect ratio of the object we are rendering
    m_dimensions = (std::min)(dimensions.x / imageDimensions.x, dimensions.y / imageDimensions.y) * imageDimensions;
  }
}