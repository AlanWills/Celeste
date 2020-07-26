#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/MathsSerializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestGLMVector3Serializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3Serializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      serialize<const glm::vec3&>(glm::vec3(100, -213, 5.2f), output);

      Assert::AreEqual(std::to_string(100.0f) + "," + std::to_string(-213.0f) + "," + std::to_string(5.2f), output);

      output.append("Wubba");
      serialize<const glm::vec3&>(glm::vec3(123.456, 0, -1), output);

      Assert::AreEqual(std::to_string(123.456f) + "," + std::to_string(0.0f) + "," + std::to_string(-1.0f), output);
    }

#pragma endregion

    };
  }
}