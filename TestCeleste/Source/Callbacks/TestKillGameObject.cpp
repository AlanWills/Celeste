#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/KillGameObject.h"
#include "Screens/Screen.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKillGameObject)

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillGameObject_Operator_InputtingGameObjectWithNullOwnerScreen_DoesNothing)
  {
    GAMEOBJECT(gameObject);

    Assert::IsNull(gameObject.getScreen());
    AssertCel::IsAlive(gameObject);

    KillGameObject callback;

    // Shouldn't throw
    callback(gameObject, "Test");

    AssertCel::IsAlive(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillGameObject_Operator_InputtingEmptyArgString_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsAlive(gameObject.get());

    KillGameObject callback;

    // Shouldn't throw
    callback(*gameObject, "");

    AssertCel::IsAlive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillGameObject_Operator_InputtingGameObjectWithSameNameAsArg_KillsInputtedGameObject)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    gameObject->setName("Test");

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsAlive(gameObject.get());

    KillGameObject callback;
    callback(*gameObject, "Test");

    AssertCel::IsNotAlive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillGameObject_Operator_InputtingName_WithNoGameObjectInScreenWithSameName_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsNull(screen->findGameObject("Test"));
    AssertCel::IsAlive(gameObject.get());

    KillGameObject callback;

    // Check does not throw
    callback(*gameObject, "Test");

    AssertCel::IsAlive(gameObject.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillGameObject_Operator_InputtingName_WithGameObjectInScreenWithSameName_KillsGameObject)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    AutoDeallocator<GameObject> namedGameObject = screen->allocateGameObject();
    namedGameObject->setName("Test");

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsAlive(namedGameObject.get());
    Assert::IsNotNull(screen->findGameObject("Test"));

    KillGameObject callback;
    callback(*gameObject, "Test");

    AssertCel::IsNotAlive(namedGameObject.get());
  }

#pragma endregion

  };
}