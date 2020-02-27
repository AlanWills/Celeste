#include "GraphicalFX/OpacityLerper.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/Renderer.h"


namespace Celeste
{
  using namespace Rendering;

  REGISTER_SCRIPT(OpacityLerper, 10)

  //------------------------------------------------------------------------------------------------
  OpacityLerper::OpacityLerper() :
    m_minOpacity(0),
    m_maxOpacity(1),
    m_lerpUpTime(1),
    m_lerpDownTime(1),
    m_maxOpacityWaitTime(0),
    m_minOpacityWaitTime(0),
    m_waitTime(0),
    m_lerpingUp(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  void OpacityLerper::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

#if _DEBUG
    if (getGameObject() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (!getGameObject()->hasComponent<Renderer>())
    {
      ASSERT_FAIL();
      return;
    }

    observer_ptr<Renderer> renderer = getGameObject()->findComponent<Renderer>();
    float currentOpacity = renderer->getOpacity();

    if (m_lerpingUp)
    {
      currentOpacity = m_lerpUpTime == 0 ? m_maxOpacity : currentOpacity + (elapsedGameTime / m_lerpUpTime);

      if (currentOpacity >= m_maxOpacity)
      {
        currentOpacity = m_maxOpacity;

        if (m_waitTime >= m_maxOpacityWaitTime)
        {
          m_waitTime = 0;
          m_lerpingUp = false;
        }
        else
        {
          m_waitTime += elapsedGameTime;
        }
      }
    }
    else if (!m_lerpingUp)
    {
      currentOpacity = m_lerpDownTime == 0 ? m_minOpacity : currentOpacity - (elapsedGameTime / m_lerpDownTime);

      if (currentOpacity <= m_minOpacity)
      {
        currentOpacity = m_minOpacity;

        if (m_waitTime >= m_minOpacityWaitTime)
        {
          m_waitTime = 0;
          m_lerpingUp = true;
        }
        else
        {
          m_waitTime += elapsedGameTime;
        }
      }
    }
    
    renderer->setOpacity(currentOpacity);
  }
}