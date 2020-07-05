#include "Viewport/OpenGLWindow.h"
#include "Input/InputManager.h"
#include "Resources/2D/RawImageLoader.h"
#include "UtilityHeaders/GLHeaders.h"
#include "OpenGL/GL.h"
#include "Assert/Assert.h"


namespace Celeste
{
  using namespace Input;

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(WindowMode windowMode, const std::string& windowTitle) :
    m_window(nullptr),
    m_resolution(0),
    m_contentArea(0),
    m_windowMode(windowMode),
    m_resolutionChanged()
  {
    if (!GL::glfw_initialize())
    {
      ASSERT_FAIL();
      LOG_CRITICAL_ERROR("GLFW failed to initialize.");
      return;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    ASSERT(monitor != nullptr);

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    ASSERT(mode != nullptr);
    
    initWindow(mode->width, mode->height, windowTitle);

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been a pain to figure this out, so just trust me)
    if (!GL::glew_initialize())
    {
      ASSERT_FAIL();
      LOG_CRITICAL_ERROR("GLEW failed to initialize.");
      return;
    }
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(
    int resolutionX, 
    int resolutionY,
    WindowMode windowMode,
    const std::string& windowTitle) :
    m_window(nullptr),
    m_resolution(0),
    m_windowMode(windowMode),
    m_resolutionChanged()
  {
    if (!GL::glfw_initialize())
    {
      ASSERT_FAIL();
      LOG_CRITICAL_ERROR("GLFW failed to initialize.");
      return;
    }

    initWindow(resolutionX, resolutionY, windowTitle);

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been a pain to figure this out, so just trust me)
    if (!GL::glew_initialize())
    {
      ASSERT_FAIL();
      LOG_CRITICAL_ERROR("GLEW failed to initialize.");
      return;
    }
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::~OpenGLWindow()
  {
    if (m_window)
    {
      glfwDestroyWindow(m_window);
    }
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::initWindow(int targetResolutionX, int targetResolutionY, const std::string& title)
  {
    m_window = glfwCreateWindow(targetResolutionX, targetResolutionY, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;
    int refreshRate = mode != nullptr ? mode->refreshRate : GLFW_DONT_CARE;
    int monitorWidth = mode != nullptr ? mode->width : targetResolutionX;
    int monitorHeight = mode != nullptr ? mode->height : targetResolutionY;

    if (m_windowMode == WindowMode::kFullScreen)
    {
      // Just use preset viewport dimensions if in full screen
      glfwSetWindowMonitor(m_window, monitor, 0, 0, targetResolutionX, targetResolutionY, refreshRate);
    }
    else
    {
      int left = 0, right = 0, top = 0, bottom = 0;
      glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
      glfwSetWindowPos(m_window, (monitorWidth - targetResolutionX) / 2, top + (monitorHeight - targetResolutionY) / 2);
    }

    glfwSetWindowSize(m_window, targetResolutionX, targetResolutionY);

    // Update gl state so to reflect the new content area dimensions
    int width = 0, height = 0;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    m_resolution = glm::vec2(targetResolutionX, targetResolutionY);
    m_contentArea = glm::vec2(width, height);

    // OpenGL configuration
    //enableViewportFlag(GL_CULL_FACE);
    //enableViewportFlag(GL_DEPTH_TEST);
    enableViewportFlag(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    setTitle(title);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::show() const
  {
    glfwShowWindow(m_window);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::hide() const
  {
    glfwHideWindow(m_window);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setWindowMode(WindowMode windowMode)
  {
    if (windowMode == getWindowMode())
    {
      // Checks to see if the current window mode is the same as the desired window mode
      // If so, early outs of the function
      return;
    }

    m_windowMode = windowMode;

    int targetResolutionX = static_cast<int>(m_resolution.x);
    int targetResolutionY = static_cast<int>(m_resolution.y);
    
    if (m_windowMode == WindowMode::kFullScreen)
    {
      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;
      int refreshRate = mode ? mode->refreshRate : GLFW_DONT_CARE;

      // Just use preset viewport dimensions if in full screen
      glfwSetWindowMonitor(m_window, monitor, 0, 0, targetResolutionX, targetResolutionY, refreshRate);
    }
    else
    {
      glfwSetWindowMonitor(m_window, nullptr, 0, 0, targetResolutionX, targetResolutionY, GLFW_DONT_CARE);
      
      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;

      int monitorWidth = mode != nullptr ? mode->width : targetResolutionX;
      int monitorHeight = mode != nullptr ? mode->height : targetResolutionY;
      int left = 0, right = 0, top = 0, bottom = 0;

      glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
      glfwSetWindowPos(m_window, (monitorWidth - targetResolutionX) / 2, top + (monitorHeight - targetResolutionY) / 2);
    }

    setResolutionImpl(m_resolution);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setTitle(const std::string& windowTitle)
  {
    if (!m_window)
    {
      ASSERT_FAIL();
      return;
    }

    glfwSetWindowTitle(m_window, windowTitle.c_str());
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setIcon(const std::string& windowTitle)
  {
    Resources::RawImageLoader loader(windowTitle);
    GLFWimage icons[1];
    icons[0].pixels = loader.getData();
    icons[0].width = loader.getWidth();
    icons[0].height = loader.getHeight();
    glfwSetWindowIcon(getGLWindow(), 1, icons);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setResolution(const glm::vec2& resolution)
  {
    if (!m_window)
    {
      ASSERT_FAIL();
      return;
    }

    ASSERT(resolution.x > 0);
    ASSERT(resolution.y > 0);

    if (m_resolution != resolution)
    {
      // Only update if we are setting to different dimensions
      setResolutionImpl(resolution);
    }
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setResolutionImpl(const glm::vec2& resolution)
  {
    // Only update if we are setting to different dimensions
    glfwSetWindowSize(m_window, static_cast<int>(resolution.x), static_cast<int>(resolution.y));

    // Update gl state so to reflect the new content area dimensions
    int width = 0, height = 0;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    if (m_windowMode == WindowMode::kWindowed)
    {
      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;
      int monitorWidth = mode != nullptr ? mode->width : static_cast<int>(resolution.x);
      int monitorHeight = mode != nullptr ? mode->height : static_cast<int>(resolution.y);

      int left = 0, right = 0, top = 0, bottom = 0;
      glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
      glfwSetWindowPos(
        m_window,
        (monitorWidth - static_cast<int>(resolution.x)) / 2,
        top + (monitorHeight - static_cast<int>(resolution.y)) / 2);
    }

    m_resolution = resolution;
    m_contentArea = glm::vec2(width, height);

    // Pass the content area to the event
    m_resolutionChanged.invoke(m_contentArea);
  }
}