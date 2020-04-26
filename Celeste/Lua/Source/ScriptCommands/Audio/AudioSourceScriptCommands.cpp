#include "ScriptCommands/Audio/AudioSourceScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Audio/AudioSource.h"
#include "Deserialization/AudioDeserializers.h"

using AudioType = Celeste::Audio::AudioType;
using AudioSource = Celeste::Audio::AudioSource;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Audio::AudioSource> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::Resources::Sound> : std::false_type {};
}

namespace Celeste::Lua::Audio::AudioSourceScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getAudioType(const Celeste::Audio::AudioSource& audioSource)
    {
      std::string output;
      serialize(audioSource.getAudioType(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setSound(AudioSource& audioSource, const std::string& soundStr)
    {
      audioSource.setSound(soundStr);
    }

    //------------------------------------------------------------------------------------------------
    void setAudioType(AudioSource& audioSource, const std::string& audioTypeStr)
    {
      AudioType audioType = AudioType::kMusic;
      if (!Celeste::deserialize<AudioType>(audioTypeStr, audioType))
      {
        ASSERT_FAIL();
        return;
      }

      audioSource.setAudioType(audioType);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using AudioSource = Celeste::Audio::AudioSource;

    registerUserType<AudioSource>(
      state,
      AudioSource::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getSound", &AudioSource::getSound,
      "setSound", &Internals::setSound,
      "getAudioType", &Internals::getAudioType,
      "setAudioType", &Internals::setAudioType,
      "getVolume", &AudioSource::getVolume,
      "setVolume", &AudioSource::setVolume,
      "isLooping", &AudioSource::isLooping,
      "setLooping", &AudioSource::setLooping,
      "isPlaying", &AudioSource::isLooping,
      "play", &AudioSource::play,
      "stop", &AudioSource::stop);
  }
}