#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Mocks/Audio/MockAudioSource.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"
#include "OpenAL/OpenALState.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::Resources;
using namespace Celeste::Audio;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestAudioSource)

  //------------------------------------------------------------------------------------------------
  static void testClassInitialize()
  {
    // Set up alut if required
    OpenALState::initialize();
  }

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getAudioManager().setMasterVolume(1);
    getAudioManager().setMusicVolume(1);
    getAudioManager().setSFXVolume(1);

    getResourceManager().unloadAll<Sound>();
  }

  //----------------------------------------------------------------------------------------------------------
  void testCleanup()
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

    observer_ptr<Component> component = ComponentRegistry::createComponent(AudioSource::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<AudioSource*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceIsNotPlaying)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSetToNullHandle)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::IsNull(audioSource.getSound());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceIsNotLooping)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::IsFalse(audioSource.isLooping());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceVolumeIsOne)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::AreEqual(1.0f, audioSource.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_SetsAudioTypeToSFX)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::IsTrue(audioSource.getAudioType() == AudioType::kSFX);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_GeneratesSourceHandle)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

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
        GameObject gameObject;
        MockAudioSource audioSource(gameObject);
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
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());

      audioSource.setSound(nullptr);

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetSound_WithNonExistentSoundPath_DoesNotUpdateSourceBuffer)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());

      audioSource.setSound("ThisAudioFileShouldn'tExist.wav");

      Assert::AreEqual(0, audioSource.getSourceBufferHandle());
    }

#pragma endregion

#pragma region Set Looping Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetLooping_AudioSourceCreated_UpdatesLooping)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSource(gameObject);

      Assert::IsTrue(alIsSource(audioSourceSource.getSourceHandle_Public()));
      Assert::IsFalse(audioSourceSource.isLooping());

      audioSourceSource.setLooping(true);

      Assert::IsTrue(audioSourceSource.isLooping());
    }

#pragma endregion

#pragma region Set Volume Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_UpdatesVolume)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSource(gameObject);

      Assert::IsTrue(alIsSource(audioSourceSource.getSourceHandle_Public()));
      Assert::AreEqual(1.0f, audioSourceSource.getVolume());

      audioSourceSource.setVolume(0.5f);

      Assert::AreEqual(0.5f, audioSourceSource.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_AudioSourceCreated_ClampsVolumeBetweenZeroAndOne)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSource(gameObject);

      Assert::IsTrue(alIsSource(audioSourceSource.getSourceHandle_Public()));
      Assert::AreEqual(1.0f, audioSourceSource.getVolume());

      audioSourceSource.setVolume(-2);

      Assert::AreEqual(0.0f, audioSourceSource.getVolume());

      audioSourceSource.setVolume(1.5f);

      Assert::AreEqual(1.0f, audioSourceSource.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetVolume_SetsInternalVolume_ToAudioManagerMasterVolumeMultipliedByAudioTypeVolume)
    {
      getAudioManager().setMasterVolume(0.5f);
      getAudioManager().setSFXVolume(0.8f);
      
      GameObject gameObject;
      MockAudioSource audioSourceSource(gameObject);

      Assert::IsTrue(alIsSource(audioSourceSource.getSourceHandle_Public()));
      
      audioSourceSource.setVolume(1);

      float volume[1];
      alGetSourcef(audioSourceSource.getSourceHandle_Public(), AL_GAIN, volume);

      Assert::AreEqual(0.4f, volume[0]);

      audioSourceSource.setVolume(0);
      alGetSourcef(audioSourceSource.getSourceHandle_Public(), AL_GAIN, volume);

      Assert::AreEqual(0.0f, volume[0]);

      audioSourceSource.setVolume(0.3f);
      alGetSourcef(audioSourceSource.getSourceHandle_Public(), AL_GAIN, volume);

      AssertExt::AreAlmostEqual(0.12f, volume[0]);
    }

#pragma endregion

#pragma region Play Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_PlayWithNoSoundSet_DoesNothing)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      Assert::IsNull(audioSource.getSound());
      Assert::IsFalse(audioSource.isPlaying());

      audioSource.play();

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_UpdatesIsPlayingFlag)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSource.getSound());
      Assert::IsFalse(audioSource.isPlaying());

      audioSource.play();

      Assert::IsTrue(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_InternallyPlaysSound)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);

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
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);
      audioSource.setSound(TestResources::getButtonHoverWavRelativePath());
      audioSource.play();

      Assert::IsTrue(audioSource.isPlaying());

      audioSource.stop();

      Assert::IsFalse(audioSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_SourceCreated_UpdatesIsPlayingFlag)
    {
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);
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
      GameObject gameObject;
      MockAudioSource audioSource(gameObject);
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