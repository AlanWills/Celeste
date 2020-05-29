#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"

#include <chrono>


namespace Celeste
{
  #define DEFAULT_TARGET_FPS 60

  class Clock
  {
    public:
      using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>>;

      CelesteDllExport Clock(float targetFramesPerSecond = DEFAULT_TARGET_FPS, float startTimeSeconds = 0);

      CelesteDllExport static uint64_t secondsToCycles(float timeSeconds);

      // WARNING: Dangerous - only use to convert small durations into seconds
      CelesteDllExport static float cyclesToSeconds(uint64_t timeCycles);

      /// \brief Convert system chrono seconds to a float
      static float systemSeconds(std::chrono::seconds seconds) { return std::chrono::duration_cast<std::chrono::milliseconds>(seconds).count() / 1000.0f; }

      /// \brief This function should be called once per frame with the real measured frame time delta in seconds.
      CelesteDllExport void update(float elapsedGameTime);

      /// \brief Advance the clock by the time scale dictated by our desired FPS
      CelesteDllExport void singleStep();

      /// \brief Reset the clock cycles counter to zero
      CelesteDllExport void reset();

      /// \brief Return the total cycles since the last reset rather than the time in seconds
      /// as a float does not have enough accuracy
      uint64_t getElapsedCycles() const { return m_cycles; }

      /// \brief Return the time since this clock was last updated
      float getElapsedDeltaTime() const { return (m_current - m_previous) * m_timeScale; }

      void setTimeScale(float timeScale) { m_timeScale = timeScale; }
      float getTimeScale() const { return m_timeScale; }

      float getTargetSecondsPerFrame() const { return m_targetSecondsPerFrame; }

      void setTargetFramesPerSecond(int framesPerSecond) { m_targetSecondsPerFrame = (1.0f / framesPerSecond); }
      int getTargetFramesPerSecond() const { return static_cast<int>(1 / m_targetSecondsPerFrame); }

      void setPaused(bool paused) { m_paused = paused; }
      bool getPaused() const { return m_paused; }

    private:
      uint64_t m_cycles;
      float m_current;
      float m_previous;
      float m_timeScale;
      float m_targetSecondsPerFrame;
      bool m_paused;
  };

  //------------------------------------------------------------------------------------------------
  inline uint64_t Clock::secondsToCycles(float timeSeconds)
  {
    return (uint64_t)(timeSeconds * CLOCKS_PER_SEC);
  }

  //------------------------------------------------------------------------------------------------
  inline float Clock::cyclesToSeconds(uint64_t timeCycles)
  {
    return (float)timeCycles / CLOCKS_PER_SEC;
  }
}