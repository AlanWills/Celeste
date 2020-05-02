#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Time/TimeUtils.h"
#include "Game/Game.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTimeUtils)

  #pragma region Get Clock Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GetClock_ShouldReturnGameClock)
  {
    Assert::IsTrue(&Celeste::Game::current().getClock() == &Celeste::getClock());
  }

  #pragma endregion

  };
}