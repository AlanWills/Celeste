#include "UtilityHeaders/UnitTestHeaders.h"

#include "Resources/Audio/Sound.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
#include "AutoALDeallocator.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestSound)

    //----------------------------------------------------------------------------------------------------------
    void TestSound::testInitialize()
    {
      getResourceManager().unloadAll<Sound>();
    }

    //----------------------------------------------------------------------------------------------------------
    void TestSound::testCleanup()
    {
      getResourceManager().unloadAll<Sound>();
    }

#pragma region Constructor Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Constructor_SetsAudioHandleTo_AL_NONE)
    {
      Sound sound;

      Assert::AreEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

#pragma endregion

#pragma region Load Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithNonExistentFilePath_ReturnsFalse)
    {
      Sound sound;
      bool result = sound.loadFromFile(Path("ThisAudioDoesntExist.wav"));

      AutoALDeallocator deallocator(sound.getAudioHandle());

      Assert::IsFalse(result);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithNonExistentFilePath_LeavesObjectUnchanged)
    {
      Sound sound;
      sound.loadFromFile(Path("ThisAudioDoesntExist.wav"));

      AutoALDeallocator deallocator(sound.getAudioHandle());

      Assert::AreEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithExistentNonAudioFilePath_ReturnsFalse)
    {
      Sound sound;

      Assert::IsFalse(sound.loadFromFile(TestResources::getArialTtfFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithExistentNonAudioFilePath_LeavesObjectUnchanged)
    {
      Sound sound;
      sound.loadFromFile(TestResources::getArialTtfFullPath());

      AutoALDeallocator deallocator(sound.getAudioHandle());

      Assert::AreEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithExistentAudioFilePath_ReturnsTrue)
    {
      Sound sound;

      Assert::IsTrue(sound.loadFromFile(TestResources::getButtonHoverWavFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Load_WithExistentAudioFilePath_LoadsAudioFile)
    {
      Sound sound;
      sound.loadFromFile(TestResources::getButtonHoverWavFullPath());

      AutoALDeallocator deallocator(sound.getAudioHandle());

      Assert::AreNotEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Unload_WithNonLoadedAudio_DoesNotThrow)
    {
      Sound sound;
      sound.unload();

      AutoALDeallocator deallocator(sound.getAudioHandle());

      //Assert::IsFalse(alIsBuffer(audioSource.getAudioHandle()));
      Assert::AreEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_Unload_WithLoadedAudio_DeallocatesAudioBuffer_AndResetsHandle)
    {
      Sound sound;
      sound.loadFromFile(TestResources::getButtonHoverWavFullPath());

      AutoALDeallocator deallocator(sound.getAudioHandle());

      sound.unload();

      Assert::AreEqual(static_cast<ALuint>(AL_NONE), sound.getAudioHandle());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_UnloadFromFile_WithNonLoadedSound_SetsResourceIdToZero)
    {
      Sound sound;
      sound.loadFromFile(Path("ThisFileShouldntExist.wav"));

      Assert::AreEqual(static_cast<StringId>(0), sound.getResourceId());

      sound.unload();

      Assert::AreEqual(static_cast<StringId>(0), sound.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Sound_UnloadFromFile_WithLoadedSound_SetsResourceIdToZero)
    {
      Sound sound;
      sound.loadFromFile(TestResources::getButtonHoverWavFullPath());

      Assert::AreNotEqual(static_cast<StringId>(0), sound.getResourceId());

      sound.unload();

      Assert::AreEqual(static_cast<StringId>(0), sound.getResourceId());
    }

#pragma endregion
    };
  }
}