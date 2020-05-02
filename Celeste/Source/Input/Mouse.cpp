#include "Input/Mouse.h"
#include "Resources/2D/RawImageLoader.h"
#include "Resources/ResourceManager.h"
#include "FileSystem/Path.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"

using namespace Celeste::Resources;


namespace Celeste::Input
{
  //------------------------------------------------------------------------------------------------
  Mouse::Mouse() :
    m_cursor(nullptr),
    m_transform()
  {
    flush();
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::update()
  {
    for (int i = 0; i < static_cast<int>(MouseButton::kNumButtons); ++i)
    {
      // Set the previous mouse button states to be the current mouse button states
      // Want this to happen once per handle input, not once per update loop
      m_previousButtons[i] = m_currentButtons[i];
      m_currentButtons[i] = m_latestButtons[i];
    }
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setButtonPressed(MouseButton mouseButton)
  {
    if (mouseButton != MouseButton::kNumButtons)
    {
      m_latestButtons[static_cast<int>(mouseButton)] = GL_TRUE;
    }
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setButtonReleased(MouseButton mouseButton)
  {
    if (mouseButton != MouseButton::kNumButtons)
    {
      m_latestButtons[static_cast<int>(mouseButton)] = GL_FALSE;
    }
  }

  //------------------------------------------------------------------------------------------------
  bool Mouse::isButtonPressed(MouseButton mouseButton) const
  {
    return (mouseButton != MouseButton::kNumButtons) ? m_currentButtons[static_cast<int>(mouseButton)] : false;
  }

  //------------------------------------------------------------------------------------------------
  bool Mouse::isButtonReleased(MouseButton mouseButton) const
  {
    return (mouseButton != MouseButton::kNumButtons) ? !m_currentButtons[static_cast<int>(mouseButton)] : false;
  }

  //------------------------------------------------------------------------------------------------
  bool Mouse::isButtonClicked(MouseButton mouseButton) const
  {
    return (mouseButton != MouseButton::kNumButtons) ? (m_currentButtons[static_cast<int>(mouseButton)] && !m_previousButtons[static_cast<int>(mouseButton)]) : false;
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::flush()
  {
    for (int i = 0; i < static_cast<int>(MouseButton::kNumButtons); ++i)
    {
      m_latestButtons[i] = GL_FALSE;
      m_currentButtons[i] = GL_FALSE;
      m_previousButtons[i] = GL_FALSE;
    }
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setCursor(const std::string& imageRelativePath, const glm::vec2& cursorHotSpot)
  {
    Path fullPath(getResourcesDirectory(), imageRelativePath);

    if (!File::exists(fullPath))
    {
      return;
    }

    if (m_cursor)
    {
      glfwDestroyCursor(m_cursor);
    }

    RawImageLoader loader(fullPath);
    GLFWimage image;
    image.width = loader.getWidth();
    image.height = loader.getHeight();
    image.pixels = loader.getData();

    m_cursor = glfwCreateCursor(&image, static_cast<int>(cursorHotSpot.x), static_cast<int>(cursorHotSpot.y));
    glfwSetCursor(getWindow().getGLWindow(), m_cursor);
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setCursor(const Path& imageRelativePath, const glm::vec2& cursorHotSpot)
  {
    setCursor(imageRelativePath.as_string(), cursorHotSpot);
  }
}