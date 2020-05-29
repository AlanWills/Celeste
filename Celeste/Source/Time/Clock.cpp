#include "Time/Clock.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Clock::Clock(float targetFramesPerSecond, float startTimeSeconds) :
    m_cycles(secondsToCycles(startTimeSeconds)),
    m_current(0.0f),
    m_previous(0.0f),
    m_timeScale(1.0f),  // Default to unscaled
    m_targetSecondsPerFrame(1.0f / targetFramesPerSecond),
    m_paused(false)   // Default to running
  {
  }

  //------------------------------------------------------------------------------------------------
  void Clock::update(float elapsedGameTime)
  {
    if (!m_paused)
    {
      m_previous = m_current;
      m_current += elapsedGameTime;
      m_cycles += secondsToCycles((m_current - m_previous) * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::singleStep()
  {
    if (!m_paused)
    {
      m_previous = m_current;
      m_current += m_targetSecondsPerFrame;

      // Add one target frame interval and scale by our current time scale
      m_cycles += secondsToCycles(m_targetSecondsPerFrame * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::reset()
  {
    m_cycles = 0;
    m_previous = 0;
    m_current = 0;
  }
}