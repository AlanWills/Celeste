#pragma once

#include "Objects/Component.h"
#include "Events/Event.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste::Input
{
#define KEYBOARD_KEY_COUNT GLFW_KEY_LAST + 1

  class Keyboard
  {
    public:
      CelesteDllExport Keyboard();

      CelesteDllExport void update();

      CelesteDllExport void setKeyPressed(int key);
      CelesteDllExport void setKeyReleased(int key);

      CelesteDllExport bool isKeyPressed(int key) const;
      CelesteDllExport bool isKeyReleased(int key) const;
      CelesteDllExport bool isKeyTapped(int key) const;

      /// Sets every value of the current keys to GL_FALSE so that
      /// all calls to isKeyDown and isKeyPressed will return GL_FALSE;
      CelesteDllExport void flush();

      void onTextInputted(char c) { m_textInputted.invoke(c); }

      Event<char>& getTextInputtedEvent() { return m_textInputted; }
      Event<int>& getKeyPressedEvent() { return m_keyPressed; }
      Event<int>& getKeyReleasedEvent() { return m_keyReleased; }

    protected:
      const GLboolean* getLatestKeys() const { return m_latestKeys; }
      const GLboolean* getCurrentKeys() const { return m_currentKeys; }
      const GLboolean* getPreviousKeys() const { return m_previousKeys; }

    private:
      GLboolean m_latestKeys[KEYBOARD_KEY_COUNT];
      GLboolean m_currentKeys[KEYBOARD_KEY_COUNT];
      GLboolean m_previousKeys[KEYBOARD_KEY_COUNT];

      Event<char> m_textInputted;
      Event<int> m_keyPressed;
      Event<int> m_keyReleased;
  };
}