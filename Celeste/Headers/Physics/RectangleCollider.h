#pragma once

#include "Collider.h"
#include "Maths/Rectangle.h"


namespace Celeste::Maths
{
  class Ray;
  class Ellipse;
}

namespace Celeste::Physics
{
  class RectangleCollider : public Collider
  {
    DECLARE_MANAGED_COMPONENT(RectangleCollider, PhysicsManager, CelesteDllExport)

    public:
      using Collider::intersects;

      CelesteDllExport bool intersects(const Maths::Ray& ray) const override;
      inline bool intersects(const glm::vec2& point) const override { return m_rectangle.contains(point); }
      inline bool intersects(const Maths::Rectangle& rectangle) const override { return m_rectangle.intersects(rectangle); }
      CelesteDllExport bool intersects(const Maths::Ellipse& ellipse) const override;

      CelesteDllExport glm::vec2 getDimensions() const;
      void setDimensions(float x, float y) { setDimensions(glm::vec2(x, y)); }
      CelesteDllExport void setDimensions(const glm::vec2& dimensions);

      inline glm::vec2 getCentre() const override { return m_rectangle.getCentre(); }
      inline glm::vec2 getLeft() const { return m_rectangle.getLeft(); }
      inline glm::vec2 getTop() const { return m_rectangle.getTop(); }
      inline glm::vec2 getRight() const { return m_rectangle.getRight(); }
      inline glm::vec2 getBottom() const { return m_rectangle.getBottom(); }
      inline const Maths::Rectangle& getRectangle() const { return m_rectangle; }
      inline float getWidth() const { return m_rectangle.getDimensions().x; }
      inline float getHeight() const { return m_rectangle.getDimensions().y; }

      /// Use the attached game object to ensure the collider's values are up to date
      CelesteDllExport void sync();

      CelesteDllExport void update(float secondsPerUpdate) override;

    protected:
      void onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset) override;

    private:
      using Inherited = Collider;

      glm::vec2 m_dimensions;
      Maths::Rectangle m_rectangle;
  };
}