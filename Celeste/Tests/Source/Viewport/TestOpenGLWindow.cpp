#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"
#include "OpenGL/GL.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestOpenGLWindow)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    glfwMakeContextCurrent(nullptr);
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    glfwMakeContextCurrent(getWindow().getGLWindow());
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_DefaultConstructor)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor()!= nullptr)
    {
      // This should just create a window using the current device primary monitor resolution and frame size
      // Check this doesn't cause any errors
      OpenGLWindow window;
      Assert::IsNotNull(window.getGLWindow());
      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

      const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

      glm::vec2 viewportDimensions(mode->width, mode->height);
      Assert::AreEqual(viewportDimensions, window.getResolution());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_Windowed_PassingScreenResolutionToConstructor_AccountsForWindowFrameSize)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      // This should just create a window using the inputted resolution
      // Check this doesn't cause any errors
      OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

      Assert::IsNotNull(window.getGLWindow());
      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::AreEqual(glm::vec2(800, 600), window.getResolution());
    }
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
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window(OpenGLWindow::WindowMode::kWindowed);

      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    }
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
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getResolution());

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getResolution());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokFullScreen_CallsResolutionChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

    glm::vec2 dims;
    auto f = [&dims](const glm::vec2& newDimensions) -> void { dims = newDimensions; };
    window.getResolutionChangedEvent().subscribe(f);

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
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

      int left = 0, top = 0, right = 0, bottom = 0;
      glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::AreEqual(glm::vec2(800, 600), window.getResolution());

      window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::AreEqual(glm::vec2(800, 600), window.getResolution());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kWindowed_TokWindowed_DoesNotCallResolutionChangedEvent)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kWindowed);

      bool called = false;
      auto f = [&called](const glm::vec2& /*newDimensions*/) -> void { called = true; };
      window.getResolutionChangedEvent().subscribe(f);

      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

      window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

      Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
      Assert::IsFalse(called);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokWindowed_UpdatesScreenResolution)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getResolution());

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getResolution());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokWindowed_CallsResolutionChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    glm::vec2 dims;
    auto f = [&dims](const glm::vec2& newDimensions) -> void { dims = newDimensions; };
    window.getResolutionChangedEvent().subscribe(f);
      
    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);

    window.setWindowMode(OpenGLWindow::WindowMode::kWindowed);

    int left = 0, top = 0, right = 0, bottom = 0;
    glfwGetWindowFrameSize(window.getGLWindow(), &left, &top, &right, &bottom);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    Assert::AreEqual(glm::vec2(800 - (left + right), 600 - (bottom + top)), window.getResolution());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokFullScreen_DoesNothing)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getResolution());

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::AreEqual(glm::vec2(800, 600), window.getResolution());*/
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetWindowMode_kFullScreen_TokFullScreen_DoesNotCallResolutionChangedEvent)
  {
    /*OpenGLWindow window(800, 600, OpenGLWindow::WindowMode::kFullScreen);

    bool called = false;
    auto f = [&called](const glm::vec2& newDimensions) -> void { called = true; };
    window.getResolutionChangedEvent().subscribe(f);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);

    window.setWindowMode(OpenGLWindow::WindowMode::kFullScreen);

    Assert::IsTrue(window.getWindowMode() == OpenGLWindow::WindowMode::kFullScreen);
    Assert::IsFalse(called);*/
  }

#pragma endregion

#pragma region Set Resolution Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetResolution_UpdatesResolutionCorrectly)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window;
      window.setResolution(100, 100);

      Assert::AreEqual(glm::vec2(100, 100), window.getResolution());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetResolution_ToDifferentResolution_CallsResolutionChangedEvent)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window;
      window.setResolution(100, 100);

      bool called = false;
      auto f = [&called](const glm::vec2&) -> void { called = true; };
      window.getResolutionChangedEvent().subscribe(f);
      window.setResolution(glm::vec2(200, 100));

      Assert::IsTrue(called);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetResolution_ToDifferentResolution_PassesContentAreaToEvent)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window;
      window.setResolution(100, 100);

      glm::vec2 newDims = glm::vec2();
      auto f = [&newDims](const glm::vec2& newDimensions) -> void { newDims = newDimensions; };
      window.getResolutionChangedEvent().subscribe(f);
      window.setResolution(glm::vec2(200, 100));

      Assert::AreEqual(window.getContentArea(), newDims);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpenGLWindow_SetResolution_ToSameResolution_DoesNotCallResolutionChangedEvent)
  {
    if (GL::isInitialized() && glfwGetPrimaryMonitor() != nullptr)
    {
      OpenGLWindow window;
      window.setResolution(100, 100);

      bool called = false;
      auto f = [&called](const glm::vec2&) -> void { called = true; };
      window.getResolutionChangedEvent().subscribe(f);
      window.setResolution(glm::vec2(100, 100));

      Assert::IsFalse(called);
    }
  }

#pragma endregion

  };
}