#pragma once

#include "Objects/Component.h"
#include "LayoutEnums.h"
#include "glm/glm.hpp"


namespace Celeste::Rendering
{
  class Renderer;
}

namespace Celeste::UI
{
  class StackPanel : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(StackPanel, CelesteDllExport)

    public:
      template <typename ...Children>
      void addChildren(GameObject& gameObject, Children&... gameObjects);
      CelesteDllExport void addChildren(GameObject& gameObject);

      template <typename ...Children>
      void removeChildren(GameObject& gameObject, Children&... gameObjects);
      CelesteDllExport void removeChildren(GameObject& gameObject);

      CelesteDllExport void clearChildren();

      inline size_t childCount() const { return m_children.size(); }

      inline Orientation getOrientation() const { return m_orientation; }
      inline void setOrientation(Orientation orientation) { m_orientation = orientation; }

      inline UI::HorizontalAlignment getHorizontalAlignment() const { return m_horizontalAlignment; }
      inline void setHorizontalAlignment(UI::HorizontalAlignment horizontalAlignment) { m_horizontalAlignment = horizontalAlignment; }

      inline UI::VerticalAlignment getVerticalAlignment() const { return m_verticalAlignment; }
      inline void setVerticalAlignment(UI::VerticalAlignment verticalAlignment) { m_verticalAlignment = verticalAlignment; }

      inline float getPadding() const { return m_padding; }
      inline void setPadding(float padding) { m_padding = padding; }

      inline observer_ptr<GameObject> getChild(size_t index) { return index < m_children.size() ? m_children[index] : nullptr; }
      inline observer_ptr<const GameObject> getChild(size_t index) const
      {
        const_cast<StackPanel*>(this)->getChild(index);
      }

      /// Update all positions of the objects within the stack panel
      CelesteDllExport void layout() const;

    private:
      using Inherited = Component;

      static glm::vec2 getVisibleDimensions(observer_ptr<Rendering::Renderer> renderer);

      Orientation m_orientation;
      UI::HorizontalAlignment m_horizontalAlignment;
      UI::VerticalAlignment m_verticalAlignment;
      float m_padding;

      std::vector<observer_ptr<GameObject>> m_children;
  };

  //------------------------------------------------------------------------------------------------
  template <typename ...Children>
  void StackPanel::addChildren(GameObject& gameObject, Children&... gameObjects)
  {
    addChildren(gameObject);
    addChildren(gameObjects...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename ...Children>
  void StackPanel::removeChildren(GameObject& gameObject, Children&... gameObjects)
  {
    removeChildren(gameObject);
    removeChildren(gameObjects...);
  }
}