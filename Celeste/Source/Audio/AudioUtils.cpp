#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"
#include "Game/Game.h"


namespace Celeste::Audio
{
  //------------------------------------------------------------------------------------------------
  AudioManager& getAudioManager()
  {
    return *Game::current().getSystem<Audio::AudioManager>();
  }
}