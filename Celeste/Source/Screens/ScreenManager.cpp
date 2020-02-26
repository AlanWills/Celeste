#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"
#include "Game/Game.h"
#include "OpenGL/GL.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  ScreenManager::ScreenManager() :
    m_window(nullptr)
  {
    if (!GL::glfw_initialize())
    {
      ASSERT_FAIL();
    }

    // Must initialize the viewport here
    if (!m_window.get())
    {
      m_window.reset(new OpenGLWindow());
    }

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been a pain to figure this out, so just trust me)
    if (!GL::glew_initialize())
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  ScreenManager::~ScreenManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::onHandleInput()
  {
    Inherited::onHandleInput();

    getWindow()->handleInput();
    
    Screen::m_componentAllocator.handleInput();
  }
  
  //------------------------------------------------------------------------------------------------
  void ScreenManager::onUpdate(float elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    Screen::m_componentAllocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::onDeath()
  {
    Inherited::onDeath();

    Screen::m_componentAllocator.die();
  }

  //------------------------------------------------------------------------------------------------
  EntityAllocatorIterator<const Screen> ScreenManager::begin() const
  {
    return Screen::m_componentAllocator.cbegin();
  }

  //------------------------------------------------------------------------------------------------
  EntityAllocatorIterator<const Screen> ScreenManager::end() const
  {
    return Screen::m_componentAllocator.cend();
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Screen> ScreenManager::findScreen(StringId name)
  {
    return Screen::m_componentAllocator.find([&name](const Screen& screen) -> bool
    {
      return screen.getName() == name;
    });
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow* ScreenManager::getWindow() const
  {
    ASSERT(m_window.get());
    return m_window.get();
  }
}