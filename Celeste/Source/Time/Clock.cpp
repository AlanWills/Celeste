#include "Time/Clock.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Clock::Clock(float targetFramesPerSecond, float startTimeSeconds) :
    m_cycles(secondsToCycles(startTimeSeconds)),
    m_current(std::chrono::system_clock::now()),
    m_previous(std::chrono::system_clock::now()),
    m_timeScale(1.0f),  // Default to unscaled
    m_targetSecondsPerFrame(1.0f / targetFramesPerSecond),
    m_paused(false)   // Default to running
  {
  }

  //------------------------------------------------------------------------------------------------
  void Clock::awake()
  {
    m_previous = m_current;
    m_current = std::chrono::system_clock::now();
  }

  //------------------------------------------------------------------------------------------------
  void Clock::update()
  {
    if (!m_paused)
    {
      m_previous = m_current;
      m_current = std::chrono::system_clock::now();
      m_cycles += secondsToCycles(static_cast<float>((m_current - m_previous).count()) * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::singleStep()
  {
    if (!m_paused)
    {
      m_previous = m_current;
      m_current += std::chrono::duration<float>(m_targetSecondsPerFrame);

      // Add one target frame interval and scale by our current time scale
      m_cycles += secondsToCycles(m_targetSecondsPerFrame * m_timeScale);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Clock::reset()
  {
    m_cycles = 0;
    m_previous = std::chrono::system_clock::now();
    m_current = m_previous;
  }
}