#include "Deserialization/ViewportDeserializers.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestProjectionModeDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingOrthographic_ReturnsTrue)
    {
      ProjectionMode mode = ProjectionMode::kPerspective;

      Assert::IsTrue(deserialize("Orthographic", mode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingOrthographic_SetsOutputTokOrthographic)
    {
      ProjectionMode mode = ProjectionMode::kPerspective;
      deserialize("Orthographic", mode);

      Assert::IsTrue(mode == ProjectionMode::kOrthographic);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingPerspective_ReturnsTrue)
    {
      ProjectionMode mode = ProjectionMode::kOrthographic;

      Assert::IsTrue(deserialize("Perspective", mode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingPerspective_SetsOutputTokGUI)
    {
      ProjectionMode mode = ProjectionMode::kOrthographic;
      deserialize("Perspective", mode);

      Assert::IsTrue(mode == ProjectionMode::kPerspective);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      ProjectionMode mode = ProjectionMode::kOrthographic;

      Assert::IsFalse(deserialize("", mode));
      Assert::IsFalse(deserialize("adhiasd", mode));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProjectionModeDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      ProjectionMode mode = ProjectionMode::kOrthographic;
      deserialize("", mode);

      Assert::IsTrue(mode == ProjectionMode::kOrthographic);

      deserialize("wjdankjds", mode);

      Assert::IsTrue(mode == ProjectionMode::kOrthographic);
    }

#pragma endregion

    };
  }
}