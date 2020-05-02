#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestGLMVector2Deserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentToNumber_AndReturnsTrue)
  {
    glm::vec2 value(0);

    Assert::IsTrue(deserialize("56", value));
    Assert::AreEqual(glm::vec2(56, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingAttributeWithTwoNumbers_SetsXYComponentsToRespectiveNumbers_AndReturnsTrue)
  {
    glm::vec2 value(0);

    Assert::IsTrue(deserialize("56, 63", value));
    Assert::AreEqual(glm::vec2(56, 63), value);
    Assert::IsTrue(deserialize("12,0.43", value));
    Assert::AreEqual(glm::vec2(12, 0.43), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingNumbersButNoDelimiters_ReturnsFalse)
  {
    glm::vec2 value(0);

    Assert::IsFalse(deserialize("56 12", value));
    Assert::AreEqual(glm::vec2(0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
  {
    glm::vec2 value(0);

    Assert::IsFalse(deserialize("awas,11ddd,00.111.121", value));
    Assert::AreEqual(glm::vec2(0), value);
  }

#pragma endregion

  };
}