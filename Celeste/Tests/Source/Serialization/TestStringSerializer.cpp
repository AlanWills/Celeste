#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"
#include "Utils/ToString.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestStringSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringSerializer_Serialize_InputtingEmptyString_SetsOutputStringToEmptyString)
    {
      std::string output;
      serialize<const std::string&>("", output);

      Assert::IsTrue(output.empty());

      output.append("Wubba");
      serialize<const std::string&>("", output);

      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringSerializer_Serialize_InputtingNonEmptyString_SetsOutputToCorrectString)
    {
      std::string output;
      serialize<const std::string&>("Lubba", output);

      Assert::AreEqual("Lubba", output.c_str());

      output.append("Wubba");
      serialize<const std::string&>("Lubba", output);

      Assert::AreEqual("Lubba", output.c_str());
    }

#pragma endregion

    };
  }
}