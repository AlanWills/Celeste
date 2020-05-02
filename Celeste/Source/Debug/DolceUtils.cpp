#if _DEBUG

#include "Debug/DolceUtils.h"
#include "Game/Game.h"
#include "Dolce/Dolce.h"


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  Dolce::Dolce& getDolce()
  {
    return *Game::current().getSystem<Dolce::Dolce>();
  }
}

#endif