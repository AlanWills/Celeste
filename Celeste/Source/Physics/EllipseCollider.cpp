#include "Physics/EllipseCollider.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Maths/Rectangle.h"
#include "Maths/Ray.h"


namespace Celeste::Physics
{
  REGISTER_MANAGED_COMPONENT(EllipseCollider, 10)

  //------------------------------------------------------------------------------------------------
  EllipseCollider::EllipseCollider(GameObject& gameObject) :
    Inherited(gameObject),
    m_unscaledDimensions(),
    m_ellipse()
  {
    sync();
  }

  //------------------------------------------------------------------------------------------------
  void EllipseCollider::update(float secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    sync();
  }

  //------------------------------------------------------------------------------------------------
  void EllipseCollider::onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset)
  {
    m_ellipse.m_centre += (newOffset - oldOffset);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 EllipseCollider::getDimensions() const
  {
    observer_ptr<const Transform> transform = getTransform();
    return transform != nullptr ? (m_unscaledDimensions * glm::vec2(transform->getWorldScale())) : m_unscaledDimensions;
  }

  //------------------------------------------------------------------------------------------------
  void EllipseCollider::setDimensions(const glm::vec2& dimensions)
  {
    m_unscaledDimensions = dimensions;

    observer_ptr<const Transform> transform = getTransform();
    m_ellipse.m_dimensions = transform != nullptr ? (m_unscaledDimensions * glm::vec2(transform->getWorldScale())) : m_unscaledDimensions;
  }

  //------------------------------------------------------------------------------------------------
  void EllipseCollider::sync()
  {
    observer_ptr<const Transform> transform = getTransform();

#if _DEBUG
    if (transform == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    m_ellipse.m_centre = glm::vec2(transform->getWorldTranslation()) + getOffset();
    m_ellipse.m_dimensions = transform != nullptr ? (m_unscaledDimensions * glm::vec2(transform->getWorldScale())) : m_unscaledDimensions;
  }

  //------------------------------------------------------------------------------------------------
  bool EllipseCollider::intersects(const Maths::Ray& ray) const
  {
    observer_ptr<const Transform> transform = getTransform();

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
  bool EllipseCollider::intersects(const glm::vec2& point) const
  {
    // https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    glm::vec2 scaledDimensions = getDimensions();

    return (scaledDimensions.y * scaledDimensions.y * (point.x - m_ellipse.m_centre.x) * (point.x - m_ellipse.m_centre.x) +
      scaledDimensions.x * scaledDimensions.x * (point.y - m_ellipse.m_centre.y) * (point.y - m_ellipse.m_centre.y))
      <=
      scaledDimensions.x * scaledDimensions.x * scaledDimensions.y * scaledDimensions.y;
  }

  //------------------------------------------------------------------------------------------------
  bool EllipseCollider::intersects(const Maths::Rectangle& rectangle) const
  {
    // First make a bounding rectangle for this ellipse to simplify calculations
    Maths::Rectangle boundingRectangle(getCentre(), getDimensions());
    if (boundingRectangle.intersects(rectangle))
    {
      return true;
    }

    // TODO proper ellipse collision - currently just rectangle rectangle
    return false;
  }

  //------------------------------------------------------------------------------------------------
  bool EllipseCollider::intersects(const Maths::Ellipse& ellipse) const
  {
    // TODO
    return false;
  }
}