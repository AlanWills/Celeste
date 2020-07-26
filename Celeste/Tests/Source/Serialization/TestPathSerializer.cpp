#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestPathSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PathSerializer_Serialize_InputtingEmptyPath_SetsOutputStringToEmptyString)
    {
      std::string output;
      serialize<const Path&>(Path(""), output);

      Assert::IsTrue(output.empty());

      output.append("Wubba");
      serialize<const Path&>(Path(""), output);

      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PathSerializer_Serialize_InputtingNonEmptyPath_SetsOutputToCorrectString)
    {
      std::string output;
      serialize<const Path&>(Path("Wubba", "Lubba", "DubDub"), output);

      Assert::AreEqual(Path("Wubba", "Lubba", "DubDub").c_str(), output.c_str());

      output.append("Wubba");
      serialize<const Path&>(Path("Ricky", "Ticky", "Tavvy"), output);

      Assert::AreEqual(Path("Ricky", "Ticky", "Tavvy").c_str(), output.c_str());
    }

#pragma endregion

  };
}
}