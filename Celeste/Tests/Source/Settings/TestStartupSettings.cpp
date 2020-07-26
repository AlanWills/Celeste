#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Settings/StartupSettings.h"
#include "Resources/ResourceManager.h"
#include "Viewport/OpenGLWindow.h"
#include "Scene/SceneUtils.h"
#include "OpenGL/GL.h"
#include "XML/tinyxml2_ext.h"

using namespace Celeste;
using namespace Celeste::XML;
using namespace Celeste::Settings;


namespace TestCeleste::Settings
{
  CELESTE_TEST_CLASS(TestStartupSettings)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(WindowSettings_Constructor_SetsWindowTitleToEmptyString)
  {
    std::unique_ptr<StartupSettings> settings = ScriptableObject::create<StartupSettings>("");

    Assert::IsTrue(settings->getWindowTitle().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(WindowSettings_Constructor_SetsWindowIconToEmptyString)
  {
    std::unique_ptr<StartupSettings> settings = ScriptableObject::create<StartupSettings>("");

    Assert::IsTrue(settings->getWindowIcon().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(WindowSettings_Constructor_SetsCursorToEmptyString)
  {
    std::unique_ptr<StartupSettings> settings = ScriptableObject::create<StartupSettings>("");

    Assert::IsTrue(settings->getCursor().empty());
  }

#pragma endregion

  };
}