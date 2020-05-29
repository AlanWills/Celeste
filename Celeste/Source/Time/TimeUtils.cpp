#include "Time/TimeUtils.h"
#include "Game/Game.h"


namespace Celeste::Time
{
  //------------------------------------------------------------------------------------------------
  Clock& getClock()
  {
    return Game::current().getClock();
  }

  //------------------------------------------------------------------------------------------------
  float getElapsedDeltaTime()
  {
    return getClock().getElapsedDeltaTime();
  }
}