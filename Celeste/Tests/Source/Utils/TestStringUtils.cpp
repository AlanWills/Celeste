#include "UtilityHeaders/UnitTestHeaders.h"
#include "Utils/StringUtils.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestStringUtils)

#pragma region Empty Wchar to Char Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_EmptyWcharToChar)
    {
      std::wstring w_string(L"");
      char string[50];

      size_t amountConverted = wcharToChar(w_string.c_str(), string, 50);

      Assert::AreEqual("", string);
      Assert::AreEqual((size_t)0, amountConverted);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_NonEmptyWcharToChar)
    {
      std::wstring w_string(L"Test String");
      char string[50];

      size_t amountConverted = wcharToChar(w_string.c_str(), string, 50);

      Assert::AreEqual("Test String", string);
      Assert::AreEqual(w_string.size(), amountConverted);
    }

#pragma endregion

#pragma region Char to Wchar tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_EmptyCharToWchar)
    {
      std::string string("");
      wchar_t w_string[50];

      size_t amountConverted = charToWchar(string.c_str(), w_string, 50);

      Assert::AreEqual(L"", w_string);
      Assert::AreEqual((size_t)0, amountConverted);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_NonEmptyCharToWchar)
    {
      std::string string("Test String");
      wchar_t w_string[50];

      size_t amountConverted = charToWchar(string.c_str(), w_string, 50);

      Assert::AreEqual(L"Test String", w_string);
      Assert::AreEqual(string.size(), amountConverted);
    }

#pragma endregion

#pragma region Split Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_EmptyString_ReturnsEmptyList)
    {
      std::vector<std::string> lines;
      split("", lines);

      Assert::AreEqual((size_t)0, lines.size());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_SingleLineText_ReturnsSingleEntryInList)
    {
      std::vector<std::string> lines;
      split("Hello Ground Control", lines);

      Assert::AreEqual((size_t)1, lines.size());
      Assert::AreEqual("Hello Ground Control", lines[0].c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_TextWithNewlineAtEnd_ReturnsTextAndEmptyStringInList)
    {
      std::vector<std::string> lines;
      split("Hello Ground Control\n", lines);

      Assert::AreEqual((size_t)2, lines.size());
      Assert::AreEqual("Hello Ground Control", lines[0].c_str());
      Assert::AreEqual("", lines[1].c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_TextWithNewlineInMiddle_ReturnsTwoLines)
    {
      std::vector<std::string> lines;
      split("Hello Ground\n Control", lines);

      Assert::AreEqual((size_t)2, lines.size());
      Assert::AreEqual("Hello Ground", lines[0].c_str());
      Assert::AreEqual(" Control", lines[1].c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_TextWithMultipleNewlines_ReturnsCorrectLines)
    {
      std::vector<std::string> lines;
      split("Hell\no Ground\n Control\n", lines);

      Assert::AreEqual((size_t)4, lines.size());
      Assert::AreEqual("Hell", lines[0].c_str());
      Assert::AreEqual("o Ground", lines[1].c_str());
      Assert::AreEqual(" Control", lines[2].c_str());
      Assert::AreEqual("", lines[3].c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_Split_AllNewlines_ReturnsCorrectLines)
    {
      std::vector<std::string> lines;
      split("\n\n\n\n\n", lines);

      Assert::AreEqual((size_t)6, lines.size());

      for (size_t i = 0; i < 6; ++i)
      {
        Assert::AreEqual("", lines[i].c_str());
      }
    }

#pragma endregion

#pragma region Numeric To String Append Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringUtils_IntToStringAppend)
    {
      {
        std::string actual;
        numericToStringAppend(0, actual);

        Assert::AreEqual("0", actual.c_str());
      }

      {
        std::string actual;
        numericToStringAppend(1010101010, actual);

        Assert::AreEqual("1010101010", actual.c_str());
      }

      {
        std::string actual("Hello");
        numericToStringAppend(-9999999, actual);

        Assert::AreEqual("Hello-9999999", actual.c_str());
      }

      {
        std::string actual("Hello");
        numericToStringAppend(-0.00054f, actual);

        Assert::AreEqual("Hello-0.000540", actual.c_str());
      }
    }

#pragma endregion

#pragma region LTrim Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrim_InputtingEmptyString_DoesNothing)
  {
    std::string input;
    ltrim(input);

    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrim_InputtingNonEmptyString_WithNoLeadingSpaces_DoesNothing)
  {
    std::string input("Test  ");
    ltrim(input);

    Assert::AreEqual("Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrim_InputtingNonEmptyString_WithLeadingSpaces_RemovesSpaces)
  {
    std::string input("   Test  ");
    ltrim(input);

    Assert::AreEqual("Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrim_InputtingWhitespace_SetsStringToEmptyString)
  {
    std::string input("   ");
    ltrim(input);

    Assert::IsTrue(input.empty());
  }

#pragma endregion

#pragma region LTrim Copy Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrimCopy_InputtingEmptyString_ReturnsEmptyString)
  {
    std::string input;

    Assert::IsTrue(ltrim_copy(input).empty());
    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrimCopy_InputtingNonEmptyString_WithNoLeadingSpaces_ReturnsInput)
  {
    std::string input("Test  ");

    Assert::AreEqual("Test  ", ltrim_copy(input).c_str());
    Assert::AreEqual("Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrimCopy_InputtingNonEmptyString_WithLeadingSpaces_ReturnsStringWithSpacesRemoved)
  {
    std::string input("   Test  ");

    Assert::AreEqual("Test  ", ltrim_copy(input).c_str());
    Assert::AreEqual("   Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LTrimCopy_InputtingWhitespace_ReturnsEmptyString)
  {
    std::string input("   ");

    Assert::IsTrue(ltrim_copy(input).empty());
    Assert::AreEqual("   ", input.c_str());
  }

#pragma endregion

#pragma region RTrim Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrim_InputtingEmptyString_DoesNothing)
  {
    std::string input;
    rtrim(input);

    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrim_InputtingNonEmptyString_WithNoTrailingSpaces_DoesNothing)
  {
    std::string input("    Test");
    rtrim(input);

    Assert::AreEqual("    Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrim_InputtingNonEmptyString_WithTrailingSpaces_RemovesSpaces)
  {
    std::string input("   Test  ");
    rtrim(input);

    Assert::AreEqual("   Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrim_InputtingWhitespace_SetsStringToEmptyString)
  {
    std::string input("   ");
    rtrim(input);

    Assert::IsTrue(input.empty());
  }

#pragma endregion

#pragma region RTrim Copy Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrimCopy_InputtingEmptyString_ReturnsEmptyString)
  {
    std::string input;

    Assert::IsTrue(rtrim_copy(input).empty());
    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrimCopy_InputtingNonEmptyString_WithNoTrailingSpaces_ReturnsInput)
  {
    std::string input("   Test");

    Assert::AreEqual("   Test", rtrim_copy(input).c_str());
    Assert::AreEqual("   Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrimCopy_InputtingNonEmptyString_WithTrailingSpaces_ReturnsStringWithSpacesRemoved)
  {
    std::string input("   Test  ");

    Assert::AreEqual("   Test", rtrim_copy(input).c_str());
    Assert::AreEqual("   Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RTrimCopy_InputtingWhitespace_ReturnsEmptyString)
  {
    std::string input("   ");

    Assert::IsTrue(rtrim_copy(input).empty());
    Assert::AreEqual("   ", input.c_str());
  }

#pragma endregion

#pragma region Trim Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingEmptyString_DoesNothing)
  {
    std::string input;
    trim(input);

    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingNonEmptyString_WithNoLeadingOrTrailingSpaces_DoesNothing)
  {
    std::string input("Test");
    trim(input);

    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingNonEmptyString_WithLeadingSpaces_RemovesSpaces)
  {
    std::string input("   Test");
    trim(input);

    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingNonEmptyString_WithTrailingSpaces_RemovesSpaces)
  {
    std::string input("Test  ");
    trim(input);

    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingNonEmptyString_WithLeadingAndTrailingSpaces_RemovesSpaces)
  {
    std::string input("   Test  ");
    trim(input);

    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Trim_InputtingWhitespace_SetsStringToEmptyString)
  {
    std::string input("   ");
    trim(input);

    Assert::IsTrue(input.empty());
  }

#pragma endregion

#pragma region Trim Copy Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingEmptyString_ReturnsEmptyString)
  {
    std::string input;

    Assert::IsTrue(trim_copy(input).empty());
    Assert::IsTrue(input.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingNonEmptyString_WithNoLeadingOrTrailingSpaces_ReturnsInputString)
  {
    std::string input("Test");

    Assert::AreEqual("Test", trim_copy(input).c_str());
    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingNonEmptyString_WithLeadingSpaces_ReturnsStringWithSpacesRemoved)
  {
    std::string input("   Test");

    Assert::AreEqual("Test", trim_copy(input).c_str());
    Assert::AreEqual("   Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingNonEmptyString_WithTrailingSpaces_ReturnsStringWithSpacesRemoved)
  {
    std::string input("Test  ");

    Assert::AreEqual("Test", trim_copy(input).c_str());
    Assert::AreEqual("Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingNonEmptyString_WithLeadingAndTrailingSpaces_ReturnsStringWithSpacesRemoved)
  {
    std::string input("   Test  ");

    Assert::AreEqual("Test", trim_copy(input).c_str());
    Assert::AreEqual("   Test  ", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TrimCopy_InputtingWhitespace_ReturnsEmptyString)
  {
    std::string input("   ");

    Assert::IsTrue(trim_copy(input).empty());
    Assert::AreEqual("   ", input.c_str());
  }

#pragma endregion

#pragma region Replace All Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_InputtingEmptyText_ReturnsEmptyText)
  {
    std::string input;
    replaceAll(input, "From", "To");

    Assert::AreEqual("", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_InputtingEmptyFromText_ReturnsOriginalString)
  {
    std::string input("Test");
    replaceAll(input, "", "To");

    Assert::AreEqual("Test", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_InputtingEmptyToText_ReturnsOriginalStringWithInstancesOfFrom_ReplacedWithEmptyString)
  {
    std::string input("TestFromTest2From");
    replaceAll(input, "From", "");

    Assert::AreEqual("TestTest2", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_FromTextNotFound_ReturnsOriginalString)
  {
    std::string input("TestTest2");
    replaceAll(input, "From", "To");

    Assert::AreEqual("TestTest2", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_SingleInstanceOfFromTextFound_ReturnsOriginalStringWithFrom_ReplacedFromToString)
  {
    std::string input("TestFromTest2");
    replaceAll(input, "From", "To");

    Assert::AreEqual("TestToTest2", input.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ReplaceAll_MultipleInstancesOfFromTextFound_ReturnsOriginalStringWithAllInstancesOfFrom_ReplacedFromToString)
  {
    std::string input("TestFromTeFromstFrom2");
    replaceAll(input, "From", "To");

    Assert::AreEqual("TestToTeTostTo2", input.c_str());
  }

#pragma endregion

  };
}