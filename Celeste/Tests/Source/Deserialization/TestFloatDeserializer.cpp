#include "Deserialization/Deserializers.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestFloatDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      float output;

      Assert::IsFalse(deserialize("WubbaLubbaDubDub", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingInvalidText_DoesNotChangeOutput)
    {
      float output = 0;
      deserialize("WubbaLubbaDubDub", output);

      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingValidText_ReturnsTrue)
    {
      float output;

      Assert::IsTrue(deserialize("5.25", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingValidText_SetsOutputToCorrectValue)
    {
      float output = 0;
      deserialize("5.25", output);

      Assert::AreEqual(5.25f, output);
    }

#pragma endregion

  };
}
}