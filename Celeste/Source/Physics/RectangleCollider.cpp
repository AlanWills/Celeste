#include "Physics/RectangleCollider.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Maths/Transform.h"
#include "Maths/Ray.h"
#include "Maths/Ellipse.h"


namespace Celeste::Physics
{
  REGISTER_COMPONENT(RectangleCollider, 50)

  //------------------------------------------------------------------------------------------------
  RectangleCollider::RectangleCollider(GameObject& gameObject) :
    Inherited(gameObject),
    m_rectangle(),
    m_dimensions()
  {
    sync();
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    sync();
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset)
  {
    m_rectangle.setCentre(m_rectangle.getCentre() + newOffset - oldOffset);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 RectangleCollider::getDimensions() const
  {
    const Transform* transform = getTransform();
    return transform != nullptr ? (m_dimensions * glm::vec2(transform->getWorldScale())) : m_dimensions;
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::setDimensions(const glm::vec2& dimensions)
  {
    m_dimensions = dimensions;

    const Transform* transform = getTransform();
    m_rectangle.setDimensions(transform != nullptr ? (m_dimensions * glm::vec2(transform->getWorldScale())) : m_dimensions);
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::sync()
  {
    const Transform* transform = getTransform();

#if _DEBUG
    if (transform == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    m_rectangle.setCentre(glm::vec2(transform->getWorldTranslation()) + getOffset());
    m_rectangle.setDimensions(m_dimensions * glm::vec2(transform->getWorldScale()));
  }

  //------------------------------------------------------------------------------------------------
  bool RectangleCollider::intersects(const Maths::Ray& ray) const
  {
    const Transform* transform = getTransform();

#if _DEBUG
    if (transform == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }
#endif

    // Calculate the point of intersection in the z plane our transform is on
    // For now we are assuming all textures are perpendicular to z
    // We also do not handle rotation at the moment (should be ok - just rotate the dims vector
    glm::vec3 translation = transform->getWorldTranslation();

    float t = (translation.z - ray.m_origin.z) / ray.m_direction.z;
    glm::vec2 intersectPoint(ray.m_origin.x + t * ray.m_direction.x, ray.m_origin.y + t * ray.m_direction.y);

    return intersects(intersectPoint);
  }

  //------------------------------------------------------------------------------------------------
  bool RectangleCollider::intersects(const Maths::Ellipse& ellipse) const
  {
    // First make a bounding rectangle for this ellipse to simplify calculations
    Maths::Rectangle boundingRectangle(ellipse.m_centre, ellipse.m_dimensions);
    if (m_rectangle.intersects(boundingRectangle))
    {
      return true;
    }

    // TODO proper ellipse collision - currently just rectangle rectangle
    return false;
  }
}