#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Maths/Transform.h"
#include "InputEnums.h"


namespace Celeste
{
  class Path;
}

namespace Celeste::Input
{
  class Mouse
  {
    public:
      CelesteDllExport Mouse();

      CelesteDllExport void handleInput();
      CelesteDllExport void flush();

      Transform& getTransform() { return m_transform; }
      const Transform& getTransform() const { return const_cast<Mouse*>(this)->getTransform(); }

      CelesteDllExport void setButtonPressed(MouseButton mouseButton);
      CelesteDllExport void setButtonReleased(MouseButton mouseButton);

      /// Returns true if the inputted mouse button has been pressed this frame
      CelesteDllExport bool isButtonPressed(MouseButton mouseButton) const;

      /// Returns true if the inputted mouse button has not been pressed this frame
      CelesteDllExport  bool isButtonReleased(MouseButton mouseButton) const;

      /// Returns true if the inputted mouse button is pressed last frame and released this frame
      /// It's possible we should reverse this logic - we shall see how it feels in game
      CelesteDllExport bool isButtonClicked(MouseButton mouseButton) const;

      CelesteDllExport void setCursor(const std::string& imageRelativePath, const glm::vec2& cursorHotSpot = glm::vec2());
      CelesteDllExport void setCursor(const Path& imageRelativePath, const glm::vec2& cursorHotSpot = glm::vec2());

      inline glm::vec2 getScreenPosition() const { return glm::vec2(m_transform.getWorldTranslation()); }

    protected:
      // Latest holds the buttons we wish to be registered as done when we call handle input
      // Similar to a buffered message waiting to be processed
      GLboolean m_latestButtons[static_cast<int>(MouseButton::kNumButtons)];
      GLboolean m_currentButtons[static_cast<int>(MouseButton::kNumButtons)];
      GLboolean m_previousButtons[static_cast<int>(MouseButton::kNumButtons)];

      GLFWcursor* m_cursor;

    private:
      Transform m_transform;
  };
}