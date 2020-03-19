#include "UtilityHeaders/UnitTestHeaders.h"

#include "Loading/LoadResourcesAsyncScript.h"
#include "Objects/GameObject.h"

#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLoadResourcesAsyncScript)

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_WithGameObjectButNoOwnerScreen_DoesNotThrow)
  {
    GameObject gameObject;
    observer_ptr<LoadResourcesAsyncScript> resourceLoader = gameObject.addComponent<LoadResourcesAsyncScript>();
    resourceLoader->update(1);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LoadResourcesAsyncScript_OnTimeComplete_InvokesOnLoadCompleteEvent)
  {
    bool called = false;

    GameObject gameObject;
    observer_ptr<LoadResourcesAsyncScript> resourceLoader = gameObject.addComponent<LoadResourcesAsyncScript>();
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

    GameObject gameObject;
    observer_ptr<LoadResourcesAsyncScript> resourceLoader = gameObject.addComponent<LoadResourcesAsyncScript>();
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
    GameObject gameObject;
    observer_ptr<LoadResourcesAsyncScript> resourceLoader = gameObject.addComponent<LoadResourcesAsyncScript>();

    Assert::IsTrue(resourceLoader->isActive());

    resourceLoader->update(1);

    Assert::IsFalse(resourceLoader->isActive());
  }

#pragma endregion

  };
}