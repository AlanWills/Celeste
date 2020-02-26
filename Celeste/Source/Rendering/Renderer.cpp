#include "Rendering/Renderer.h"
#include "Maths/Transform.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  Renderer::Renderer() :
    m_origin(0.5f),
    m_colour(1, 1, 1, 1),
    m_scissorRectangle()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Renderer::onDeath()
  {
    Inherited::onDeath();

    m_origin = glm::vec2(0.5f);
    m_colour = glm::vec4(1);
    m_scissorRectangle = Maths::Rectangle();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 Renderer::getScaledDimensions() const
  {
    return getDimensions() * glm::vec2(getTransform()->getScale());
  }
}