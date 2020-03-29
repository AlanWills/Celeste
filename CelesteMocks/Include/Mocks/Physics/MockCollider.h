#pragma once

#include "StaticLibExport.h"
#include "Physics/Collider.h"


namespace Celeste::Maths
{
  class Ray;
  class Rectangle;
  class Ellipse;
}

namespace Celeste::Physics
{
  class PhysicsManager;
}

namespace CelesteMocks
{
  class MockCollider : public Celeste::Physics::Collider
  {
    DECLARE_MANAGED_COMPONENT(MockCollider, Celeste::Physics::PhysicsManager, StaticLibExport)

    public:
      glm::vec2 getCentre() const { return glm::vec2(); }

      void setIntersectsRayResult(bool intersectsRay) { m_intersectsRayResult = intersectsRay; }
      void setIntersectsPointResult(bool intersectsPoint) { m_intersectsPointResult = intersectsPoint; }
      void setIntersectsRectangleResult(bool intersectsRectangle) { m_intersectsRectangleResult = intersectsRectangle; }
      void setIntersectsEllipseResult(bool intersectsEllipse) { m_intersectsEllipseResult = intersectsEllipse; }

      bool intersects(const Celeste::Maths::Ray&) const override { return m_intersectsRayResult; }
      bool intersects(const glm::vec2&) const override { return m_intersectsPointResult; }
      bool intersects(const Celeste::Maths::Rectangle&) const override { return m_intersectsRectangleResult; }
      bool intersects(const Celeste::Maths::Ellipse&) const override { return m_intersectsEllipseResult; }

      bool isOnSetOffsetCalled() const { return m_onSetOffSetCalled; }

      void reset()
      {
        m_onSetOffSetCalled = false;
      }

    protected:
      void onSetOffset(const glm::vec2& /*oldOffset*/, const glm::vec2& /*newOffset*/) override
      {
        m_onSetOffSetCalled = true;
      }

    private:
      using Inherited = Celeste::Physics::Collider;

      bool m_onSetOffSetCalled;
      bool m_intersectsRayResult = false;
      bool m_intersectsPointResult = false;
      bool m_intersectsRectangleResult = false;
      bool m_intersectsEllipseResult = false;
  };
}