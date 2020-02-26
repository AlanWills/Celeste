#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestGLMVector3Deserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingEmptyString_DoesNotChangeValue_AndReturnsFalse)
    {
      glm::vec3 value;

      Assert::IsFalse(deserialize("", value));
      Assert::AreEqual(glm::vec3(), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentToNumber_AndReturnsTrue)
    {
      glm::vec3 value;

      Assert::IsTrue(deserialize("56", value));
      Assert::AreEqual(glm::vec3(56, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingTwoNumbers_SetsXYComponentsToFirstNumberAndSecondNumber_AndReturnsTrue)
    {
      glm::vec3 value;

      Assert::IsTrue(deserialize("56, 63", value));
      Assert::AreEqual(glm::vec3(56, 63, 0), value);
      Assert::IsTrue(deserialize("12,0.43", value));
      Assert::AreEqual(glm::vec3(12, 0.43, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingThreeNumbers_SetsXYZComponentsToFirstSecondThirdNumbers_AndReturnsTrue)
    {
      glm::vec3 value;

      Assert::IsTrue(deserialize("56, 63, 100", value));
      Assert::AreEqual(glm::vec3(56, 63, 100), value);
      Assert::IsTrue(deserialize("12,0.43,0", value));
      Assert::AreEqual(glm::vec3(12, 0.43, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingSinglePercentage_SetsXComponentToCorrectViewportDimensionPercentage_AndReturnsTrue)
    {
      glm::vec3 value;

      Assert::IsTrue(deserialize("56%", value));
      Assert::AreEqual(glm::vec3(56 * getViewportDimensions().x, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingTwoPercentages_SetsXYComponentsToCorrectViewportDimensionPercentage_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec3 value;

      Assert::IsTrue(deserialize("56%, 63%", value));
      Assert::AreEqual(glm::vec3(56 * viewportDimensions.x, 63 * viewportDimensions.y, 0), value);
      Assert::IsTrue(deserialize("12%,0.43%", value));
      Assert::AreEqual(glm::vec3(12 * viewportDimensions.x, 0.43 * viewportDimensions.y, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingThreePercentages_SetsXYZComponentsToCorrectViewportDimensionPerctanges_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec3 value;

      Assert::IsTrue(deserialize("56%, 63%, 100%", value));
      Assert::AreEqual(glm::vec3(56 * viewportDimensions.x, 63 * viewportDimensions.y, 100), value);
      Assert::IsTrue(deserialize("12%,0.43%,0%", value));
      Assert::AreEqual(glm::vec3(12 * viewportDimensions.x, 0.43 * viewportDimensions.y, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingNumbersButNoDelimiters_ReturnsFalse)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec3 value;

      Assert::IsFalse(deserialize("56 63 100", value));
      Assert::AreEqual(glm::vec3(), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingPercentageForJustOneNumber_SetsNumbersToCorrectRelativeAndAbsoluteValues_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec3 value;

      Assert::IsTrue(deserialize("5.6%, 12, 0.1", value));
      Assert::AreEqual(glm::vec3(5.6f * getViewportDimensions().x, 12, 0.1), value);
      Assert::IsTrue(deserialize("6,2%,0.5", value));
      Assert::AreEqual(glm::vec3(6, 2 * getViewportDimensions().y, 0.5), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      glm::vec3 value;

      Assert::IsFalse(deserialize("awas,11ddd,00.111.121", value));
      Assert::AreEqual(glm::vec3(), value);
    }

#pragma endregion

    };
  }
}