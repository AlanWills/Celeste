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
    m_viewportDimensions(0),
    m_windowMode(windowMode),
    m_viewportDimensionsChanged()
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
    int screenWidth, 
    int screenHeight,
    WindowMode windowMode,
    const std::string& windowTitle) :
    m_window(nullptr),
    m_viewportDimensions(0),
    m_windowMode(windowMode),
    m_viewportDimensionsChanged()
  {
    if (!GL::glfw_initialize())
    {
      ASSERT_FAIL();
      LOG_CRITICAL_ERROR("GLFW failed to initialize.");
      return;
    }

    initWindow(screenWidth, screenHeight, windowTitle);

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
  void OpenGLWindow::initWindow(int targetWidth, int targetHeight, const std::string& title)
  {
    m_window = glfwCreateWindow(targetWidth, targetHeight, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;
    int refreshRate = mode != nullptr ? mode->refreshRate : GLFW_DONT_CARE;

    if (m_windowMode == WindowMode::kFullScreen)
    {
      // Just use preset viewport dimensions if in full screen
      glfwSetWindowMonitor(m_window, monitor, 0, 0, targetWidth, targetHeight, refreshRate);
    }
    else
    {
      int left = 0, right = 0, top = 0, bottom = 0;
      glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);

      glfwSetWindowPos(m_window, 0, top);
    }

    setViewportDimensions(glm::vec2(targetWidth, targetHeight));

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
    // POSSIBLY NEED TO REVISIT THIS - don't think viewport calculation is correct

    if (windowMode == getWindowMode())
    {
      // Checks to see if the current window mode is the same as the desired window mode
      // If so, early outs of the function
      return;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = monitor != nullptr ? glfwGetVideoMode(monitor) : nullptr;

    int refreshRate = mode ? mode->refreshRate : GLFW_DONT_CARE;
    int viewportDimensionsX = static_cast<int>(m_viewportDimensions.x);
    int viewportDimensionsY = static_cast<int>(m_viewportDimensions.y);

    int left = 0, right = 0, top = 0, bottom = 0;
    glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);

    if (windowMode == WindowMode::kFullScreen)
    {
      glfwSetWindowMonitor(m_window, monitor, 0, 0, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }
    else
    {
      glfwSetWindowMonitor(m_window, nullptr, left, top, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }

    glViewport(0, 0, viewportDimensionsX, viewportDimensionsY);
    glCheckError();

    m_windowMode = windowMode;
    m_viewportDimensionsChanged.invoke(m_viewportDimensions);
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
  void OpenGLWindow::setViewportDimensions(const glm::vec2& viewportDimensions)
  {
    if (!m_window)
    {
      ASSERT_FAIL();
      return;
    }

    ASSERT(viewportDimensions.x > 0);
    ASSERT(viewportDimensions.y > 0);

    if (m_viewportDimensions != viewportDimensions)
    {
      // Only update if we are setting to different dimensions
      glfwSetWindowSize(m_window, static_cast<int>(viewportDimensions.x), static_cast<int>(viewportDimensions.y));

      // Update gl state so to reflect the new dimensions
      int width = 0, height = 0;
      glfwGetFramebufferSize(m_window, &width, &height);
      glViewport(0, 0, width, height);

      m_viewportDimensions.x = static_cast<float>(width);
      m_viewportDimensions.y = static_cast<float>(height);
      m_viewportDimensionsChanged.invoke(m_viewportDimensions);
    }
  }
}