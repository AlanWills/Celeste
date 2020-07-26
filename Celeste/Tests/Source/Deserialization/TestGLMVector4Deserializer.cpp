#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestGLMVector4Deserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingEmptyString_DoesNotChangeValue_AndReturnsFalse)
  {
    glm::vec4 value(0);

    Assert::IsFalse(deserialize("", value));
    Assert::AreEqual(glm::vec4(0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentsToNumber_AndReturnsTrue)
  {
    glm::vec4 value(0);

    Assert::IsTrue(deserialize("56", value));
    Assert::AreEqual(glm::vec4(56, 0, 0, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingTwoNumbers_SetsXYComponentsToFirstAndSecondNumbers_AndReturnsTrue)
  {
    glm::vec4 value(0);

    Assert::IsTrue(deserialize("56, 63", value));
    Assert::AreEqual(glm::vec4(56, 63, 0, 0), value);
    Assert::IsTrue(deserialize("12,0.43", value));
    Assert::AreEqual(glm::vec4(12, 0.43f, 0, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingThreeNumbers_SetsXYZComponentsToFirstSecondAndThirdNumbers_AndReturnsTrue)
  {
    glm::vec4 value(0);

    Assert::IsTrue(deserialize("56, 63, 100", value));
    Assert::AreEqual(glm::vec4(56, 63, 100, 0), value);
    Assert::IsTrue(deserialize("12,0.43,0", value));
    Assert::AreEqual(glm::vec4(12, 0.43, 0, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingFourNumbers_SetsXYZWComponentsToFirstSecondThirdAndFourthNumbers_AndReturnsTrue)
  {
    glm::vec4 value(0);

    Assert::IsTrue(deserialize("56, 63, 100, 0.1", value));
    Assert::AreEqual(glm::vec4(56, 63, 100, 0.1f), value);
    Assert::IsTrue(deserialize("12,0.43,0,-2", value));
    Assert::AreEqual(glm::vec4(12, 0.43, 0, -2), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
  {
    glm::vec4 value(0);

    Assert::IsFalse(deserialize("awas,11ddd,00.111.121,-asdasd", value));
    Assert::AreEqual(glm::vec4(0), value);
  }

#pragma endregion

  };
}