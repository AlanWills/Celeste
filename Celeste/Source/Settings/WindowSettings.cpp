#include "Settings/WindowSettings.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "Resources/ResourceUtils.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"


namespace Celeste
{
  namespace Settings
  {
    REGISTER_SCRIPTABLE_OBJECT(WindowSettings);

    //------------------------------------------------------------------------------------------------
    WindowSettings::WindowSettings() :
      Inherited(),
      m_windowTitle(createReferenceField<std::string>("window_title")),
      m_windowIcon(createReferenceField<std::string>("window_icon")),
      m_resolution(createReferenceField<glm::vec2>("resolution")),
      m_windowed(createValueField<bool>("windowed"))
    {
    }

    //------------------------------------------------------------------------------------------------
    void WindowSettings::apply() const
    {
      OpenGLWindow& window = getWindow();
      window.setTitle(getWindowTitle());
      window.setIcon(Path(Resources::getResourcesDirectory(), getWindowIcon()).as_string());
      window.setWindowMode(isWindowed() ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);
      
      // Set window dimensions after we set window mode because the order matters
      const glm::vec2& resolution = getResolution();
      if (resolution != glm::zero<glm::vec2>())
      {
        window.setViewportDimensions(resolution);
      }
    }
  }
}