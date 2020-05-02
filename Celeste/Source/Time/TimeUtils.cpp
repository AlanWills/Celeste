#include "Time/TimeUtils.h"
#include "Game/Game.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Clock& getClock()
  {
    return Game::current().getClock();
  }
}