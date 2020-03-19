#include "UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/MathsSerializers.h"
#include "Maths/MathsEnums.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestSpaceSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceSerializer_Serialize_InputtingkWorld_SetsOutputStringToWorld)
    {
      std::string output;
      serialize(Maths::Space::kWorld, output);

      Assert::AreEqual("World", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceSerializer_Serialize_InputtingkLocal_SetsOutputStringToLocal)
    {
      std::string output;
      serialize(Maths::Space::kLocal, output);

      Assert::AreEqual("Local", output.c_str());
    }

#pragma endregion

    };
  }
}