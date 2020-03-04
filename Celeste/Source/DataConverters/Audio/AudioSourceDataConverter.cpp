#include "DataConverters/Audio/AudioSourceDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Audio/AudioSource.h"

using namespace Celeste::Audio;


namespace Celeste
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(AudioSourceDataConverter)

  const char* const AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME("sound");
  const char* const AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME("is_playing");
  const char* const AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME("is_looping");
  const char* const AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME("volume");
  const char* const AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME("audio_type");

  //------------------------------------------------------------------------------------------------
  AudioSourceDataConverter::AudioSourceDataConverter() :
    Inherited(AudioSource::type_name()),
    m_soundPath(createReferenceAttribute<Path>(SOUND_PATH_ATTRIBUTE_NAME)),
    m_isPlaying(createValueAttribute(IS_PLAYING_ATTRIBUTE_NAME, false)),
    m_isLooping(createValueAttribute(IS_LOOPING_ATTRIBUTE_NAME, false)),
    m_volume(createValueAttribute(VOLUME_ATTRIBUTE_NAME, 1.0f)),
    m_audioType(createValueAttribute(AUDIO_TYPE_ATTRIBUTE_NAME, Audio::AudioType::kMusic, DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  void AudioSourceDataConverter::doSetValues(AudioSource& audioSource) const
  {
    if (!getSoundPath().as_string().empty())
    {
      audioSource.setSound(getSoundPath());
    }

    audioSource.setAudioType(getAudioType());
    audioSource.setVolume(getVolume());
    audioSource.setLooping(getIsLooping());

    if (getIsPlaying())
    {
      audioSource.play();
    }
  }
}