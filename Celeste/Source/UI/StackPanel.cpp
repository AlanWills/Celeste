#include "UI/StackPanel.h"
#include "Rendering/Renderer.h"
#include "UtilityHeaders/ComponentHeaders.h"

using namespace Celeste::Rendering;


namespace Celeste::UI
{
  REGISTER_COMPONENT(StackPanel, 10)

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

    if (&gameObject == &getGameObject())
    {
      // Cannot add parent to ourself
      ASSERT_FAIL();
      return;
    }
#endif

    gameObject.setParent(&getGameObject());
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
    float currentPosition = 0;

    if (m_orientation == Orientation::kHorizontal)
    {
      for (observer_ptr<GameObject> child : m_children)
      {
        if (observer_ptr<Renderer> renderer = child->findComponent<Renderer>(); renderer->isActive())
        {
          if (child != *firstVisible)
          {
            currentPosition += m_padding * 0.5f;
          }

          float width = getVisibleDimensions(renderer).x;
          float position = currentPosition + width * 0.5f;

          if (m_horizontalAlignment == HorizontalAlignment::kCentre)
          {
            position -= totalSize.x * 0.5f;
          }
          else if (m_horizontalAlignment == HorizontalAlignment::kRight)
          {
            position *= -1;
          }

          observer_ptr<Transform> transform = child->getTransform();
          transform->setTranslation(glm::vec3(position, transform->getTranslation().y, transform->getTranslation().z));

          currentPosition += width;
          
          if (child != *lastVisible)
          {
            currentPosition += m_padding * 0.5f;
          }
        }
      }
    }
    else
    {
      for (observer_ptr<GameObject> child : m_children)
      {
        if (observer_ptr<Renderer> renderer = child->findComponent<Renderer>(); renderer->isActive())
        {
          if (child != *firstVisible)
          {
            currentPosition += m_padding * 0.5f;
          }

          float height = getVisibleDimensions(renderer).y;
          float position = currentPosition + height * 0.5f;

          if (m_verticalAlignment == VerticalAlignment::kCentre)
          {
            position -= totalSize.y * 0.5f;
            position *= -1; // Vertical centre adds elements at the top first
          }
          else if (m_verticalAlignment == VerticalAlignment::kTop)
          {
            position *= -1;
          }

          observer_ptr<Transform> transform = child->getTransform();
          transform->setTranslation(glm::vec3(transform->getTranslation().x, position, transform->getTranslation().z));

          currentPosition += height;

          if (child != *lastVisible)
          {
            currentPosition += m_padding * 0.5f;
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