#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/ActivateGameObject.h"
#include "Screens/Screen.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestActivateGameObject);

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ActivateGameObject_Operator_InputtingGameObjectWithNullOwnerScreen_DoesNothing)
  {
    GAMEOBJECT(gameObject);

    Assert::IsNull(gameObject.getScreen());
    AssertCel::IsActive(gameObject);

    ActivateGameObject callback;

    // Shouldn't throw
    callback(gameObject, "Test");

    AssertCel::IsActive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ActivateGameObject_Operator_InputtingEmptyArgsString_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsActive(gameObject.get());

    ActivateGameObject callback;

    // Shouldn't throw
    callback(*gameObject.get(), "");

    AssertCel::IsActive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ActivateGameObject_Operator_InputtingGameObjectWithSameNameAsArg_ActivatesInput)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    gameObject->setName("Test");
    gameObject->setActive(false);

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsNotActive(gameObject.get());

    ActivateGameObject callback;
    callback(*gameObject.get(), "Test");

    AssertCel::IsActive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ActivateGameObject_Operator_InputtingName_WithNoGameObjectInScreenWithSameName_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsNull(screen->findGameObject("Test"));
    AssertCel::IsActive(gameObject.get());

    ActivateGameObject callback;

    // Check does not throw
    callback(*gameObject.get(), "Test");

    AssertCel::IsActive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ActivateGameObject_Operator_InputtingName_WithGameObjectInScreenWithSameName_SetsGameObjectToActive)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    AutoDeallocator<GameObject> namedGameObject = screen->allocateGameObject();
    namedGameObject->setName("Test");
    namedGameObject->setActive(false);

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsNotActive(namedGameObject.get());
    Assert::IsNotNull(screen->findGameObject("Test"));

    ActivateGameObject callback;
    callback(*gameObject.get(), "Test");

    AssertCel::IsActive(namedGameObject.get());
  }

#pragma endregion

  };
}