#include "UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestBoolSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolSerializer_Serialize_True_SetsOutputStringTo_true)
    {
      std::string output;
      serialize(true, output);

      Assert::AreEqual("true", output.c_str());

      output.append("Wubba");
      serialize(true, output);

      Assert::AreEqual("true", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolSerializer_Serialize_False_SetsOutputStringTo_false)
    {
      std::string output;
      serialize(false, output);

      Assert::AreEqual("false", output.c_str());

      output.append("Wubba");
      serialize(false, output);

      Assert::AreEqual("false", output.c_str());
    }

#pragma endregion

    };
  }
}