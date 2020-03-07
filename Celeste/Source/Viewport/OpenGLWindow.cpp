#include "Viewport/OpenGLWindow.h"
#include "Input/InputManager.h"
#include "Resources/2D/RawImageLoader.h"
#include "UtilityHeaders/GLHeaders.h"
#include "OpenGL/GL.h"
#include "Debug/Assert.h"


namespace Celeste
{
  using namespace Input;

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(WindowMode windowMode, const std::string& windowTitle) :
    m_window(nullptr),
    m_title(windowTitle),
    m_left(0),
    m_top(0),
    m_right(0),
    m_bottom(0),
    m_viewportDimensions(1),
    m_viewportDimensionsChanged()
  {
    if (!GL::glfw_initialize())
    {
      ASSERT_FAIL();
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (mode)
    {
      m_viewportDimensions.x = static_cast<float>(mode->width);
      m_viewportDimensions.y = static_cast<float>(mode->height);
    }

    initWindow(windowMode);

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been a pain to figure this out, so just trust me)
    if (!GL::glew_initialize())
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(
    int screenWidth, 
    int screenHeight,
    WindowMode windowMode,
    const std::string& windowTitle) :
    m_window(nullptr),
    m_title(windowTitle),
    m_left(0),
    m_top(0),
    m_right(0),
    m_bottom(0),
    m_viewportDimensions(screenWidth, screenHeight),
    m_viewportDimensionsChanged()
  {
    initWindow(windowMode);
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
  void OpenGLWindow::initWindow(WindowMode windowMode)
  {
    int viewportDimensionsX = static_cast<int>(m_viewportDimensions.x);
    int viewportDimensionsY = static_cast<int>(m_viewportDimensions.y);

    m_window = glfwCreateWindow(viewportDimensionsX, viewportDimensionsY, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwGetWindowFrameSize(m_window, &m_left, &m_top, &m_right, &m_bottom);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int refreshRate = mode ? mode->refreshRate : 60;

    if (windowMode == WindowMode::kFullScreen)
    {
      // Just use preset viewport dimensions if in full screen
      glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }
    else
    {
      // Account for window frame when in windowed mode
      m_viewportDimensions -= glm::vec2(m_left + m_right, m_top + m_bottom);
      viewportDimensionsX = static_cast<int>(m_viewportDimensions.x);
      viewportDimensionsY = static_cast<int>(m_viewportDimensions.y);

      glfwSetWindowMonitor(m_window, nullptr, m_left, m_top, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }

    glViewport(0, 0, viewportDimensionsX, viewportDimensionsY);
    glCheckError();

    // Don't bother calling event, because who will have subscribed?  We call this function from the constructor

    // OpenGL configuration
    //enableViewportFlag(GL_CULL_FACE);
    //enableViewportFlag(GL_DEPTH_TEST);
    enableViewportFlag(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::handleInput()
  {
    // Check to see whether we should exit
    if (getKeyboard().isKeyTapped(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(m_window, GL_TRUE);
    }
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

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int refreshRate = mode ? mode->refreshRate : 60;
    int viewportDimensionsX = static_cast<int>(m_viewportDimensions.x);
    int viewportDimensionsY = static_cast<int>(m_viewportDimensions.y);

    if (windowMode == WindowMode::kFullScreen)
    {
      // When in full screen, our window will not have a left or right
      // So only account for them in windowed mode
      //m_viewportDimensions += glm::vec2(m_left + m_right, m_top + m_bottom);

      glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }
    else
    {
      // When in full screen, our window will not have a left or right
      // So only account for them in windowed mode

      //m_viewportDimensions -= glm::vec2(m_left + m_right, m_top + m_bottom);

      glfwSetWindowMonitor(m_window, nullptr, m_left, m_top, viewportDimensionsX, viewportDimensionsY, refreshRate);
    }

    glViewport(0, 0, viewportDimensionsX, viewportDimensionsY);
    glCheckError();

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

    m_title = windowTitle;
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
  glm::vec2 OpenGLWindow::getWindowDimensions() const
  {
    return getWindowMode() == WindowMode::kFullScreen ? m_viewportDimensions : 
      m_viewportDimensions + glm::vec2(m_left + m_right, m_top + m_bottom);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setWindowDimensions(glm::vec2 windowDimensions)
  {
    if (!m_window)
    {
      ASSERT_FAIL();
      return;
    }

    if (getWindowMode() == WindowMode::kWindowed)
    {
      // Adjust the viewport dimensions taking into account the border
      windowDimensions.x -= (m_left + m_right);
      windowDimensions.y -= (m_top + m_bottom);
    }

    setViewportDimensions(windowDimensions);
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

    if (getWindowMode() == WindowMode::kWindowed)
    {
      // Adjust the dimensions for the window borders when in windowed mode
      glfwSetWindowSize(m_window, static_cast<int>(viewportDimensions.x) + m_left + m_right, static_cast<int>(m_viewportDimensions.y + m_top + m_bottom));
    }

    if (m_viewportDimensions != viewportDimensions)
    {
      // Only update if we are setting to different dimensions
      m_viewportDimensions = viewportDimensions;

      // Update gl state so to reflect the new dimensions
      glViewport(0, 0, static_cast<int>(m_viewportDimensions.x), static_cast<int>(m_viewportDimensions.y));

      m_viewportDimensionsChanged.invoke(m_viewportDimensions);
    }
  }
}