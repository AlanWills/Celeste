#include "Audio/AudioUtils.h"
#include "Game/Game.h"


namespace Celeste::Audio
{
  //------------------------------------------------------------------------------------------------
  AudioManager& getAudioManager()
  {
    return Game::getAudioManager();
  }
}