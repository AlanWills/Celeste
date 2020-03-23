#include "Maths/Rectangle.h"
#include "Maths/Ray.h"


namespace Celeste::Maths
{
  //------------------------------------------------------------------------------------------------
  Rectangle::Rectangle() : 
    m_centre(0, 0), 
    m_dimensions(0, 0)
  {
  }

  //------------------------------------------------------------------------------------------------
  Rectangle::Rectangle(const glm::vec2& getCentre, const glm::vec2& getDimensions) : 
    m_centre(getCentre), 
    m_dimensions(getDimensions) 
  {
  }

  //------------------------------------------------------------------------------------------------
  Rectangle::Rectangle(float centre_x, float centre_y, float width, float height) :
    m_centre(centre_x, centre_y),
    m_dimensions(width, height)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Rectangle::contains(const glm::vec2& point) const
  {
    // Not equal to
    // This corresponds to an open set and allows us to place colliders next to each other with no intersection
    glm::vec2 halfDims = m_dimensions * 0.5f;

    return ((m_centre.x - halfDims.x) < point.x) &&
           ((m_centre.x + halfDims.x) > point.x) &&
           ((m_centre.y - halfDims.y) < point.y) &&
           ((m_centre.y + halfDims.y) > point.y);
  }

  //------------------------------------------------------------------------------------------------
  bool Rectangle::intersects(const Rectangle& rectangle) const
  {
    if (rectangle.getDimensions() == glm::zero<glm::vec2>() ||
      m_dimensions == glm::zero<glm::vec2>())
    {
      return false;
    }

    // Bottom answer
    // http://stackoverflow.com/questions/13390333/two-rectangles-intersection

    // Not equal to
    // This corresponds to an open set and allows us to place colliders next to each other with no intersection
    return getRight().x > rectangle.getLeft().x &&
            getLeft().x < rectangle.getRight().x &&
            getTop().y > rectangle.getBottom().y &&
            getBottom().y < rectangle.getTop().y;
  }
}