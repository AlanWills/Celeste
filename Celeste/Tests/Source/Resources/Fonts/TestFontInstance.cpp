#define NOMINMAX

#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Fonts/MockFontInstance.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"

using namespace Celeste::Resources;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestFontInstance)

#pragma region Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(FontInstance_Constructor_SetsValuesToDefault)
  {
    MockFontInstance instance;

    Assert::AreEqual(0.0f, instance.getHeight());
    Assert::AreEqual((StringId)0, instance.getFontName());
    Assert::AreEqual((size_t)0, instance.getNumberOfCharacters_Public());
  }

#pragma endregion

#pragma region Reset Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(FontInstance_Reset_OnNonLoadedFont_SetsValuesToDefault)
  {
    MockFontInstance instance;

    Assert::AreEqual(0.0f, instance.getHeight());
    Assert::AreEqual((StringId)0, instance.getFontName());
    Assert::AreEqual((size_t)0, instance.getNumberOfCharacters_Public());

    instance.reset();

    Assert::AreEqual(0.0f, instance.getHeight());
    Assert::AreEqual((StringId)0, instance.getFontName());
    Assert::AreEqual((size_t)0, instance.getNumberOfCharacters_Public());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(FontInstance_Reset_OnLoadedFont_SetsValuesToDefault)
  {
    observer_ptr<Font> font = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath());
    FontInstance instance = font->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());
    Assert::AreEqual(font->getResourceId(), instance.getFontName());

    instance.reset();

    Assert::AreEqual(0.0f, instance.getHeight());
    Assert::AreEqual((StringId)0, instance.getFontName());
  }

#pragma endregion

#pragma region Get Character Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetCharacter_WhichDoesntExist)
  {
    MockFontInstance font;

    // Don't load font so our map will be empty
    Assert::IsNull(font.getCharacter('a'));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetCharacter_WhichDoesExist)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::IsNotNull(instance.getCharacter('a'));
  }

#pragma endregion

#pragma region Measure String Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontNotLoaded_ReturnsZeroVector)
  {
    MockFontInstance font;

    Assert::AreEqual(0.0f, font.getHeight());
    Assert::AreEqual((size_t)0, font.getNumberOfCharacters_Public());
    Assert::AreEqual((StringId)0, font.getFontName());
    Assert::AreEqual(glm::vec2(), font.measureString("Hello"));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingEmptyString_Returns_Zero_FontHeight)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());
    Assert::AreEqual(glm::vec2(0, 6.0f), instance.measureString(""));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_ReturnsCorrectDimensions)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::string str = "Hello";
    float x = 0;

    for (char letter : str)
    {
      const Character* character = instance.getCharacter(letter);

      x += character->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance.getHeight()), instance.measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithSpaces_ReturnsCorrectDimensions)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::string str = "H       el  lo";
    float x = 0;

    for (char letter : str)
    {
      x += instance.getCharacter(letter)->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance.getHeight()), instance.measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithNewline_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::string str = "Hello\nWorld";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance.getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("World"))
      {
        x += instance.getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 2 * instance.getHeight()), instance.measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithMultipleNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::string str = "Hello\nGroundControl\nThisIsMajorTom";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance.getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("GroundControl"))
      {
        x += instance.getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    {
      float x = 0;
      for (char letter : std::string("ThisIsMajorTom"))
      {
        x += instance.getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 3 * instance.getHeight()), instance.measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_AllNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::string str = "\n\n\n\n\n";

    Assert::AreEqual(glm::vec2(0, 6 * instance.getHeight()), instance.measureString(str));
  }

#pragma endregion

#pragma region Get Lines Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontNotLoaded_InputtingAnyText_ReturnsEmptyList)
  {
    MockFontInstance instance;

    Assert::AreEqual(0.0f, instance.getHeight());

    std::vector<std::string> outputLines;
    Assert::IsTrue(outputLines.empty());

    instance.getLines("", 100000000000000.0f, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello", 100000000000000.0f, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello\n", 100000000000000.0f, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello\n Wor\nld", 100000000000000.0f, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello", instance.measureString("Hell").x, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hell\no", instance.measureString("Hel").x, outputLines);
    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hell\no W\n\nor\nld", instance.measureString("Hel").x, outputLines);
    Assert::IsTrue(outputLines.empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingEmptyString_ReturnsEmptyList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("", 100000000000000.0f, outputLines);

    Assert::IsTrue(outputLines.empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_ReturnsSingleEntryInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)1, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_AndNewlineCharacter_ReturnsTwoEntriesInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello\n", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)2, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
    Assert::AreEqual("", outputLines[1].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_AndMultipleNewlineCharacters_ReturnsMultipleEntriesInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello\n Wor\nld", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)3, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
    Assert::AreEqual(" Wor", outputLines[1].c_str());
    Assert::AreEqual("ld", outputLines[2].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_ReturnsSplitEntriesInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hello", instance.measureString("Hell").x, outputLines);

    Assert::AreEqual((size_t)2, outputLines.size());
    Assert::AreEqual("Hell", outputLines[0].c_str());
    Assert::AreEqual("o", outputLines[1].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_AndNewlineCharacter_ReturnsSplitEntriesInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hell\no", instance.measureString("Hel").x, outputLines);

    Assert::AreEqual((size_t)3, outputLines.size());
    Assert::AreEqual("Hel", outputLines[0].c_str());
    Assert::AreEqual("l", outputLines[1].c_str());
    Assert::AreEqual("o", outputLines[2].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_AndMultipleNewlineCharacters_ReturnsSplitEntriesInList)
  {
    FontInstance instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance.getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance.getLines("Hell\no W\n\nor\nld", instance.measureString("Hel").x, outputLines);

    Assert::AreEqual((size_t)7, outputLines.size());
    Assert::AreEqual("Hel", outputLines[0].c_str());
    Assert::AreEqual("l", outputLines[1].c_str());
    Assert::AreEqual("o ", outputLines[2].c_str());
    Assert::AreEqual("W", outputLines[3].c_str());
    Assert::AreEqual("", outputLines[4].c_str());
    Assert::AreEqual("or", outputLines[5].c_str());
    Assert::AreEqual("ld", outputLines[6].c_str());
  }

#pragma endregion
  
  };
}