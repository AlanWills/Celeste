#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Objects/Entity.h"
#include "Input/InputUtils.h"

#include <memory.h>


namespace Celeste
{
  class GLFWWindow;
}

namespace Celeste::Input
{
  class InputManager : public Entity
  {
    public:
      CelesteDllExport InputManager(GLFWwindow* window);
      CelesteDllExport ~InputManager() override;

      InputManager(const InputManager&) = delete;
      InputManager& operator=(const InputManager&) = delete;

      inline Keyboard& getKeyboard() { return m_keyboard; }
      inline const Keyboard& getKeyboard() const { return m_keyboard; }

      inline Mouse& getMouse() { return m_mouse; }
      inline const Mouse& getMouse() const { return m_mouse; }

      CelesteDllExport void handleInput() override;
      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = Entity;

      void updateMousePosition();
      void raycast() const;

      Keyboard m_keyboard;
      Mouse m_mouse;
  };

  //------------------------------------------------------------------------------------------------
  CelesteDllExport void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
  CelesteDllExport void charCallback(GLFWwindow* window, unsigned int codepoint);
  CelesteDllExport void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
}