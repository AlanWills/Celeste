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
    Screen::m_allocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::handleInput()
  {
    Inherited::handleInput();

    getWindow()->handleInput();
    
    Screen::m_allocator.handleInput();
  }
  
  //------------------------------------------------------------------------------------------------
  void ScreenManager::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    Screen::m_allocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  EntityAllocatorIterator<const Screen> ScreenManager::begin() const
  {
    return Screen::m_allocator.cbegin();
  }

  //------------------------------------------------------------------------------------------------
  EntityAllocatorIterator<const Screen> ScreenManager::end() const
  {
    return Screen::m_allocator.cend();
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Screen> ScreenManager::findScreen(StringId name)
  {
    return Screen::m_allocator.find([&name](const Screen& screen) -> bool
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