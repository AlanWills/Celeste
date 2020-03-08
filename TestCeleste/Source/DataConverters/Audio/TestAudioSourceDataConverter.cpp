#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Audio/MockAudioSourceDataConverter.h"
#include "Resources/Audio/AudioSourceLoadingResources.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Resources/ResourceManager.h"
#include "Audio/AudioSource.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;
using namespace Celeste::Audio;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestAudioSourceDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestAudioSourceDataConverter::testInitialize()
  {
    AudioSourceLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<AudioSourceDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(AudioSourceLoadingResources::getValidFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<AudioSource*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Instantiate_SetsInputtedPointer_ToNewAudioSourceDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    AudioSourceDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<AudioSourceDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    AudioSourceDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    AudioSourceDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsElementName_ToInput)
  {
    AudioSourceDataConverter converter;

    Assert::AreEqual("AudioSource", converter.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsSoundPath_ToEmptyPath)
  {
    AudioSourceDataConverter converter;

    Assert::IsTrue(converter.getSoundPath().as_string().empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsIsPlaying_ToFalse)
  {
    AudioSourceDataConverter converter;

    Assert::IsFalse(converter.getIsPlaying());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsIsLooping_ToFalse)
  {
    AudioSourceDataConverter converter;

    Assert::IsFalse(converter.getIsLooping());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsVolume_ToOne)
  {
    AudioSourceDataConverter converter;

    Assert::AreEqual(1.0f, converter.getVolume());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsAudioType_TokMusic)
  {
    AudioSourceDataConverter converter;

    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_AddsSoundPath)
  {
    const MockAudioSourceDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_AddsIsPlaying)
  {
    const MockAudioSourceDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_AddsIsLooping)
  {
    const MockAudioSourceDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_AddsVolume)
  {
    const MockAudioSourceDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_AddsAudioType)
  {
    const MockAudioSourceDataConverter converter;
    
    Assert::IsNotNull(converter.findAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_Constructor_SetsAudioType_TokRequired)
  {
    const MockAudioSourceDataConverter converter;

    Assert::IsTrue(converter.findAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    AudioSourceDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    AudioSourceDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(AudioSourceLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    AudioSourceDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(AudioSourceLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(AudioSourceLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    AudioSourceDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(AudioSourceLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_NoSoundAttribute_DoesNothing_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");

    Assert::IsNull(element->Attribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_SoundAttribute_WithEmptyText_SetsSoundPathToEmpty_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME, "");

    Assert::AreEqual("", element->Attribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_SoundAttribute_WithNonEmptyText_SetsSoundPathToCorrectPath_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME, "WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", element->Attribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getSoundPath().c_str());
  }

#pragma endregion

#pragma region Convert IsPlaying Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_NoIsPlayingAttribute_DoesNothing_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");

    Assert::IsNull(element->Attribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsPlaying());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InvalidIsPlayingAttribute_DoesNothing_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME, "adaidasd");

    Assert::AreEqual("adaidasd", element->Attribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsPlaying());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_ValidIsPlayingAttribute_SetsIsPlayingToCorrectValue_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME, "false");

    Assert::AreEqual("false", element->Attribute(AudioSourceDataConverter::IS_PLAYING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsPlaying());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsPlaying());
  }

#pragma endregion

#pragma region Convert IsLooping Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_NoIsLoopingAttribute_DoesNothing_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");

    Assert::IsNull(element->Attribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsLooping());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsLooping());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InvalidIsLoopingAttribute_DoesNothing_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME, "adaidasd");

    Assert::AreEqual("adaidasd", element->Attribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsLooping());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsLooping());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_ValidIsLoopingAttribute_SetsIsLoopingToCorrectValue_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME, "true");

    Assert::AreEqual("true", element->Attribute(AudioSourceDataConverter::IS_LOOPING_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.getIsLooping());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsLooping());
  }

#pragma endregion

#pragma region Convert Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_NoVolumeAttribute_DoesNothing_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");

    Assert::IsNull(element->Attribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getVolume());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InvalidVolumeAttribute_DoesNothing_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME, "adaidasd");

    Assert::AreEqual("adaidasd", element->Attribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getVolume());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_ValidVolumeAttribute_SetsVolumeToCorrectValue_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "Music");
    element->SetAttribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual("0.2", element->Attribute(AudioSourceDataConverter::VOLUME_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getVolume());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getVolume());
  }

#pragma endregion

#pragma region Convert Audio Type Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_NoAudioTypeAttribute_DoesNothing_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");

    Assert::IsNull(element->Attribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_InvalidAudioTypeAttribute_DoesNothing_ReturnsFalse)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "adaidasd");

    Assert::AreEqual("adaidasd", element->Attribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_ConvertFromXML_ValidAudioTypeAttribute_SetsAudioTypeToCorrectValue_ReturnsTrue)
  {
    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("AudioSource");
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "SFX");

    Assert::AreEqual("SFX", element->Attribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kMusic);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getAudioType() == Audio::AudioType::kSFX);
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_SetValues_InputtingAudioSource_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    AudioSource audioSource(gameObject);
    audioSource.setVolume(0.4f);
    audioSource.setLooping(true);

    AudioSourceDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(audioSource);

    Assert::AreEqual(0.4f, audioSource.getVolume());
    Assert::IsTrue(audioSource.isLooping());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_SetValues_InputtingAudioSource_DataLoadedCorrectly_ChangesAudioSourceToMatchData)
  {
    GameObject gameObject;
    AudioSource audioSource(gameObject);
    audioSource.setVolume(0.4f);
    audioSource.setLooping(true);
    audioSource.setAudioType(Audio::AudioType::kSFX);

    // Valid.xml
    // <AudioSource sound="SFX\ButtonHover.wav" is_playing="true" is_looping="true" volume="0.5" audio_type="Music"/>

    AudioSourceDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(AudioSourceLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(audioSource);

    Assert::IsNotNull(audioSource.getSound());
    Assert::IsTrue(getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath()) == audioSource.getSound());
    Assert::IsTrue(audioSource.isPlaying());
    Assert::IsTrue(audioSource.isLooping());
    Assert::AreEqual(0.5f, audioSource.getVolume());
    Assert::IsTrue(audioSource.getAudioType() == Audio::AudioType::kMusic);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceDataConverter_SetValues_DoesNotSetSoundIfPathIsEmpty)
  {
    GameObject gameObject;
    AudioSource audioSource(gameObject);
    audioSource.setVolume(0.4f);
    audioSource.setLooping(true);
    audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(audioSource.getSound());

    AudioSourceDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement(AudioSource::type_name());
    element->SetAttribute(AudioSourceDataConverter::AUDIO_TYPE_ATTRIBUTE_NAME, "SFX");
    converter.convertFromXML(element);

    Assert::IsNull(element->FindAttribute(AudioSourceDataConverter::SOUND_PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(audioSource);

    Assert::IsNotNull(audioSource.getSound());
    Assert::IsTrue(getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath()) == audioSource.getSound());
  }

#pragma endregion

  };
}