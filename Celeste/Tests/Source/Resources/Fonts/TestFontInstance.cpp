#define NOMINMAX

#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Fonts/MockFontInstance.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"

using namespace Celeste::Resources;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestFontInstance)

#pragma region Get Character Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetCharacter_WhichDoesntExist)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);
    
    Assert::IsNull(instance->getCharacter(static_cast<GLchar>(-1)));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetCharacter_WhichDoesExist)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::IsNotNull(instance->getCharacter('a'));
  }

#pragma endregion

#pragma region Measure String Tests

#pragma region String Overload

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingEmptyString_Returns_Zero_FontHeight)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());
    Assert::AreEqual(glm::vec2(0, 6.0f), instance->measureString(""));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_ReturnsCorrectDimensions)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello";
    float x = 0;

    for (char letter : str)
    {
      const Character* character = instance->getCharacter(letter);

      x += character->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance->getHeight()), instance->measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithSpaces_ReturnsCorrectDimensions)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "H       el  lo";
    float x = 0;

    for (char letter : str)
    {
      x += instance->getCharacter(letter)->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance->getHeight()), instance->measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithNewline_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello\nWorld";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("World"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 2 * instance->getHeight()), instance->measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_WithMultipleNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello\nGroundControl\nThisIsMajorTom";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("GroundControl"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    {
      float x = 0;
      for (char letter : std::string("ThisIsMajorTom"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 3 * instance->getHeight()), instance->measureString(str));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEmptyString_AllNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "\n\n\n\n\n";

    Assert::AreEqual(glm::vec2(0, 6 * instance->getHeight()), instance->measureString(str));
  }

#pragma endregion

#pragma region Iterators Overload

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingEqualIterators_Returns_Zero_FontHeight)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);
    std::string str("");

    Assert::AreEqual(6.0f, instance->getHeight());
    Assert::AreEqual(glm::vec2(0, 6.0f), instance->measureString(str.begin(), str.end()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEqualIterators_ReturnsCorrectDimensions)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello";
    float x = 0;

    for (char letter : str)
    {
      const Character* character = instance->getCharacter(letter);

      x += character->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance->getHeight()), instance->measureString(str.begin(), str.end()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEqualIterators_WithSpaces_ReturnsCorrectDimensions)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "H       el  lo";
    float x = 0;

    for (char letter : str)
    {
      x += instance->getCharacter(letter)->m_advance;
    }

    Assert::AreEqual(glm::vec2(x, instance->getHeight()), instance->measureString(str.begin(), str.end()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEqualIterators_WithNewline_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello\nWorld";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("World"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 2 * instance->getHeight()), instance->measureString(str.begin(), str.end()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEqualIterators_WithMultipleNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "Hello\nGroundControl\nThisIsMajorTom";
    float maxX = 0;

    {
      float x = 0;
      for (char letter : std::string("Hello"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = x;
    }

    {
      float x = 0;
      for (char letter : std::string("GroundControl"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    {
      float x = 0;
      for (char letter : std::string("ThisIsMajorTom"))
      {
        x += instance->getCharacter(letter)->m_advance;
      }

      maxX = std::max(x, maxX);
    }

    Assert::AreEqual(glm::vec2(maxX, 3 * instance->getHeight()), instance->measureString(str.begin(), str.end()));
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_MeasureString_FontLoaded_InputtingNonEqualIterators_AllNewlines_ReturnsCorrectDimensions)
  {
    // Don't use raw char strings as they end in a \0
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::string str = "\n\n\n\n\n";

    Assert::AreEqual(glm::vec2(0, 6 * instance->getHeight()), instance->measureString(str.begin(), str.end()));
  }

#pragma endregion

#pragma endregion

#pragma region Get Lines Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingEmptyString_ReturnsEmptyList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("", 100000000000000.0f, outputLines);

    Assert::IsTrue(outputLines.empty());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_ReturnsSingleEntryInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hello", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)1, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_AndNewlineCharacter_ReturnsTwoEntriesInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hello\n", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)2, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
    Assert::AreEqual("", outputLines[1].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthLessThanMaxWidth_AndMultipleNewlineCharacters_ReturnsMultipleEntriesInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hello\n Wor\nld", 100000000000000.0f, outputLines);

    Assert::AreEqual((size_t)3, outputLines.size());
    Assert::AreEqual("Hello", outputLines[0].c_str());
    Assert::AreEqual(" Wor", outputLines[1].c_str());
    Assert::AreEqual("ld", outputLines[2].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_ReturnsSplitEntriesInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hello", instance->measureString("Hell").x, outputLines);

    Assert::AreEqual((size_t)2, outputLines.size());
    Assert::AreEqual("Hell", outputLines[0].c_str());
    Assert::AreEqual("o", outputLines[1].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_AndNewlineCharacter_ReturnsSplitEntriesInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hell\no", instance->measureString("Hel").x, outputLines);

    Assert::AreEqual((size_t)3, outputLines.size());
    Assert::AreEqual("Hel", outputLines[0].c_str());
    Assert::AreEqual("l", outputLines[1].c_str());
    Assert::AreEqual("o", outputLines[2].c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(Font_GetLines_FontLoaded_InputtingString_WithLengthGreaterThanMaxWidth_AndMultipleNewlineCharacters_ReturnsSplitEntriesInList)
  {
    auto instance = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath())->createInstance(6);

    Assert::AreEqual(6.0f, instance->getHeight());

    std::vector<std::string> outputLines;

    Assert::IsTrue(outputLines.empty());

    instance->getLines("Hell\no W\n\nor\nld", instance->measureString("Hel").x, outputLines);

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