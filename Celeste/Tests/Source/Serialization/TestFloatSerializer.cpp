#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestFloatSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatSerializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize(53.25f, output);

      Assert::AreEqual(std::to_string(53.25), output);

      output.append("Wubba");
      serialize(-2311.0001f, output);

      Assert::AreEqual(std::to_string(-2311.0001f), output);
    }

#pragma endregion

    };
  }
}