#include "Deserialization/MathsDeserializers.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestGLMUVector2Deserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMUVector2Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentToNumber_AndReturnsTrue)
  {
    glm::uvec2 value;

    Assert::IsTrue(deserialize("56", value));
    Assert::AreEqual(glm::uvec2(56, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMUVector2Deserializer_Deserialize_InputtingAttributeWithTwoNumbers_SetsXYComponentsToRespectiveNumbers_AndReturnsTrue)
  {
    glm::uvec2 value;

    Assert::IsTrue(deserialize("56, 63", value));
    Assert::AreEqual(glm::uvec2(56, 63), value);
    Assert::IsTrue(deserialize("12,43", value));
    Assert::AreEqual(glm::uvec2(12, 43), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMUVector2Deserializer_Deserialize_InputtingNumbersButNoDelimiters_ReturnsFalse)
  {
    glm::uvec2 value;

    Assert::IsFalse(deserialize("56 12", value));
    Assert::AreEqual(glm::uvec2(), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMUVector2Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
  {
    glm::uvec2 value;

    Assert::IsFalse(deserialize("awas,11ddd,00.111.121", value));
    Assert::AreEqual(glm::uvec2(), value);
  }

#pragma endregion

  };
}