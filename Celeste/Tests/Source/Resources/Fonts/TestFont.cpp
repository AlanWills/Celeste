#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Fonts/MockFont.h"
#include "TestResources/TestResources.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste::Resources;


namespace TestCeleste::Resources
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

    Assert::AreEqual(string_id(), font.getResourceId());

    font.unload();

    Assert::AreEqual(string_id(), font.getResourceId());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_Unload_OnLoadedFont_SetsResourceIdToZero)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    Assert::AreNotEqual(string_id(), font.getResourceId());

    font.unload();

    Assert::AreEqual(string_id(), font.getResourceId());
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
  TEST_METHOD(Font_CreateInstance_FontNotLoaded_ReturnsNullptr)
  {
    MockFont font;
    std::unique_ptr<FontInstance> instance = font.createInstance(4);

    AssertExt::IsNull(instance);
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_CreateInstance_ReturnsFontInstance_WithCorrectValues)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    std::unique_ptr<FontInstance> instance = font.createInstance(4);

    AssertExt::IsNotNull(instance);
    Assert::AreEqual(4.0f, instance->getHeight());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_CreateInstance_InputtingZero_ReturnsNullptr)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    std::unique_ptr<FontInstance> instance = font.createInstance(0);

    AssertExt::IsNull(instance);
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_CreateInstance_InputtingNegative_ReturnsNullptr)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    std::unique_ptr<FontInstance> instance = font.createInstance(-12);

    AssertExt::IsNull(instance);
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_CreateInstance_WithHeightNotAlreadyLoaded_AddsToLookup)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());

    std::unique_ptr<FontInstance> instance = font.createInstance(4);

    Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_CreateInstance_WithHeightAlreadyLoaded_UsesDataInLookup)
  {
    MockFont font;
    font.loadFromFile(TestResources::getArialTtfFullPath());

    Assert::AreEqual((size_t)0, font.getNumberOfHeightsLoaded_Public());

    std::unique_ptr<FontInstance> instance = font.createInstance(4);

    Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());

    std::unique_ptr<FontInstance> secondInstance = font.createInstance(4);

    Assert::AreEqual((size_t)1, font.getNumberOfHeightsLoaded_Public());
  }

#pragma endregion
  
  };
}