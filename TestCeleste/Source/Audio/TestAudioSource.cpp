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
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::IsFalse(audioSourceSourceSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSetToNullHandle)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::IsNull(audioSourceSourceSource.getSound());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceIsNotLooping)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::IsFalse(audioSourceSourceSource.isLooping());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_AudioSourceVolumeIsOne)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::AreEqual(1.0f, audioSourceSourceSource.getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_SetsAudioTypeToSFX)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::IsTrue(audioSourceSourceSource.getAudioType() == AudioType::kSFX);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Constructor_GeneratesSourceHandle)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::AreNotEqual(static_cast<ALuint>(0), audioSourceSourceSource.getSourceHandle_Public());
      Assert::AreEqual(0, audioSourceSourceSource.getSourceBufferHandle());
      Assert::IsTrue(alIsSource(audioSourceSourceSource.getSourceHandle_Public()));
    }

#pragma endregion

#pragma region Destructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Destructor_DeallocatesSourceHandle)
    {
      ALuint audioSourceSourceSourceHandle = 0;

      {
        GameObject gameObject;
        MockAudioSource audioSourceSourceSource(gameObject);
        audioSourceSourceSourceHandle = audioSourceSourceSource.getSourceHandle_Public();

        Assert::IsTrue(alIsSource(audioSourceSourceSourceHandle));
      }

      Assert::IsFalse(alIsSource(audioSourceSourceSourceHandle));
    }

#pragma endregion

#pragma region Set Sound Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetSound_InputtingNullptr_DoesNotUpdateSourceBuffer)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::AreEqual(0, audioSourceSourceSource.getSourceBufferHandle());

      audioSourceSourceSource.setSound(nullptr);

      Assert::AreEqual(0, audioSourceSourceSource.getSourceBufferHandle());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_SetSound_WithNonExistentSoundPath_DoesNotUpdateSourceBuffer)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::AreEqual(0, audioSourceSourceSource.getSourceBufferHandle());

      audioSourceSourceSource.setSound("ThisAudioFileShouldn'tExist.wav");

      Assert::AreEqual(0, audioSourceSourceSource.getSourceBufferHandle());
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
      MockAudioSource audioSourceSourceSource(gameObject);

      Assert::IsNull(audioSourceSourceSource.getSound());
      Assert::IsFalse(audioSourceSourceSource.isPlaying());

      audioSourceSourceSource.play();

      Assert::IsFalse(audioSourceSourceSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_UpdatesIsPlayingFlag)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      audioSourceSourceSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSourceSourceSource.getSound());
      Assert::IsFalse(audioSourceSourceSource.isPlaying());

      audioSourceSourceSource.play();

      Assert::IsTrue(audioSourceSourceSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Play_SoundSet_InternallyPlaysSound)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);

      audioSourceSourceSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSourceSourceSource.getSound());

      ALenum state;
      alGetSourcei(audioSourceSourceSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);

      audioSourceSourceSource.play();
      alGetSourcei(audioSourceSourceSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsTrue(state == AL_PLAYING);
    }

#pragma endregion

#pragma region Stop Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_NoSourceCreated_UpdatesIsPlayingFlag)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);
      audioSourceSourceSource.setSound(TestResources::getButtonHoverWavRelativePath());
      audioSourceSourceSource.play();

      Assert::IsTrue(audioSourceSourceSource.isPlaying());

      audioSourceSourceSource.stop();

      Assert::IsFalse(audioSourceSourceSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_SourceCreated_UpdatesIsPlayingFlag)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);
      audioSourceSourceSource.setSound(TestResources::getButtonHoverWavRelativePath());

      Assert::IsNotNull(audioSourceSourceSource.getSound());
      Assert::IsFalse(audioSourceSourceSource.isPlaying());
      Assert::IsTrue(alIsSource(audioSourceSourceSource.getSourceHandle_Public()));

      audioSourceSourceSource.play();

      Assert::IsTrue(audioSourceSourceSource.isPlaying());

      audioSourceSourceSource.stop();

      Assert::IsFalse(audioSourceSourceSource.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioSource_Stop_SourceCreated_StopsSoundPlayingInternally)
    {
      GameObject gameObject;
      MockAudioSource audioSourceSourceSource(gameObject);
      audioSourceSourceSource.setSound(TestResources::getButtonHoverWavRelativePath());

      ALenum state;
      alGetSourcei(audioSourceSourceSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);

      audioSourceSourceSource.play();
      alGetSourcei(audioSourceSourceSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsTrue(state == AL_PLAYING);

      audioSourceSourceSource.stop();
      alGetSourcei(audioSourceSourceSource.getSourceHandle_Public(), AL_SOURCE_STATE, &state);

      Assert::IsFalse(state == AL_PLAYING);
    }

#pragma endregion
  };
}