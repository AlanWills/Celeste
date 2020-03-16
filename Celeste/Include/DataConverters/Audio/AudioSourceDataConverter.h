#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "Deserialization/AudioDeserializers.h"
#include "Bindings/AudioDataBindingGenerators.h"
#include "Audio/AudioEnums.h"


namespace Celeste::Audio
{
  class AudioSource;
}

namespace Celeste
{
  class AudioSourceDataConverter : public ComponentDataConverter
  {
    DECLARE_MANAGED_COMPONENT_DATA_CONVERTER(AudioSourceDataConverter, Audio::AudioSource, CelesteDllExport)

    public:
      inline const Path& getSoundPath() const { return m_soundPath.getValue(); }
      inline bool getIsPlaying() const { return m_isPlaying.getValue(); }
      inline bool getIsLooping() const { return m_isLooping.getValue(); }
      inline float getVolume() const { return m_volume.getValue(); }
      inline Audio::AudioType getAudioType() const { return m_audioType.getValue(); }

      CelesteDllExport static const char* const SOUND_PATH_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const IS_PLAYING_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const IS_LOOPING_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const VOLUME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const AUDIO_TYPE_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<Path>& m_soundPath;
      XML::ValueAttribute<bool>& m_isPlaying;
      XML::ValueAttribute<bool>& m_isLooping;
      XML::ValueAttribute<float>& m_volume;
      XML::ValueAttribute<Audio::AudioType>& m_audioType;
  };
}