#include "UI/ProgressBar.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/SpriteRenderer.h"


namespace Celeste::UI
{
  REGISTER_COMPONENT(ProgressBar, 4)

  //------------------------------------------------------------------------------------------------
  ProgressBar::ProgressBar(GameObject& gameObject) :
    Inherited(gameObject),
    m_spriteRenderer(gameObject.findComponent<Rendering::SpriteRenderer>()),
    m_progress(0),
    m_min(0),
    m_max(100)
  {
  }

  //------------------------------------------------------------------------------------------------
  void ProgressBar::setMin(float min)
  {
    m_min = min;
    setProgress(min);
  }

  //------------------------------------------------------------------------------------------------
  void ProgressBar::setMax(float max)
  {
    m_max = max;
    setProgress(m_progress);  // Triggers UI update
  }

  //------------------------------------------------------------------------------------------------
  void ProgressBar::setProgress(float progress)
  {
    m_progress = glm::clamp(progress, m_min, m_max);

#if _DEBUG
    if (m_spriteRenderer == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    auto scaledDimensions = m_spriteRenderer->getDimensions() * glm::vec2(m_spriteRenderer->getTransform()->getWorldScale());
    m_spriteRenderer->getScissorRectangle().setDimensions(0, scaledDimensions.y);
    m_spriteRenderer->getScissorRectangle().setCentre(-scaledDimensions.x * 0.5f, 0);

    float newWidth = (m_max > m_min) ? (scaledDimensions.x * (m_progress - m_min)) / (m_max - m_min) : 0;
    m_spriteRenderer->getScissorRectangle().stretchWidth(newWidth, UI::HorizontalAlignment::kLeft);
  }
}