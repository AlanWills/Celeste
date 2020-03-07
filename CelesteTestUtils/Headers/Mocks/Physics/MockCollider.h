#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Physics/Collider.h"


namespace Celeste::Maths
{
  class Ray;
  class Rectangle;
  class Ellipse;
}

namespace CelesteTestUtils
{
  class MockCollider : public Celeste::Physics::Collider
  {
    DECLARE_UNMANAGED_COMPONENT(MockCollider, CelesteTestUtilsDllExport)

    public:
      glm::vec2 getCentre() const { return glm::vec2(); }

      bool intersects(const Celeste::Maths::Ray&) const override { return false; }
      bool intersects(const glm::vec2&) const override { return false; }
      bool intersects(const Celeste::Maths::Rectangle&) const override { return false; }
      bool intersects(const Celeste::Maths::Ellipse&) const override { return false; }

      bool isOnSetOffsetCalled() const { return m_onSetOffSetCalled; }

      void reset()
      {
        m_onSetOffSetCalled = false;
      }

    protected:
      void onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset) override
      {
        m_onSetOffSetCalled = true;
      }

    private:
      using Inherited = Celeste::Physics::Collider;

      bool m_onSetOffSetCalled;
  };
}