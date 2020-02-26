#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestGLMVector4Deserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingEmptyString_DoesNotChangeValue_AndReturnsFalse)
    {
      glm::vec4 value;

      Assert::IsFalse(deserialize("", value));
      Assert::AreEqual(glm::vec4(), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentsToNumber_AndReturnsTrue)
    {
      glm::vec4 value;

      Assert::IsTrue(deserialize("56", value));
      Assert::AreEqual(glm::vec4(56, 0, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingTwoNumbers_SetsXYComponentsToFirstAndSecondNumbers_AndReturnsTrue)
    {
      glm::vec4 value;

      Assert::IsTrue(deserialize("56, 63", value));
      Assert::AreEqual(glm::vec4(56, 63, 0, 0), value);
      Assert::IsTrue(deserialize("12,0.43", value));
      Assert::AreEqual(glm::vec4(12, 0.43f, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingThreeNumbers_SetsXYZComponentsToFirstSecondAndThirdNumbers_AndReturnsTrue)
    {
      glm::vec4 value;

      Assert::IsTrue(deserialize("56, 63, 100", value));
      Assert::AreEqual(glm::vec4(56, 63, 100, 0), value);
      Assert::IsTrue(deserialize("12,0.43,0", value));
      Assert::AreEqual(glm::vec4(12, 0.43, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingFourNumbers_SetsXYZWComponentsToFirstSecondThirdAndFourthNumbers_AndReturnsTrue)
    {
      glm::vec4 value;

      Assert::IsTrue(deserialize("56, 63, 100, 0.1", value));
      Assert::AreEqual(glm::vec4(56, 63, 100, 0.1f), value);
      Assert::IsTrue(deserialize("12,0.43,0,-2", value));
      Assert::AreEqual(glm::vec4(12, 0.43, 0, -2), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingSinglePercentage_SetsXComponentsToCorrectRelativeNumber_AndReturnsTrue)
    {
      glm::vec4 value;

      Assert::IsTrue(deserialize("5.6%", value));
      Assert::AreEqual(glm::vec4(5.6f * getViewportDimensions().x, 0, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingTwoPercentages_SetsXYComponentsToCorrectRelativeNumbers_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec4 value;

      Assert::IsTrue(deserialize("5.6%, 6.3%", value));
      Assert::AreEqual(glm::vec4(5.6f * viewportDimensions.x, 6.3f * viewportDimensions.y, 0, 0), value);
      Assert::IsTrue(deserialize("12%,0.43%", value));
      Assert::AreEqual(glm::vec4(12 * viewportDimensions.x, 0.43f * viewportDimensions.y, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingThreePercentages_SetsXYZComponentsToCorrectRelativeNumbers_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec4 value;

      Assert::IsTrue(deserialize("5.6%, 6.3%, 100%", value));
      Assert::AreEqual(glm::vec4(5.6f * viewportDimensions.x, 6.3f * viewportDimensions.y, 100, 0), value);
      Assert::IsTrue(deserialize("12%,0.43%,0%", value));
      Assert::AreEqual(glm::vec4(12 * viewportDimensions.x, 0.43f * viewportDimensions.y, 0, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingFourPercentages_SetsXYZWComponentsToCorrectRelativeNumbers_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec4 value;

      Assert::IsTrue(deserialize("56%, 63%, 100%, -0.1%", value));
      Assert::AreEqual(glm::vec4(56 * viewportDimensions.x, 63 * viewportDimensions.y, 100, -0.1), value);
      Assert::IsTrue(deserialize("12%,0.43%,0%,-6%", value));
      Assert::AreEqual(glm::vec4(12 * viewportDimensions.x, 0.43 * viewportDimensions.y, 0, -6), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingNumbersButNoDelimiters_ReturnsFalse)
    {
      glm::vec4 value;

      Assert::IsFalse(deserialize("5.6 6.3 100 -0.1", value));
      Assert::AreEqual(glm::vec4(), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingPercentageForJustOneNumber_SetsNumbersToCorrectAbsoluteAndRelativeValues_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec4 value;

      Assert::IsTrue(deserialize("56%, 12, 0.1, -2", value));
      Assert::AreEqual(glm::vec4(56 * viewportDimensions.x, 12, 0.1, -2), value);
      Assert::IsTrue(deserialize("6,2%,0.5,-10", value));
      Assert::AreEqual(glm::vec4(6, 2 * viewportDimensions.y, 0.5, -10), value);
      Assert::IsTrue(deserialize("6,0,0.5%,-10", value));
      Assert::AreEqual(glm::vec4(6, 0, 0.5, -10), value);
      Assert::IsTrue(deserialize("6,0,0.5,-10%", value));
      Assert::AreEqual(glm::vec4(6, 0, 0.5, -10), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      glm::vec4 value;

      Assert::IsFalse(deserialize("awas,11ddd,00.111.121,-asdasd", value));
      Assert::AreEqual(glm::vec4(), value);
    }

#pragma endregion

    };
  }
}