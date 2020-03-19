#include "UtilityHeaders/UnitTestHeaders.h"
#include "UID/StringId.h"

using namespace Celeste;


namespace TestCeleste
{		
  CELESTE_TEST_CLASS(TestStringId)
		
#pragma region Intern String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_InternString_InputtingEmptyString_ReturnsZero)
    {
      Assert::AreEqual(static_cast<StringId>(0), internString(""));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_InternString_SameStringsEqualId)
		{
      std::string string("Test String");

      StringId firstStringId = internString(string);
      StringId secondStringId = internString(string);

      Assert::AreEqual(firstStringId, secondStringId);
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_InternString_DifferentStringsNotEqualId)
    {
      std::string firstString("First String");
      std::string secondString("Second String");

      StringId firstStringId = internString(firstString);
      StringId secondStringId = internString(secondString);

      Assert::AreNotEqual(firstStringId, secondStringId);
    }

#pragma endregion

#pragma region Deintern String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_DeinternStringThatExistsInMap_ReturnsCorrectString)
    {
      std::string firstString("First String");
      std::string secondString("Second String");

      StringId firstStringId = internString(firstString);
      StringId secondStringId = internString(secondString);

      Assert::AreEqual(firstString, deinternString(firstStringId));
      Assert::AreEqual(secondString, deinternString(secondStringId));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_DeinternStringThatDoesNotExistInMap_ReturnsZero)
    {
      Assert::AreEqual("", deinternString(111919).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_DeinternString_ReturnsZero)
    {
      // Add the empty string to the map so that it is there
      Assert::AreEqual(static_cast<StringId>(0), internString(""));
      Assert::AreEqual("", deinternString(static_cast<StringId>(0)).c_str());
    }

#pragma endregion

#pragma region String Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_LHSEqualityWithString_ShouldReturnTrue)
    {
      StringId id = internString("Test");

      Assert::IsTrue(id == std::string("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_RHSEqualityWithString_ShouldReturnTrue)
    {
      StringId id = internString("Test");

      Assert::IsTrue(std::string("Test") == id);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_LHSEqualityWithString_ShouldReturnFalse)
    {
      StringId id = internString("Test");

      Assert::IsFalse(id == std::string("Test2"));
      Assert::IsFalse(id == std::string(""));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_RHSEqualityWithString_ShouldReturnFalse)
    {
      StringId id = internString("Test");

      Assert::IsFalse(std::string("Test2") == id);
      Assert::IsFalse(std::string("") == id);
    }

#pragma endregion

#pragma region String Inequality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_LHSInequalityWithString_ShouldReturnTrue)
    {
      StringId id = internString("Test");

      Assert::IsTrue(id != std::string("Test2"));
      Assert::IsTrue(id != std::string(""));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_RHSInequalityWithString_ShouldReturnTrue)
    {
      StringId id = internString("Test");

      Assert::IsTrue(std::string("Test2") != id);
      Assert::IsTrue(std::string("") != id);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_LHSInequalityWithString_ShouldReturnFalse)
    {
      StringId id = internString("Test");

      Assert::IsFalse(id != std::string("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringId_RHSInequalityWithString_ShouldReturnFalse)
    {
      StringId id = internString("Test");

      Assert::IsFalse(std::string("Test") != id);
    }

#pragma endregion

	};
}