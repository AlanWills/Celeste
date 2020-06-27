#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Layout/LayoutSystem.h"
#include "Layout/ResolutionScaler.h"
#include "Objects/GameObject.h"
#include "Viewport/OpenGLWindow.h"

using namespace Celeste;
using namespace Celeste::Layout;


namespace TestCeleste::Layout
{
  CELESTE_TEST_CLASS(TestLayoutSystem)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystem_Constructor_SubscribesToWindowResolutionChangedEvent)
  {
    OpenGLWindow window(1, 1);

    Assert::AreEqual(static_cast<size_t>(0), window.getResolutionChangedEvent().getSubscriberCount());

    LayoutSystem layoutSystem(window);

    Assert::AreEqual(static_cast<size_t>(1), window.getResolutionChangedEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Destructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystem_Destructor_UnsubscribesFromWindowResolutionChangedEvent)
  {
    OpenGLWindow window(1, 1);

    {
      LayoutSystem layoutSystem(window);

      Assert::AreEqual(static_cast<size_t>(1), window.getResolutionChangedEvent().getSubscriberCount());
    }

    Assert::AreEqual(static_cast<size_t>(0), window.getResolutionChangedEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystem_Update_ResolutionScalerMarkedForRescale_RescalesResolutionScaler)
  {
    OpenGLWindow window(1, 1);
    LayoutSystem layoutSystem(window);

    GameObject gameObject;
    std::unique_ptr<ResolutionScaler> resolutionScaler = std::make_unique<ResolutionScaler>(gameObject);
    resolutionScaler->markForRescale();

    Assert::IsTrue(resolutionScaler->needsRescale());

    layoutSystem.update(0);
  
    Assert::IsFalse(resolutionScaler->needsRescale());
  }

#pragma endregion

#pragma region Window Resolution Changed Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LayoutSystem_ResolutionChanged_UpdatesAllResolutionScalers)
  {
    OpenGLWindow window(1, 1);
    LayoutSystem layoutSystem(window);

    GameObject gameObject;
    std::unique_ptr<ResolutionScaler> resolutionScaler = std::make_unique<ResolutionScaler>(gameObject);
    resolutionScaler->markForRescale();

    Assert::IsTrue(resolutionScaler->needsRescale());

    window.setResolution(2, 2);

    Assert::IsFalse(resolutionScaler->needsRescale());
  }

#pragma endregion

  };
}