#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/KillOwnerScreen.h"
#include "Screens/Screen.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestKillOwnerScreen);

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillOwnerScreen_Operator_InputtingGameObjectWithNullOwnerScreen_DoesNothing)
  {
    GAMEOBJECT(gameObject);

    Assert::IsNull(gameObject.getScreen());

    KillOwnerScreen callback;

    // Shouldn't throw
    callback(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KillOwnerScreen_Operator_KillsGameObjectOwnerScreen)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    AssertCel::IsAlive(screen.get());

    KillOwnerScreen callback;
    callback(*gameObject);

    AssertCel::IsNotAlive(screen.get());
  }

#pragma endregion

  };
}