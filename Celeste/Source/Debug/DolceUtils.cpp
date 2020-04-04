#if _DEBUG

#include "Debug/DolceUtils.h"
#include "Game/Game.h"


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  Dolce::Dolce& getDolce()
  {
    return Game::getDolce();
  }
}

#endif