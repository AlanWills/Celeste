#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Maths
{
  class Ray;
  class Rectangle;
  class Ellipse;
}

namespace Celeste::Physics
{
  enum class ColliderType
  {
    kTrigger = true,
    kCollider = false
  };

  class Collider : public Component
  {
    public:
      CelesteDllExport Collider();

      virtual glm::vec2 getCentre() const = 0;

      inline ColliderType getColliderType() const { return m_colliderType; }
      inline void setColliderType(ColliderType colliderType) { m_colliderType = colliderType; }

      inline bool isHitByRay() const { return m_hitByRay; }
      inline void setHitByRay(bool isHitByRay) { m_hitByRay = isHitByRay; }

      inline const glm::vec2& getOffset() const { return m_offset; }
      inline void setOffset(float x, float y) { setOffset(glm::vec2(x, y)); }
      inline void setOffset(const glm::vec2& offset)
      {
        onSetOffset(m_offset, offset);
        m_offset = offset;
      }

      virtual bool intersects(const Maths::Ray& ray) const = 0;
      virtual bool intersects(const glm::vec2& point) const = 0;
      virtual bool intersects(const Maths::Rectangle& collider) const = 0;
      virtual bool intersects(const Maths::Ellipse& ellipse) const = 0;
      CelesteDllExport bool intersects(const Collider& collider) const;

    protected:
      virtual void onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset) = 0;

    private:
      using Inherited = Component;

      ColliderType m_colliderType;
      bool m_hitByRay;
      glm::vec2 m_offset;
  };
}