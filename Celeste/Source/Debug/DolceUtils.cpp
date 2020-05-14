#if _DEBUG

#include "Debug/DolceUtils.h"
#include "Game/Game.h"
#include "Dolce/IDolce.h"


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  Dolce::IDolce& getDolce()
  {
    return *Game::current().getSystem<Dolce::IDolce>();
  }
}

#endif