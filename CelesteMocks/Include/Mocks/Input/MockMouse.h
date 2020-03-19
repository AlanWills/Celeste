#pragma once

#include "Input/Mouse.h"


namespace CelesteMocks
{
  class MockMouse : public Celeste::Input::Mouse
  {
    public:
      bool getLatestButtonFlag(Celeste::Input::MouseButton button) const { return m_latestButtons[static_cast<int>(button)]; }
      bool getCurrentButtonFlag(Celeste::Input::MouseButton button) const { return m_currentButtons[static_cast<int>(button)]; }
      bool getPreviousButtonFlag(Celeste::Input::MouseButton button) const { return m_previousButtons[static_cast<int>(button)]; }
      GLFWcursor* getCursor() const { return m_cursor; }
  };
}