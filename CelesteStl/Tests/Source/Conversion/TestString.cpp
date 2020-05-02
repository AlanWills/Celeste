#include "TestUtils/TestUtils.h"
#include "CelesteStl/Conversion/String.h"

using namespace celstl;


namespace Testcelstl
{
  TEST_UTILS_TEST_CLASS(TestString)

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

  };
}