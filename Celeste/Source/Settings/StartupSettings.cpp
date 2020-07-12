#include "Settings/StartupSettings.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "Resources/ResourceUtils.h"
#include "Scene/SceneUtils.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Viewport/OpenGLWindow.h"


namespace Celeste::Settings
{
  REGISTER_SCRIPTABLE_OBJECT(StartupSettings);

  //------------------------------------------------------------------------------------------------
  const Path StartupSettings::SETTINGS_RELATIVE_PATH = Path("Data", "Settings", "StartupSettings.asset");

  //------------------------------------------------------------------------------------------------
  StartupSettings::StartupSettings() :
    Inherited(),
    m_windowTitle(createReferenceField<std::string>("window_title")),
    m_windowIcon(createReferenceField<std::string>("window_icon")),
    m_cursor(createReferenceField<std::string>("cursor"))
  {
  }

  //------------------------------------------------------------------------------------------------
  void StartupSettings::apply() const
  {
    OpenGLWindow& window = getWindow();
    window.setTitle(getWindowTitle());
    window.setIcon(Path(Resources::getResourcesDirectory(), getWindowIcon()).as_string());

    if (!getCursor().empty())
    {
      Input::Mouse& mouse = Input::getMouse();
      mouse.setCursor(getCursor());
    }
  }
}