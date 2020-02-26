#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"

using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestUIntDeserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
  {
    unsigned int output;

    Assert::IsFalse(deserialize("WubbaLubbaDubDub", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingInvalidText_DoesNotChangeOutput)
  {
    unsigned int output = 0;
    deserialize("WubbaLubbaDubDub", output);

    Assert::AreEqual(0U, output);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingNegativeNumberText_ReturnsFalse)
  {
    unsigned int output;

    Assert::IsFalse(deserialize("-5", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingValidText_DoesNotChangeOutput)
  {
    unsigned int output = 0;
    deserialize("-5", output);

    Assert::AreEqual(0U, output);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingValidText_ReturnsTrue)
  {
    unsigned int output;

    Assert::IsTrue(deserialize("5", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(UIntDeserializer_Deserialize_InputtingValidText_SetsOutputToCorrectValue)
  {
    unsigned int output = 0;
    deserialize("5", output);

    Assert::AreEqual(5U, output);
  }

#pragma endregion

  };
}