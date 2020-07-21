#include "Input/Keyboard.h"


namespace Celeste::Input
{
  //------------------------------------------------------------------------------------------------
  Keyboard::Keyboard() :
    m_textInputted(),
    m_keyPressed(),
    m_keyReleased()
  {
    flush();
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::update()
  {
    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      // Update the previous frame's keys with the contents of the current keys buffer
      // Do this here because we want this to happen once per handle input run, not once per update
      m_previousKeys[i] = m_currentKeys[i];
      m_currentKeys[i] = m_latestKeys[i];
    }
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::setKeyPressed(int key)
  {
    if (0 <= key && key < KEYBOARD_KEY_COUNT)
    {
      // Don't assert here - some keys seem to not be mapped to glfw key
      m_latestKeys[key] = GL_TRUE;
      m_keyPressed.invoke(key);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::setKeyReleased(int key)
  {
    if (0 <= key && key < KEYBOARD_KEY_COUNT)
    {
      // Don't assert here - some keys seem to not be mapped to glfw key
      m_latestKeys[key] = GL_FALSE;
      m_keyReleased.invoke(key);
    }
  }

  //------------------------------------------------------------------------------------------------
  bool Keyboard::isKeyPressed(int key) const
  {
    return (0 <= key && key < KEYBOARD_KEY_COUNT) ? m_currentKeys[key] : false;
  }

  //------------------------------------------------------------------------------------------------
  bool Keyboard::isKeyReleased(int key) const
  {
    return (0 <= key && key < KEYBOARD_KEY_COUNT) ? !m_currentKeys[key] : false;
  }

  //------------------------------------------------------------------------------------------------
  bool Keyboard::isKeyTapped(int key) const
  {
    return (0 <= key && key < KEYBOARD_KEY_COUNT) ? m_currentKeys[key] && !m_previousKeys[key] : false;
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::flush()
  {
    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      m_latestKeys[i] = GL_FALSE;
      m_currentKeys[i] = GL_FALSE;
      m_previousKeys[i] = GL_FALSE;
    }
  }
}