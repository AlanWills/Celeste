#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestGLMVector2Deserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingSingleNumber_SetsXComponentToNumber_AndReturnsTrue)
    {
      glm::vec2 value;

      Assert::IsTrue(deserialize("56", value));
      Assert::AreEqual(glm::vec2(56, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingAttributeWithTwoNumbers_SetsXYComponentsToRespectiveNumbers_AndReturnsTrue)
    {
      glm::vec2 value;

      Assert::IsTrue(deserialize("56, 63", value));
      Assert::AreEqual(glm::vec2(56, 63), value);
      Assert::IsTrue(deserialize("12,0.43", value));
      Assert::AreEqual(glm::vec2(12, 0.43), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingSinglePercentage_SetsXComponentsToCorrectViewportPercentage_AndReturnsTrue)
    {
      glm::vec2 value;

      Assert::IsTrue(deserialize("5.6%", value));
      Assert::AreEqual(glm::vec2(5.6f * getViewportDimensions().x, 0), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingTwoPercentages_SetsXAndYComponentsToCorrectViewportPercentage_AndReturnsTrue)
    {
      const glm::vec2& viewportDimensions = getViewportDimensions();
      glm::vec2 value;

      Assert::IsTrue(deserialize("5.6%, 6.3%", value));
      Assert::AreEqual(glm::vec2(5.6f * viewportDimensions.x, 6.3f * viewportDimensions.y), value);
      Assert::IsTrue(deserialize("12%, 0.43%", value));
      Assert::AreEqual(glm::vec2(12 * viewportDimensions.x, 0.43f * viewportDimensions.y), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingNumbersButNoDelimiters_ReturnsFalse)
    {
      glm::vec2 value;

      Assert::IsFalse(deserialize("56 12", value));
      Assert::AreEqual(glm::vec2(), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingPercentageForJustOneNumber_SetsNumbersToCorrectRelativeAndAbsoluteValue)
    {
      glm::vec2 value;

      Assert::IsTrue(deserialize("56%, 12", value));
      Assert::AreEqual(glm::vec2(56 * getViewportDimensions().x, 12), value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Deserializer_Deserialize_InputtingInvalidText_ReturnsFalse)
    {
      glm::vec2 value;

      Assert::IsFalse(deserialize("awas,11ddd,00.111.121", value));
      Assert::AreEqual(glm::vec2(), value);
    }

#pragma endregion

    };
  }
}