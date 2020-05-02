#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/MathsDeserializers.h"
#include "Maths/MathsEnums.h"

using namespace Celeste;
using namespace Celeste::Maths;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestSpaceDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingWorld_ReturnsTrue)
    {
      Space space = Space::kLocal;

      Assert::IsTrue(deserialize("World", space));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingWorld_SetsOutputTokWorld)
    {
      Space space = Space::kLocal;
      deserialize("World", space);

      Assert::IsTrue(space == Space::kWorld);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingLocal_ReturnsTrue)
    {
      Space space = Space::kWorld;

      Assert::IsTrue(deserialize("Local", space));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingLocal_SetsOutputTokGUI)
    {
      Space space = Space::kWorld;
      deserialize("Local", space);

      Assert::IsTrue(space == Space::kLocal);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingInvalidText_ReturnsFalse)
    {
      Space space = Space::kWorld;

      Assert::IsFalse(deserialize("", space));
      Assert::IsFalse(deserialize("adhiasd", space));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDeserializer_InputtingInvalidText_DoesNotChangeOutput)
    {
      Space space = Space::kWorld;
      deserialize("", space);

      Assert::IsTrue(space == Space::kWorld);

      deserialize("wjdankjds", space);

      Assert::IsTrue(space == Space::kWorld);
    }

#pragma endregion

    };
  }
}