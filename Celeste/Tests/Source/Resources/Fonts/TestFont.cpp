#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Fonts/MockFont.h"
#include "TestResources/TestResources.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestFont)

#pragma region Constructor Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_Constructor_SetsValuesToDefault)
    {
      MockFont font;

      Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_Unload_OnNonLoadedFont_DoesNotThow)
    {
      MockFont font;
      font.unload();

      // Check it doesn't throw
      Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_Unload_OnNonLoadedFont_SetsResourceIdToZero)
    {
      MockFont font;
      font.loadFromFile(Path("ThisShouldNotExist.ttf"));

      Assert::AreEqual(static_cast<StringId>(0), font.getResourceId());

      font.unload();

      Assert::AreEqual(static_cast<StringId>(0), font.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_Unload_OnLoadedFont_SetsResourceIdToZero)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      Assert::AreNotEqual(static_cast<StringId>(0), font.getResourceId());

      font.unload();

      Assert::AreEqual(static_cast<StringId>(0), font.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_Unload_ClearsCharacterLookup)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());
      font.createInstance(12);  // Generate some characters

      Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());

      font.unload();

      Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());
    }

#pragma endregion

#pragma region Create Instance Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_FontNotLoaded_ReturnsFontInstance_WithZeroHeight)
    {
      MockFont font;
      FontInstance instance = font.createInstance(4);

      Assert::AreEqual(0.0f, instance.getHeight());
      Assert::AreEqual((StringId)0, instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_ReturnsFontInstance_WithCorrectValues)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      FontInstance instance = font.createInstance(4);

      Assert::AreEqual(4.0f, instance.getHeight());
      Assert::AreEqual(font.getResourceId(), instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_InputtingZero_ReturnsFontInstance_WithZeroHeight)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      FontInstance instance = font.createInstance(0);

      Assert::AreEqual(0.0f, instance.getHeight());
      Assert::AreEqual(font.getResourceId(), instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_InputtingNegative_ReturnsFontInstance_WithZeroHeight)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      FontInstance instance = font.createInstance(-12);

      Assert::AreEqual(0.0f, instance.getHeight());
      Assert::AreEqual(font.getResourceId(), instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_WithHeightNotAlreadyLoaded_AddsToLookup)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());

      FontInstance instance = font.createInstance(4);

      Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());
      Assert::AreEqual(font.getResourceId(), instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_WithHeightAlreadyLoaded_UsesDataInLookup)
    {
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());

      FontInstance instance = font.createInstance(4);

      Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());

      FontInstance secondInstance = font.createInstance(4);

      Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());
      Assert::AreEqual(font.getResourceId(), instance.getFontName());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Font_CreateInstance_DoesNotAffectOtherInstances)
    {
      // The font instances were originally motivated by a bug I had
      // The information for the font instance used to live in the Font class, but I realised that multiple renderers
      // sharing the same font instance editted the same values.
      // As a result, a font could only ever have one height.
      // With font instances, the font acts as a single resource, spawning off copies for individual heights
      MockFont font;
      font.loadFromFile(TestResources::getArialTtfFullPath());

      FontInstance instance = font.createInstance(4);
      FontInstance secondInstance = font.createInstance(4);

      instance.reset();

      Assert::AreEqual(0.0f, instance.getHeight());
      Assert::AreEqual(4.0f, secondInstance.getHeight());
      Assert::AreEqual((StringId)0, instance.getFontName());
      Assert::AreEqual(font.getResourceId(), secondInstance.getFontName());
    }

#pragma endregion
    };
  }
}