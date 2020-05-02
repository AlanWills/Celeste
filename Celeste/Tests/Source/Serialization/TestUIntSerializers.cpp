#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste::Serialization
{
  CELESTE_TEST_CLASS(TestUIntSerializer)

#pragma region Serialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntSerializer_Serialize_SetsOutputStringToCorrectString)
  {
    std::string output;
    serialize(53, output);

    Assert::AreEqual("53", output.c_str());

    output.append("Wubba");
    serialize(1234567890, output);

    Assert::AreEqual("1234567890", output.c_str());
  }

#pragma endregion

  };
}