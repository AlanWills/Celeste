#include "Audio/AudioManager.h"
#include "Audio/AudioSource.h"
#include "OpenAL/OpenALState.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Audio;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestAudioManager)

    //------------------------------------------------------------------------------------------------
    static void testClassInitialize()
    {
      // Reset the alut state
      OpenALState::terminate();
      OpenALState::initialize();
    }

    //------------------------------------------------------------------------------------------------
    void testCleanup()
    {
      // Reset the alut state
      OpenALState::terminate();
      OpenALState::initialize();
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_Constructor_SetsMasterVolumeToOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMasterVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_Constructor_SetsMusicVolumeToOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMusicVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_Constructor_SetsSFXVolumeToOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getSFXVolume());
    }

#pragma endregion

#pragma region Set Master Volume Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMasterVolume_UpdatesMasterVolume)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMasterVolume());

      manager.setMasterVolume(0.5f);

      Assert::AreEqual(0.5f, manager.getMasterVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMasterVolume_KeepsPublicVolumeOfAllAllocatedAudioSourcesTheSame)
    {
      AudioManager manager;
      GameObject object;
      observer_ptr<AudioSource> audioSource = object.addComponent<AudioSource>();

      Assert::AreEqual(1.0f, manager.getMasterVolume());
      Assert::AreEqual(1.0f, audioSource->getVolume());

      manager.setMasterVolume(0.5f);

      // Keep this volume the same - internally the volume will be changed
      Assert::AreEqual(1.0f, audioSource->getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMasterVolume_ClampsBetweenZeroAndOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMasterVolume());

      manager.setMasterVolume(-0.5f);

      Assert::AreEqual(0.0f, manager.getMasterVolume());

      manager.setMasterVolume(2);

      Assert::AreEqual(1.0f, manager.getMasterVolume());
    }

#pragma endregion

#pragma region Set Music Volume Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMusicVolume_UpdatesMusicVolume)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMusicVolume());

      manager.setMusicVolume(0.5f);

      Assert::AreEqual(0.5f, manager.getMusicVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMusicVolume_KeepsPublicVolumeOfAllAllocatedMusicAudioSourcesTheSame)
    {
      AudioManager manager;
      GameObject object;
      observer_ptr<AudioSource> audioSource = object.addComponent<AudioSource>();
      audioSource->setAudioType(AudioType::kMusic);

      Assert::IsTrue(audioSource->getAudioType() == AudioType::kMusic);
      Assert::AreEqual(1.0f, manager.getMusicVolume());
      Assert::AreEqual(1.0f, audioSource->getVolume());

      manager.setMusicVolume(0.5f);

      // Keep this volume the same - internally the volume will be changed
      Assert::AreEqual(1.0f, audioSource->getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetMusicVolume_ClampsBetweenZeroAndOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getMusicVolume());

      manager.setMusicVolume(-0.5f);

      Assert::AreEqual(0.0f, manager.getMusicVolume());

      manager.setMusicVolume(2);

      Assert::AreEqual(1.0f, manager.getMusicVolume());
    }

#pragma endregion

#pragma region Set SFX Volume Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetSFXVolume_UpdatesSFXVolume)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getSFXVolume());

      manager.setSFXVolume(0.5f);

      Assert::AreEqual(0.5f, manager.getSFXVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetSFXVolume_KeepsPublicVolumeOfAllAllocatedSFXAudioSourcesTheSame)
    {
      AudioManager manager;
      GameObject object;
      observer_ptr<AudioSource> audioSource = object.addComponent<AudioSource>();
      audioSource->setAudioType(AudioType::kSFX);

      Assert::IsTrue(audioSource->getAudioType() == AudioType::kSFX);
      Assert::AreEqual(1.0f, manager.getSFXVolume());
      Assert::AreEqual(1.0f, audioSource->getVolume());

      manager.setSFXVolume(0.5f);

      // Keep this volume the same - internally the volume will be changed
      Assert::AreEqual(1.0f, audioSource->getVolume());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioManager_SetSFXVolume_ClampsBetweenZeroAndOne)
    {
      AudioManager manager;

      Assert::AreEqual(1.0f, manager.getSFXVolume());

      manager.setSFXVolume(-0.5f);

      Assert::AreEqual(0.0f, manager.getSFXVolume());

      manager.setSFXVolume(2);

      Assert::AreEqual(1.0f, manager.getSFXVolume());
    }

#pragma endregion

  };
}