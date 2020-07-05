#include "Rendering/SpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "UtilityHeaders/ComponentHeaders.h"

using namespace Celeste::Resources;


namespace Celeste::Rendering
{
  REGISTER_COMPONENT(SpriteRenderer, 50)

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer(GameObject& gameObject) :
    Inherited(gameObject),
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
    const glm::vec2& dimensions = rectangle.getDimensions();

    if (dimensions != glm::vec2())
    {
      glEnable(GL_SCISSOR_TEST);
      glScissor(
        static_cast<GLint>(viewModelMatrix[3].x + rectangle.getLeft().x),
        static_cast<GLint>(viewModelMatrix[3].y + rectangle.getBottom().y),
        static_cast<GLsizei>(dimensions.x),
        static_cast<GLsizei>(dimensions.y));
    }

    shaderProgram.setVector4f("colour", getColour());
    shaderProgram.setMatrix4("view_model", viewModelMatrix * glm::translate(glm::identity<glm::mat4>(), glm::vec3(-getOrigin(), 0)));

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
    m_texture = texture;

    if (m_texture == nullptr)
    {
      return;
    }

    if (glm::zero<glm::vec2>() == m_dimensions)
    {
      // Don't have dimensions specified
      m_dimensions = m_texture->getDimensions();
    }
    else if (m_preserveAspectRatio)
    {
      updateDimensionsForAspectRatio(m_texture->getDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setDimensions(const glm::vec2& dimensions)
  {
    m_dimensions = dimensions;

    if (m_texture != nullptr && m_preserveAspectRatio)
    {
      updateDimensionsForAspectRatio(m_texture->getDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::updateDimensionsForAspectRatio(const glm::vec2& imageDimensions)
  {
    ASSERT(imageDimensions.x > 0 && imageDimensions.y > 0);

    // We wish to maintain the aspect ratio of the object we are rendering
    m_dimensions = (std::min)(m_dimensions.x / imageDimensions.x, m_dimensions.y / imageDimensions.y) * imageDimensions;
  }
}