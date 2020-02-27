#include "Physics/Collider.h"
#include "Physics/RectangleCollider.h"
#include "Physics/EllipseCollider.h"
#include "Maths/Ray.h"


namespace Celeste::Physics
{
  //------------------------------------------------------------------------------------------------
  Collider::Collider() :
    m_colliderType(ColliderType::kCollider),
    m_hitByRay(false),
    m_offset()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Collider::intersects(const Collider& collider) const
  {
    if (const RectangleCollider* rectangleCollider = dynamic_cast<const RectangleCollider*>(&collider); rectangleCollider != nullptr)
    {
      return intersects(rectangleCollider->getRectangle());
    }
    else if (const EllipseCollider* ellipseCollider = dynamic_cast<const EllipseCollider*>(&collider); ellipseCollider != nullptr)
    {
      return intersects(ellipseCollider->getEllipse());
    }

    ASSERT_FAIL();
    return false;
  }
}