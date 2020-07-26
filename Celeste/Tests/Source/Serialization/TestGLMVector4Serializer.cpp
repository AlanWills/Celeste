#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/MathsSerializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestGLMVector4Serializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4Serializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize<const glm::vec4&>(glm::vec4(100, -213, 5.2f, 0), output);

      Assert::AreEqual(std::to_string(100.0f) + "," + std::to_string(-213.0f) + "," + std::to_string(5.2f) + "," + std::to_string(0.0f), output);

      output.append("Wubba");
      serialize<const glm::vec4&>(glm::vec4(123.456, 0, -1, 666), output);

      Assert::AreEqual(std::to_string(123.456f) + "," + std::to_string(0.0f) + "," + std::to_string(-1.0f) + "," + std::to_string(666.0f), output);
    }

#pragma endregion

    };
  }
}