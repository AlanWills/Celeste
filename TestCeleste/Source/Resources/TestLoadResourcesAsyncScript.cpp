#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/MockLoadResourcesAsyncScript.h"
#include "Screens/Screen.h"
#include "Screens/ScreenManager.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLoadResourcesAsyncScript)

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_WithNoGameObject_DoesNotThrow)
    {
      MockLoadResourcesAsyncScript resourceLoader;

      Assert::IsNull(resourceLoader.getGameObject());

      resourceLoader.update(1);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_WithGameObjectButNoOwnerScreen_DoesNotThrow)
    {
      GameObject gameObject;
      AutoDeallocator<MockLoadResourcesAsyncScript> resourceLoader = gameObject.addComponent<MockLoadResourcesAsyncScript>();
      resourceLoader->update(1);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_InvokesOnLoadCompleteEvent)
    {
      bool called = false;

      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<MockLoadResourcesAsyncScript> resourceLoader = gameObject->addComponent<MockLoadResourcesAsyncScript>();
      resourceLoader->getLoadCompleteEvent().subscribe([&called]() -> void
      {
        called = true;
      });

      resourceLoader->update(1);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_UnsubscribesAllSubscribers)
    {
      bool called = false;

      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<MockLoadResourcesAsyncScript> resourceLoader = gameObject->addComponent<MockLoadResourcesAsyncScript>();
      resourceLoader->getLoadCompleteEvent().subscribe([&called]() -> void
      {
        called = true;
      });

      resourceLoader->update(1);

      Assert::IsTrue(called);

      called = false;
      resourceLoader->getLoadCompleteEvent().invoke();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_SetsIsActive)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<MockLoadResourcesAsyncScript> resourceLoader = gameObject->addComponent<MockLoadResourcesAsyncScript>();

      Assert::IsTrue(resourceLoader->isActive());

      resourceLoader->update(1);

      Assert::IsFalse(resourceLoader->isActive());
    }

#pragma endregion

  };
}