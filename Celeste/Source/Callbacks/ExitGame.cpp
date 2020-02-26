#include "Callbacks/ExitGame.h"
#include "UtilityHeaders/CallbackHeaders.h"
#include "Game/Game.h"


namespace Celeste
{
  REGISTER_CALLBACK(ExitGame)

  //------------------------------------------------------------------------------------------------
  void ExitGame::operator()(GameObject&, const std::string&)
  {
    Game::exit();
  }
}