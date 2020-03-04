#include "Debug/Profiling/FPSCounter.h"
#include "Rendering/TextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste::Debugging
{
  REGISTER_UNMANAGED_COMPONENT(FPSCounter, 1)

  //------------------------------------------------------------------------------------------------
  FPSCounter::FPSCounter() :
    m_textRenderer(),
    m_current(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  void FPSCounter::begin()
  {
    m_begun = true;

    m_textRenderer = getGameObject()->findComponent<Celeste::Rendering::TextRenderer>();
    ASSERT(m_textRenderer != nullptr);
  }

  //------------------------------------------------------------------------------------------------
  void FPSCounter::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

#if _DEBUG
    if (m_textRenderer == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    m_current += elapsedGameTime;

    if (m_current > 0.5f)
    {
      size_t fps = static_cast<size_t>(1 / elapsedGameTime);
      m_textRenderer->setText(std::to_string(fps));
      m_current = 0;
    }
  }
}