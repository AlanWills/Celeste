#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestSize_tDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDeserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      size_t output;

      Assert::IsFalse(deserialize("WubbaLubbaDubDub", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDeserializer_Deserialize_InputtingInvalidText_DoesNotChangeOutput)
    {
      size_t output = 0;
      deserialize("WubbaLubbaDubDub", output);

      Assert::AreEqual(static_cast<size_t>(0), output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDeserializer_Deserialize_InputtingValidText_ReturnsTrue)
    {
      size_t output;

      Assert::IsTrue(deserialize("5", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDeserializer_Deserialize_InputtingValidText_SetsOutputToCorrectValue)
    {
      size_t output = 0;
      deserialize("5", output);

      Assert::AreEqual(static_cast<size_t>(5), output);
    }

#pragma endregion

    };
  }
}