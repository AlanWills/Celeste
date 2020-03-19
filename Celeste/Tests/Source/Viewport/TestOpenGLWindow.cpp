#include "UtilityHeaders/UnitTestHeaders.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"
#include "OpenGL/GL.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestOpenGLWindow)

  //------------------------------------------------------------------------------------------------
  void TestOpenGLWindow::testInitialize()
  {
    glfwMakeContextCurrent(nullptr);
  }

  //------------------------------------------------------------------------------------------------
  void TestOpenGLWindow::testCleanup()
  {
    glfwMakeContextCurrent(getWindow().getGLWindow());
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_DefaultConstructor)
  {
    if (GL::isInitialized())
    {
      // This should just create a window using the current device primary monitor resolution and frame size
      // Check this doesn't cause any errors
      OpenGLWindow window;
      Assert::IsNotNull(window.getGLWindow());
      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::AreEqual("", window.getTitle().c_str());

      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);
      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

      glm::vec2 viewportDimensions(mode->width - (left + right), mode->height - (top + bottom));
      Assert::AreEqual(viewportDimensions, window.getViewportDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_PassingTitleToConstructor)
  {
    OpenGLWindow viewport(OpenGLWindow::WindowMode::kWindowed, "Test Window");

    Assert::AreEqual("Test Window", viewport.getTitle().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_Windowed_PassingScreenResolutionToConstructor_AccountsForWindowFrameSize)
  {
    if (GL::isInitialized())
    {
      // This should just create a window using the inputted resolution
      // Check this doesn't cause any errors
      OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

      Assert::IsNotNull(window.getGLWindow());
      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (top + bottom)), window.getViewportDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_FullScreen_PassingResolutionToConstructor_DoesNotAccountForWindowFrameSize)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsNotNull(window.getGLWindow());
    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getViewportDimensions());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_Constructor_FullScreen)
  {
    /*OpenGLWindow window(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGWindow_Constructor_Windowed)
  {
    OpenGLWindow window(OpenGLWindow::WindowMode::kWindowed);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
  }

#pragma endregion

#pragma region Set Window Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokFullScreen_UpdatesScreenResolution)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getViewportDimensions());

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getViewportDimensions());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokFullScreen_CallsViewportDimensionsChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

    glm::vec2 dims;
    auto f = [&dims](const glm::vec2& newDimensions) -> void { dims = newDimensions; };
    window.getViewportDimensionsChangedEvent().subscribe(f);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), dims);*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokWindowed_DoesNothing)
  {
    OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getViewportDimensions());

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getViewportDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokWindowed_DoesNotCallViewportDimensionsChangedEvent)
  {
    OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

    bool called = false;
    auto f = [&called](const glm::vec2& /*newDimensions*/) -> void { called = true; };
    window.getViewportDimensionsChangedEvent().subscribe(f);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokWindowed_UpdatesScreenResolution)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getViewportDimensions());

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getViewportDimensions());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokWindowed_CallsViewportDimensionsChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    glm::vec2 dims;
    auto f = [&dims](const glm::vec2& newDimensions) -> void { dims = newDimensions; };
    window.getViewportDimensionsChangedEvent().subscribe(f);
      
    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getViewportDimensions());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokFullScreen_DoesNothing)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getViewportDimensions());

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getViewportDimensions());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokFullScreen_DoesNotCallViewportDimensionsChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    bool called = false;
    auto f = [&called](const glm::vec2& newDimensions) -> void { called = true; };
    window.getViewportDimensionsChangedEvent().subscribe(f);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::IsFalse(called);*/
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetTitle_UpdatesTitleCorrectly)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      Assert::AreEqual("", window.getTitle().c_str());

      window.setTitle("Test Window");
      Assert::AreEqual("Test Window", window.getTitle().c_str());

      window.setTitle("Another Test");
      Assert::AreEqual("Another Test", window.getTitle().c_str());
    }
  }

#pragma region Set Window Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_Windowed_UpdatesWindowDimensionsCorrectly)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);
      window.setWindowDimensions(100, 100);

      int left, right, top, bottom;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

      Assert::AreEqual(glm::vec2(100 - left - right, 100 - top - bottom), window.getViewportDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_FullScreen_UpdatesWindowDimensionsCorrectly)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);
      window.setWindowDimensions(100, 100);

      Assert::AreEqual(glm::vec2(100, 100), window.getViewportDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_ToDifferentDimensions_CallsViewportDimensionsChangedEvent)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setWindowDimensions(100, 100);

      bool called = false;
      auto f = [&called](const glm::vec2&) -> void { called = true; };
      window.getViewportDimensionsChangedEvent().subscribe(f);
      window.setWindowDimensions(glm::vec2(200, 100));

      Assert::IsTrue(called);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_Windowed_ToDifferentDimensions_PassesViewportAdjustedDimensionsToEvent)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);
      window.setWindowDimensions(100, 100);

      glm::vec2 newDims;
      auto f = [&newDims](const glm::vec2& newDimensions) -> void { newDims = newDimensions; };
      window.getViewportDimensionsChangedEvent().subscribe(f);
      window.setWindowDimensions(glm::vec2(200, 100));

      int left, right, top, bottom;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

      Assert::AreEqual(glm::vec2(200 - left - right, 100 - top - bottom), newDims);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_FullScreen_ToDifferentDimensions_PassesViewportAdjustedDimensionsToEvent)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);
      window.setWindowDimensions(100, 100);

      glm::vec2 newDims;
      auto f = [&newDims](const glm::vec2& newDimensions) -> void { newDims = newDimensions; };
      window.getViewportDimensionsChangedEvent().subscribe(f);
      window.setWindowDimensions(glm::vec2(200, 100));

      Assert::AreEqual(glm::vec2(200, 100), newDims);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowDimensions_ToSameDimensions_DoesNotCallViewportDimensionsChangedEvent)
  {
    OpenGLWindow window;
    window.setWindowDimensions(100, 100);

    bool called = false;
    auto f = [&called](const glm::vec2&) -> void { called = true; };
    window.getViewportDimensionsChangedEvent().subscribe(f);
    window.setWindowDimensions(glm::vec2(100, 100));

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Set Viewport Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetViewportDimensions_UpdatesViewportDimensionsCorrectly)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setViewportDimensions(100, 100);

      Assert::AreEqual(glm::vec2(100, 100), window.getViewportDimensions());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetViewportDimensions_ToDifferentDimensions_CallsViewportDimensionsChangedEvent)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setViewportDimensions(100, 100);

      bool called = false;
      auto f = [&called](const glm::vec2&) -> void { called = true; };
      window.getViewportDimensionsChangedEvent().subscribe(f);
      window.setViewportDimensions(glm::vec2(200, 100));

      Assert::IsTrue(called);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetViewportDimensions_ToDifferentDimensions_PassesViewportDimensionsToEvent)
  {
    if (GL::isInitialized())
    {
      OpenGLWindow window;
      window.setViewportDimensions(100, 100);

      glm::vec2 newDims;
      auto f = [&newDims](const glm::vec2 & newDimensions) -> void { newDims = newDimensions; };
      window.getViewportDimensionsChangedEvent().subscribe(f);
      window.setViewportDimensions(glm::vec2(200, 100));

      Assert::AreEqual(glm::vec2(200, 100), newDims);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetViewportDimensions_ToSameDimensions_DoesNotCallViewportDimensionsChangedEvent)
  {
    OpenGLWindow window;
    window.setViewportDimensions(100, 100);

    bool called = false;
    auto f = [&called](const glm::vec2&) -> void { called = true; };
    window.getViewportDimensionsChangedEvent().subscribe(f);
    window.setViewportDimensions(glm::vec2(100, 100));

    Assert::IsFalse(called);
  }

#pragma endregion

  };
}