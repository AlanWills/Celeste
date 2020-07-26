#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestBoolDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      bool output;

      Assert::IsFalse(deserialize("WubbaLubbaDubDub", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingInvalidText_DoesNotChangeOutput)
    {
      bool output = false;
      deserialize("WubbaLubbaDubDub", output);

      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingtrueText_ReturnsTrue)
    {
      bool output;

      Assert::IsTrue(deserialize("true", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingtrueText_SetsOutputToTrue)
    {
      bool output = false;
      deserialize("true", output);

      Assert::IsTrue(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingTrueText_ReturnsTrue)
    {
      bool output;

      Assert::IsTrue(deserialize("True", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingTrueText_SetsOutputToTrue)
    {
      bool output = false;
      deserialize("True", output);

      Assert::IsTrue(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingfalseText_ReturnsTrue)
    {
      bool output;

      Assert::IsTrue(deserialize("false", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingfalseText_SetsOutputToFalse)
    {
      bool output = true;
      deserialize("false", output);

      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDeserializer_Deserialize_InputtingFalseText_ReturnsTrue)
    {
      bool output;

      Assert::IsTrue(deserialize("False", output));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDeserializer_Deserialize_InputtingFalseText_SetsOutputToFalse)
    {
      bool output = true;
      deserialize("False", output);

      Assert::IsFalse(output);
    }

#pragma endregion

    };
  }
}