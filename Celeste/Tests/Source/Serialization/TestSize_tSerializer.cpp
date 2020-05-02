#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestSize_tSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tSerializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize(53, output);

      Assert::AreEqual("53", output.c_str());

      output.append("Wubba");
      serialize(213131321, output);

      Assert::AreEqual("213131321", output.c_str());
    }

#pragma endregion

    };
  }
}