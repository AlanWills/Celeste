#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestIntDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDeserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      int output;

      Assert::IsFalse(deserialize("WubbaLubbaDubDub", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDeserializer_Deserialize_InputtingInvalidText_DoesNotChangeOutput)
    {
      int output = 0;
      deserialize("WubbaLubbaDubDub", output);

      Assert::AreEqual(0, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDeserializer_Deserialize_InputtingValidText_ReturnsTrue)
    {
      int output;

      Assert::IsTrue(deserialize("5", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDeserializer_Deserialize_InputtingValidText_SetsOutputToCorrectValue)
    {
      int output = 0;
      deserialize("5", output);

      Assert::AreEqual(5, output);
    }

#pragma endregion

    };
  }
}