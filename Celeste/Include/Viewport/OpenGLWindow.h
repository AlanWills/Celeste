#pragma once

#include "Events/Event.h"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>


namespace Celeste
{
  class OpenGLWindow
  {
    public:
      enum class WindowMode
      {
        kWindowed,
        kFullScreen
      };

      CelesteDllExport OpenGLWindow(WindowMode windowMode = WindowMode::kWindowed, const std::string& windowTitle = "");
      CelesteDllExport OpenGLWindow(
        int windowWidth, 
        int windowHeight,
        WindowMode windowMode = WindowMode::kWindowed,
        const std::string& windowTitle = "");
      CelesteDllExport ~OpenGLWindow();

      CelesteDllExport void show() const;
      CelesteDllExport void hide() const;

      const glm::vec2& getViewportDimensions() const { return m_viewportDimensions; }
      CelesteDllExport void setViewportDimensions(const glm::vec2& viewportDimensions);
      void setViewportDimensions(int x, int y) { setViewportDimensions(glm::vec2(x, y)); }

      GLFWwindow* getGLWindow() const { return m_window; }

      void enableViewportFlag(GLenum flag) { glEnable(flag); }

      WindowMode getWindowMode() const { return m_windowMode; }
      CelesteDllExport void setWindowMode(WindowMode windowMode);

      CelesteDllExport void setTitle(const std::string& windowTitle);
      CelesteDllExport void setIcon(const std::string& windowTitle);

      const Event<const glm::vec2&>& getViewportDimensionsChangedEvent() const { return m_viewportDimensionsChanged; }

    private:
      void initWindow(int targetWidth, int targetHeight, const std::string& title);

      GLFWwindow* m_window;

      /// Store the values of the window frame size
      //int m_left, m_top, m_right, m_bottom;

      glm::vec2 m_viewportDimensions;
      WindowMode m_windowMode;
      Event<const glm::vec2&> m_viewportDimensionsChanged;
  };
}