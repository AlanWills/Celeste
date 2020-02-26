#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "Lua/LuaState.h"

#include "Settings/WindowSettings.h"
#include "Resources/Settings/WindowSettingsLoadingResources.h"
#include "Viewport/OpenGLWindow.h"
#include "OpenGL/GL.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste
{
  namespace Lua
  {
    namespace Settings
    {
      namespace WindowSettingsScriptCommands
      {
        CELESTE_TEST_CLASS(TestWindowSettingsScriptCommands)

        std::string originalWindowTitle;
        glm::vec2 originalResolution;
        bool originalWindowed;

        //------------------------------------------------------------------------------------------------
        void TestWindowSettingsScriptCommands::testInitialize()
        {
          OpenGLWindow* window = getWindow();

          originalWindowTitle = window->getTitle();
          originalResolution = window->getViewportDimensions();
          originalWindowed = window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed;
        }

        //------------------------------------------------------------------------------------------------
        void TestWindowSettingsScriptCommands::testCleanup()
        {
          resetWindow();
        }

        //------------------------------------------------------------------------------------------------
        void TestWindowSettingsScriptCommands::resetWindow()
        {
          OpenGLWindow* window = getWindow();

          window->setTitle(originalWindowTitle);
          window->setViewportDimensions(originalResolution);
          window->setWindowMode(originalWindowed ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);
        }

#pragma region Initialize Tests

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_Initialize_Adds_WindowSettingsUserType_ToGlobalTable)
        {
          sol::state& state = LuaState::instance();

          Assert::IsFalse(state.globals()["WindowSettings"].valid());

          Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

          Assert::IsTrue(state.globals()["WindowSettings"].valid());
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_Initialize_Adds_apply_ToWindowSettingsTable)
        {
          sol::state& state = LuaState::instance();

          Assert::IsFalse(state.globals()["WindowSettings"]["apply"].valid());

          Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

          Assert::IsTrue(state.globals()["WindowSettings"]["apply"].valid());
        }

#pragma endregion

#pragma region Apply Tests

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_apply_InputtingNonExistentPath_DoesNothing)
        {
          if (GL::isInitialized())
          {
            OpenGLWindow* window = getWindow();

            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

            sol::state & state = LuaState::instance();
            Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

            auto result = state["WindowSettings"]["apply"]("WubbaLubbaDubDub");

            Assert::IsTrue(result.valid());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
          }
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_apply_InputtingRelativeExistentPath_SettingsInvalid_DoesNothing)
        {
          if (GL::isInitialized())
          {
            OpenGLWindow* window = getWindow();

            FileAssert::FileExists(Path(TestResources::getResourcesDirectory(), WindowSettingsLoadingResources::getInvalidRelativePath()).as_string());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

            sol::state & state = LuaState::instance();
            Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

            auto result = state["WindowSettings"]["apply"](WindowSettingsLoadingResources::getInvalidRelativePath());

            Assert::IsTrue(result.valid());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
          }
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_apply_InputtingRelativeExistentPath_SettingsValid_AppliesSettingsCorrectly)
        {
          if (GL::isInitialized())
          {
            OpenGLWindow* window = getWindow();

            FileAssert::FileExists(Path(TestResources::getResourcesDirectory(), WindowSettingsLoadingResources::getValidRelativePath()).as_string());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

            sol::state & state = LuaState::instance();
            Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

            auto result = state["WindowSettings"]["apply"](WindowSettingsLoadingResources::getValidRelativePath());

            Assert::IsTrue(result.valid());
            Assert::AreEqual("Test Window Settings", window->getTitle().c_str());
            Assert::AreEqual(glm::vec2(120, 200), window->getViewportDimensions());
            Assert::IsTrue(OpenGLWindow::WindowMode::kFullScreen == window->getWindowMode());
          }
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_apply_InputtingExistentPath_SettingsInvalid_DoesNothing)
        {
          if (GL::isInitialized())
          {
            OpenGLWindow* window = getWindow();

            FileAssert::FileExists(WindowSettingsLoadingResources::getInvalidFullPath().as_string());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

            sol::state & state = LuaState::instance();
            Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

            auto result = state["WindowSettings"]["apply"](WindowSettingsLoadingResources::getInvalidFullPath().as_string());

            Assert::IsTrue(result.valid());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
          }
        }

        //------------------------------------------------------------------------------------------------
        TEST_METHOD(WindowSettingsScriptCommands_apply_InputtingExistentPath_SettingsValid_AppliesSettingsCorrectly)
        {
          if (GL::isInitialized())
          {
            OpenGLWindow* window = getWindow();

            FileAssert::FileExists(WindowSettingsLoadingResources::getValidFullPath().as_string());
            Assert::AreEqual(originalWindowTitle, window->getTitle());
            Assert::AreEqual(originalResolution, window->getViewportDimensions());
            Assert::AreEqual(originalWindowed, window->getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

            sol::state & state = LuaState::instance();
            Celeste::Lua::Settings::WindowSettingsScriptCommands::initialize();

            auto result = state["WindowSettings"]["apply"](WindowSettingsLoadingResources::getValidFullPath().as_string());

            Assert::IsTrue(result.valid());
            Assert::AreEqual("Test Window Settings", window->getTitle().c_str());
            Assert::AreEqual(glm::vec2(120, 200), window->getViewportDimensions());
            Assert::IsTrue(OpenGLWindow::WindowMode::kFullScreen == window->getWindowMode());
          }
        }

#pragma endregion

        };
      }
    }
  }
}