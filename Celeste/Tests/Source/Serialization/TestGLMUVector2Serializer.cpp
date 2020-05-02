#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/MathsSerializers.h"


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestGLMUVector2Serializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector2Serializer_Serialize_SetsOutputStringToCorrectString)
    {
      std::string output;
      Celeste::serialize<const glm::uvec2&>(glm::uvec2(100, 213), output);

      Assert::AreEqual(std::to_string(100) + "," + std::to_string(213), output);

      output.append("Wubba");
      Celeste::serialize<const glm::uvec2&>(glm::uvec2(123, 0), output);

      Assert::AreEqual(std::to_string(123) + "," + std::to_string(0), output);
    }

#pragma endregion

    };
  }
}