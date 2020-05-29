#include "Debug/Profiling/FPSCounter.h"
#include "Rendering/TextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Time/TimeUtils.h"


namespace Celeste::Debugging
{
  REGISTER_COMPONENT(FPSCounter, 1)

  //------------------------------------------------------------------------------------------------
  FPSCounter::FPSCounter(GameObject& gameObject) :
    Inherited(gameObject),
    m_textRenderer(gameObject.findComponent<Celeste::Rendering::TextRenderer>()),
    m_current(0)
  {
    ASSERT_NOT_NULL(m_textRenderer);
  }

  //------------------------------------------------------------------------------------------------
  void FPSCounter::update()
  {
    Inherited::update();

#if _DEBUG
    if (m_textRenderer == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    float elapsedGameTime = Time::getElapsedDeltaTime();
    m_current += elapsedGameTime;

    if (m_current > 0.5f)
    {
      size_t fps = static_cast<size_t>(1 / elapsedGameTime);
      m_textRenderer->setText(std::to_string(fps));
      m_current = 0;
    }
  }
}