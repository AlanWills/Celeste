#include "UtilityHeaders/UnitTestHeaders.h"

#include "Settings/WindowSettings.h"
#include "Resources/ResourceManager.h"
#include "Viewport/OpenGLWindow.h"
#include "OpenGL/GL.h"
#include "XML/tinyxml2_ext.h"

using namespace Celeste;
using namespace Celeste::XML;
using namespace Celeste::Settings;


namespace TestCeleste
{
  namespace Settings
  {
    CELESTE_TEST_CLASS(TestWindowSettings)

    std::string originalWindowTitle;
    glm::vec2 originalResolution;
    bool originalWindowed;

    //------------------------------------------------------------------------------------------------
    void TestWindowSettings::testInitialize()
    {
      OpenGLWindow* window = getWindow();

      originalWindowTitle = window->getTitle();
      originalResolution = window->getViewportDimensions();
      originalWindowed = window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed;
    }

    //------------------------------------------------------------------------------------------------
    void TestWindowSettings::testCleanup()
    {
      resetWindow();
    }

    //------------------------------------------------------------------------------------------------
    void TestWindowSettings::resetWindow()
    {
      OpenGLWindow* window = getWindow();

      window->setTitle(originalWindowTitle);
      window->setViewportDimensions(originalResolution);
      window->setWindowMode(originalWindowed ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Constructor_SetsWindowTitleToEmptyString)
    {
      std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");

      Assert::IsTrue(settings->getWindowTitle().empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Constructor_SetsWindowIconToEmptyString)
    {
      std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");

      Assert::IsTrue(settings->getWindowIcon().empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Constructor_SetsResolutionToEmptyString)
    {
      std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");

      Assert::AreEqual(glm::vec2(), settings->getResolution());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Constructor_SetsWindowed_ToFalse)
    {
      std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");

      Assert::IsFalse(settings->isWindowed());
    }

#pragma endregion

#pragma region Apply Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Apply_SetsWindowTitleToValue)
    {
      if (GL::isInitialized())
      {
        std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");
        settings->setWindowTitle(originalWindowTitle + "Test");

        OpenGLWindow * window = getWindow();

        Assert::AreEqual(originalWindowTitle, window->getTitle());

        settings->apply();

        Assert::AreEqual(originalWindowTitle + "Test", window->getTitle());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Apply_SetsViewportDimensionsToValue)
    {
      if (GL::isInitialized())
      {
        std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");
        settings->setResolution(originalResolution + glm::vec2(100, 200));

        OpenGLWindow * window = getWindow();

        Assert::AreEqual(originalResolution, window->getViewportDimensions());

        settings->apply();

        Assert::AreEqual(originalResolution + glm::vec2(100, 200), window->getViewportDimensions());
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(WindowSettings_Apply_SetsWindowModeToValue)
    {
      if (GL::isInitialized())
      {
        std::unique_ptr<WindowSettings> settings = ScriptableObject::create<WindowSettings>("");
        settings->setWindowed(!originalWindowed);

        OpenGLWindow* window = getWindow();

        Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

        settings->apply();

        Assert::AreEqual(!originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      }
    }

#pragma endregion

    };
  }
}