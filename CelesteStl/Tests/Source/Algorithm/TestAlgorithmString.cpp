#include "TestUtils/TestUtils.h"
#include "CelesteStl/Algorithm/String.h"


namespace Testcelstl
{
  BASE_TEST_CLASS(TestAlgorithmString)

#pragma region Replace Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingEmptyString_DoesNothing)
  {
    std::string target;
    celstl::replace(target, 'x', 'y');

    Assert::IsTrue(target.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingNonEmptyString_NoTargetCharacterInString_DoesNothing)
  {
    std::string target("WubbaLubbaDubDub");
    
    Assert::AreEqual(target.npos, target.find('x'));

    celstl::replace(target, 'x', 'y');

    Assert::AreEqual("WubbaLubbaDubDub", target.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingNonEmptyString_TargetCharacterSameAsReplaceCharacter_DoesNothing)
  {
    std::string target("WubbaLubbaDubDub");
    
    Assert::AreNotEqual(target.npos, target.find('L'));

    celstl::replace(target, 'L', 'L');

    Assert::AreEqual("WubbaLubbaDubDub", target.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingNonEmptyString_SingleMatchingCharacter_ReplacesCharacterCorrectly)
  {
    std::string target("WubbaLubbaDubDub");
    
    Assert::AreNotEqual(target.npos, target.find('W'));

    celstl::replace(target, 'W', 'D');

    Assert::AreEqual("DubbaLubbaDubDub", target.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingNonEmptyString_MultipleMatchingCharacters_ReplacesCharactersCorrectly)
  {
    std::string target("WubbaLubbaDubDub");
    
    Assert::AreNotEqual(target.npos, target.find('D'));

    celstl::replace(target, 'D', 'L');

    Assert::AreEqual("WubbaLubbaLubLub", target.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AlgorithmString_ReplaceInputtingNonEmptyString_InputStringAllMatchingCharacters_ConvertsEntireStringToReplaceCharacters)
  {
    std::string target("wwwwwwww");
    
    Assert::AreNotEqual(target.npos, target.find('w'));

    celstl::replace(target, 'w', 'a');

    Assert::AreEqual("aaaaaaaa", target.c_str());
  }

#pragma endregion
  
  };
}