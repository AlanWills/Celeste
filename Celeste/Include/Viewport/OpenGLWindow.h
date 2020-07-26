#pragma once

#include "CelesteDllExport.h"
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
        int resolutionX, 
        int resolutionY,
        WindowMode windowMode = WindowMode::kWindowed,
        const std::string& windowTitle = "");
      CelesteDllExport ~OpenGLWindow();

      CelesteDllExport void show() const;
      CelesteDllExport void hide() const;

      const glm::vec2& getResolution() const { return m_resolution; }
      CelesteDllExport void setResolution(const glm::vec2& resolution);
      void setResolution(int x, int y) { setResolution(glm::vec2(x, y)); }

      const glm::vec2& getContentArea() const { return m_contentArea; }

      GLFWwindow* getGLWindow() const { return m_window; }

      void enableViewportFlag(GLenum flag) { glEnable(flag); }

      WindowMode getWindowMode() const { return m_windowMode; }
      CelesteDllExport void setWindowMode(WindowMode windowMode);

      CelesteDllExport void setTitle(const std::string& windowTitle);
      CelesteDllExport void setIcon(const std::string& windowTitle);

      Event<const glm::vec2&>& getResolutionChangedEvent() { return m_resolutionChanged; }

    private:
      void initWindow(int targetResolutionX, int targetResolutionY , const std::string& title);
      void setResolutionImpl(const glm::vec2& resolution);

      GLFWwindow* m_window;

      glm::vec2 m_resolution;
      glm::vec2 m_contentArea;
      WindowMode m_windowMode;
      Event<const glm::vec2&> m_resolutionChanged;
  };
}