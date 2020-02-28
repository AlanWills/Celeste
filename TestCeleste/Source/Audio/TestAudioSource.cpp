#include "UtilityHeaders/UnitTestHeaders.h"
#include "Mocks/Audio/MockAudioSource.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"
#include "OpenAL/OpenALState.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::Resources;
using namespace Celeste::Audio;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestAudioSource)

  //------------------------------------------------------------------------------------------------
  static void TestAudioSource::testClassInitialize()
  {
    // Set up alut if required
    OpenALState::initialize();
  }

  //------------------------------------------------------------------------------------------------
  void TestAudioSource::testInitialize()
  {
    getAudioManager().setMasterVolume(1);
    getAudioManager().setMusicVolume(1);
    getAudioManager().setSFXVolume(1);

    getResourceManager().unloadAll<Sound>();
  }

  //----------------------------------------------------------------------------------------------------------
  void TestAudioSource::testCleanup()
  {
    getResourceManager().unloadAll<Sound>();

    // Recreate the alut state
    OpenALState::terminate();
    OpenALState::initialize();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSource_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<AudioSource>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSource_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(AudioSource::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<AudioSource*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceIsNotPlaying)
    {
      MockAudioSource audioSource;

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSetToNullHandle)
    {
      MockAudioSource audioSource;

      Assert::IsNull(audioSource.getSound());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceIsNotLooping)
    {
      MockAudioSource audioSource;

      Assert::IsFalse(audioSource.isLooping());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceVolumeIsOne)
    {
      MockAudioSource audioSource;

      Assert::AreEqual(1.0f, audioSource.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_SetsAudioTypeToSFX)
    {
      MockAudioSource audioSource;

      Assert::IsTrue(audioSource.getAudioType() == AudioType::kSFX);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_GeneratesSourceHandle)
    {
      MockAudioSource audioSource;

      Assert::AreNotEqual(static_cast<ALuint>(0), audioSource.getSourceHandle_Public());
      Assert::AreEqual(0, audioSource.getSourceBufferHandle());
      Assert::IsTrue(alIsSource(audioSource.getSourceHandle_Public()));
    }

#pragma endregion

#pragma region Destructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Destructor_DeallocatesSourceHandle)
    {
      ALuint audioSourceHandle = 0;

      {
        MockAudioSource audioSource;
        audioSourceHandle = audioSource.getSourceHandle_Public();

        Assert::IsTrue(alIsSource(audioSourceHandle));
      }

      Assert::IsFalse(alIsSource(audioSourceHandle));
    }

#pragma endregion

#pragma region Set Sound Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetSound_InputtingNullptr_DoesNotUpdateSourceBuffer)
    {
      MockAudioSource audioSource;

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());

      audioSource.setSound(nullptr);

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetSound_WithNonExistentSoundPath_DoesNotUpdateSourceBuffer)
    {
      MockAudioSource audioSource;

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());

      audioSource.setSound("ThisAudioFileShouldn'tExist.wav");

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());
    }

#pragma endregion

#pragma region Set Looping Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetLooping_AudioSourceCreated_UpdatesLooping)
    {
      MockAudioSource audio;

      Assert::IsTrue(alIsSource(audio.getSourceHandle_Public()));
      Assert::IsFalse(audio.isLooping());

      audio.setLooping(true);

      Assert::IsTrue(audio.isLooping());
    }

#pragma endregion

#pragma region Set Volume Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_UpdatesVolume)
    {
      MockAudioSource audio;

      Assert::IsTrue(alIsSource(audio.getSourceHandle_Public()));
      Assert::AreEqual(1.0f, audio.getVolume());

      audio.setVolume(0.5f);

      Assert::AreEqual(0.5f, audio.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_AudioSourceCreated_ClampsVolumeBetweenZeroAndOne)
    {
      MockAudioSource audio;

      Assert::IsTrue(alIsSource(audio.getSourceHandle_Public()));
      Assert::AreEqual(1.0f, audio.getVolume());

      audio.setVolume(-2);

      Assert::AreEqual(0.0f, audio.getVolume());

      audio.setVolume(1.5f);

      Assert::AreEqual(1.0f, audio.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_SetsInternalVolume_ToAudioManagerMasterVolumeMultipliedByAudioTypeVolume)
    {
      getAudioManager().setMasterVolume(0.5f);
      getAudioManager().setSFXVolume(0.8f);
      MockAudioSource audio;

      Assert::IsTrue(alIsSource(audio.getSourceHandle_Public()));
      
      audio.setVolume(1);

      float volume[1];
      alGetSourcef(audio.getSourceHandle_Public(), AL_GAIN, volume);

      Assert::AreEqual(0.4f, volume[0]);

      audio.setVolume(0);
      alGetSourcef(audio.getSourceHandle_Public(), AL_GAIN, volume);

      Assert::AreEqual(0.0f, volume[0]);

      audio.setVolume(0.3f);
      alGetSourcef(audio.getSourceHandle_Public(), AL_GAIN, volume);

      AssertExt::AreAlmostEqual(0.12f, volume[0]);
    }

#pragma endregion

#pragma region Play Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_PlayWithNoSoundSet_DoesNothing)
    {
      MockAudioSource audioSource;

      Assert::IsNull(audioSource.getSound());
      Assert::IsFalse(audioSource.isPlaying());

      audioSource.play();

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_UpdatesIsPlayingFlag)
    {
      MockAudioSource audioSource;

      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSource.getSound());
      Assert::IsFalse(audioSource.isPlaying());

      audioSource.play();

      Assert::IsTrue(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_InternallyPlaysSound)
    {
      MockAudioSource audioSource;

      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSource.getSound());

      ALenum state;
      alGetSourcei(audioSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);

      audioSource.play();
      alGetSourcei(audioSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsTrue(state == AL_PLAYING);
    }

#pragma endregion

#pragma region Stop Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_NoSourceCreated_UpdatesIsPlayingFlag)
    {
      MockAudioSource audioSource;
      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());
      audioSource.play();

      Assert::IsTrue(audioSource.isPlaying());

      audioSource.stop();

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_SourceCreated_UpdatesIsPlayingFlag)
    {
      MockAudioSource audioSource;
      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSource.getSound());
      Assert::IsFalse(audioSource.isPlaying());
      Assert::IsTrue(alIsSource(audioSource.getSourceHandle_Public()));

      audioSource.play();

      Assert::IsTrue(audioSource.isPlaying());

      audioSource.stop();

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_SourceCreated_StopsSoundPlayingInternally)
    {
      MockAudioSource audioSource;
      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

      ALenum state;
      alGetSourcei(audioSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);

      audioSource.play();
      alGetSourcei(audioSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsTrue(state == AL_PLAYING);

      audioSource.stop();
      alGetSourcei(audioSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);
    }

#pragma endregion
  };
}