#include "UI/StackPanel.h"
#include "Rendering/Renderer.h"
#include "UtilityHeaders/ComponentHeaders.h"

using namespace Celeste::Rendering;


namespace Celeste::UI
{
  REGISTER_MANAGED_COMPONENT(StackPanel, 10)

  //------------------------------------------------------------------------------------------------
  StackPanel::StackPanel(GameObject& gameObject) :
    Inherited(gameObject),
    m_orientation(Orientation::kVertical),
    m_horizontalAlignment(HorizontalAlignment::kCentre),
    m_verticalAlignment(VerticalAlignment::kCentre),
    m_padding(5)
  {
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::addChildren(GameObject& gameObject)
  {
#if _DEBUG
    if (!gameObject.hasComponent<Renderer>())
    {
      // We use the objects renderer to calculate the dimensions of an object for layout, so any object added to this must have one
      ASSERT_FAIL();
      return;
    }

    if (&gameObject == getGameObject())
    {
      // Cannot add parent to ourself
      ASSERT_FAIL();
      return;
    }
#endif

    ASSERT_NOT_NULL(getGameObject());
    gameObject.setParent(getGameObject());
    m_children.push_back(&gameObject);
    layout();
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::removeChildren(GameObject& gameObject)
  {
    auto foundChildIt = std::find(m_children.begin(), m_children.end(), &gameObject);
    if (foundChildIt != m_children.end())
    {
      m_children.erase(foundChildIt);
      layout();
    }
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::layout() const
  {
    auto visibilityPredicate = [](observer_ptr<GameObject> gameObject) { return gameObject->findComponent<Renderer>()->isActive(); };
    auto numVisible = std::count_if(m_children.begin(), m_children.end(), visibilityPredicate);

    if (numVisible == 0U)
    {
      // No visible children, so return
      return;
    }

    auto firstVisible = std::find_if(m_children.begin(), m_children.end(), visibilityPredicate);
    auto lastVisible = std::find_if(m_children.rbegin(), m_children.rend(), visibilityPredicate);

    glm::vec2 totalSize = glm::vec2();
    for (observer_ptr<GameObject> child : m_children)
    {
      if (observer_ptr<Renderer> renderer = child->findComponent<Renderer>(); renderer->isActive())
      {
        totalSize += getVisibleDimensions(renderer);
      }
    }

    totalSize += (float)(numVisible - 1) * glm::vec2(m_padding);

    if (m_orientation == Orientation::kHorizontal)
    {
      // Stack all the children horizontally with the first added on the left
      float currentLeft = 0;
      if (m_horizontalAlignment == HorizontalAlignment::kCentre)
      {
        currentLeft -= totalSize.x * 0.5f;
      }
      else if (m_horizontalAlignment == HorizontalAlignment::kRight)
      {
        currentLeft -= totalSize.x;
      }

      for (observer_ptr<GameObject> child : m_children)
      {
        if (observer_ptr<Renderer> renderer = child->findComponent<Renderer>(); renderer->isActive())
        {
          if (child != *firstVisible)
          {
            currentLeft += m_padding * 0.5f;
          }

          float halfDims = getVisibleDimensions(renderer).x * 0.5f;
          currentLeft += halfDims;

          observer_ptr<Transform> transform = child->getTransform();
          transform->setTranslation(glm::vec3(currentLeft, transform->getTranslation().y, transform->getTranslation().z));

          currentLeft += halfDims;

          if (child != *lastVisible)
          {
            currentLeft += m_padding * 0.5f;
          }
        }
      }
    }
    else
    {
      // Stack all the children vertically with the first added at the top
      float currentBottom = 0;
      if (m_verticalAlignment == VerticalAlignment::kCentre)
      {
        currentBottom -= totalSize.y * 0.5f;
      }
      else if (m_verticalAlignment == VerticalAlignment::kTop)
      {
        currentBottom -= totalSize.y;
      }

      for (observer_ptr<GameObject> child : m_children)
      {
        if (observer_ptr<Renderer> renderer = child->findComponent<Renderer>(); renderer->isActive())
        {
          if (child != *firstVisible)
          {
            currentBottom += m_padding * 0.5f;
          }

          float halfDims = getVisibleDimensions(child->findComponent<Renderer>()).y * 0.5f;
          currentBottom += halfDims;

          observer_ptr<Transform> transform = child->getTransform();
          transform->setTranslation(glm::vec3(transform->getTranslation().x, currentBottom, transform->getTranslation().z));

          currentBottom += halfDims;

          if (child != *lastVisible)
          {
            currentBottom += m_padding * 0.5f;
          }
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::clearChildren()
  {
    m_children.clear();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 StackPanel::getVisibleDimensions(observer_ptr<Rendering::Renderer> renderer)
  {
    glm::vec2 scissorRectangle = renderer->getScissorRectangle().getDimensions();
    return scissorRectangle != glm::zero<glm::vec2>() ? scissorRectangle : renderer->getDimensions();
  }
}