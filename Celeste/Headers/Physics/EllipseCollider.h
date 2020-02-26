#pragma once

#include "Collider.h"
#include "Maths/Ellipse.h"


namespace Celeste::Physics
{
  class EllipseCollider : public Collider
  {
    DECLARE_COMPONENT(EllipseCollider, PhysicsManager, CelesteDllExport)

    public:
      using Collider::intersects;

      CelesteDllExport bool intersects(const Maths::Ray& ray) const override;
      CelesteDllExport bool intersects(const glm::vec2& point) const override;
      CelesteDllExport bool intersects(const Maths::Rectangle& rectangle) const override;
      CelesteDllExport bool intersects(const Maths::Ellipse& ellipse) const override;

      CelesteDllExport glm::vec2 getDimensions() const;
      void setDimensions(float radius) { setDimensions(radius, radius); }
      void setDimensions(float xDimension, float yDimension) { setDimensions(glm::vec2(xDimension, yDimension)); }
      CelesteDllExport void setDimensions(const glm::vec2& dimensions);

      inline glm::vec2 getCentre() const override { return m_ellipse.m_centre; }
      inline void setCentre(const glm::vec2& centre) { m_ellipse.m_centre = centre; }

      inline const Maths::Ellipse& getEllipse() const { return m_ellipse; }

      /// Use the attached game object to ensure the collider's values are up to date
      CelesteDllExport void sync();

    protected:
      CelesteDllExport void onSetGameObject(GameObject& gameObject) override;
      CelesteDllExport void onUpdate(float secondsPerUpdate) override;
      CelesteDllExport void onSetOffset(const glm::vec2& oldOffset, const glm::vec2& newOffset) override;
      CelesteDllExport void onDeath() override;

    private:
      using Inherited = Collider;

      glm::vec2 m_unscaledDimensions;
      Maths::Ellipse m_ellipse;
  };
}