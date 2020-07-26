#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestGLMVector3Deserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingEmptyString_DoesNotChangeValue_AndReturnsFalse)
  {
    glm::vec3 value(0);

    Assert::IsFalse(deserialize("", value));
    Assert::AreEqual(glm::vec3(0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentToNumber_AndReturnsTrue)
  {
    glm::vec3 value(0);

    Assert::IsTrue(deserialize("56", value));
    Assert::AreEqual(glm::vec3(56, 0, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingTwoNumbers_SetsXYComponentsToFirstNumberAndSecondNumber_AndReturnsTrue)
  {
    glm::vec3 value(0);

    Assert::IsTrue(deserialize("56, 63", value));
    Assert::AreEqual(glm::vec3(56, 63, 0), value);
    Assert::IsTrue(deserialize("12,0.43", value));
    Assert::AreEqual(glm::vec3(12, 0.43, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingThreeNumbers_SetsXYZComponentsToFirstSecondThirdNumbers_AndReturnsTrue)
  {
    glm::vec3 value(0);

    Assert::IsTrue(deserialize("56, 63, 100", value));
    Assert::AreEqual(glm::vec3(56, 63, 100), value);
    Assert::IsTrue(deserialize("12,0.43,0", value));
    Assert::AreEqual(glm::vec3(12, 0.43, 0), value);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
  {
    glm::vec3 value(0);

    Assert::IsFalse(deserialize("awas,11ddd,00.111.121", value));
    Assert::AreEqual(glm::vec3(0), value);
  }

#pragma endregion

  };
}