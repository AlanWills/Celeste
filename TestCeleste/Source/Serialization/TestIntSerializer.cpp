#include "UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestIntSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntSerializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize(53, output);

      Assert::AreEqual("53", output.c_str());

      output.append("Wubba");
      serialize(-2311, output);

      Assert::AreEqual("-2311", output.c_str());
    }

#pragma endregion

    };
  }
}