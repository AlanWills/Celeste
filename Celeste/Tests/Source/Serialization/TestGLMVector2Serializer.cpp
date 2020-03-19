#include "UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/MathsSerializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestGLMVector2Serializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2Serializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize<const glm::vec2&>(glm::vec2(100, -213), output);

      Assert::AreEqual(std::to_string(100.0f) + "," + std::to_string(-213.0f), output);

      output.append("Wubba");
      serialize<const glm::vec2&>(glm::vec2(123.456, 0), output);

      Assert::AreEqual(std::to_string(123.456f) + "," + std::to_string(0.0f), output);
    }

#pragma endregion

    };
  }
}