#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "UI/LayoutEnums.h"


namespace Celeste::Maths
{
  class Ray;

  class Rectangle
  {
    public:
      CelesteDllExport Rectangle();
      CelesteDllExport Rectangle(const glm::vec2& centre, const glm::vec2& dimensions);
      CelesteDllExport Rectangle(float centre_x, float centre_y, float width, float height);

      const glm::vec2& getCentre() const { return m_centre; }
      const glm::vec2& getDimensions() const { return m_dimensions; }
      glm::vec2 getLeft() const { return glm::vec2(m_centre.x - m_dimensions.x * 0.5f, m_centre.y); }
      glm::vec2 getTop() const { return glm::vec2(m_centre.x, m_centre.y + m_dimensions.y * 0.5f); }
      glm::vec2 getRight() const { return glm::vec2(m_centre.x + m_dimensions.x * 0.5f, m_centre.y); }
      glm::vec2 getBottom() const { return glm::vec2(m_centre.x, m_centre.y - m_dimensions.y * 0.5f); }

      void setCentreX(float centreX) { m_centre.x = centreX; }
      void setCentreY(float centreY) { m_centre.y = centreY; }

      void setCentre(float centreX, float centreY) { setCentre(glm::vec2(centreX, centreY)); }
      void setCentre(const glm::vec2& getCentre) { m_centre = getCentre; }

      void setDimensions(float x, float y) { setDimensions(glm::vec2(x, y)); }
      void setDimensions(const glm::vec2& getDimensions) { m_dimensions = getDimensions; }

      void stretchWidth(float newWidth, UI::HorizontalAlignment anchor = UI::HorizontalAlignment::kCentre)
      {
        m_centre.x -= (static_cast<int>(anchor) - 1) * (newWidth - m_dimensions.x) * 0.5f;
        m_dimensions.x = newWidth;
      }

      void stretchHeight(float newHeight, UI::VerticalAlignment anchor = UI::VerticalAlignment::kCentre)
      {
        m_centre.y -= (static_cast<int>(anchor) - 1) * (newHeight - m_dimensions.y) * 0.5f;
        m_dimensions.y = newHeight;
      }

      CelesteDllExport bool contains(const glm::vec2& point) const;
      CelesteDllExport bool intersects(const Rectangle& point) const;

    private:
      glm::vec2 m_centre;
      glm::vec2 m_dimensions;
  };
}