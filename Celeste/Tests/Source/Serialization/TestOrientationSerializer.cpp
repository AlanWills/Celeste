#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"
#include "UI/LayoutEnums.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestOrientationSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationSerializer_Serialize_InputtingkVertical_SetsOutputStringToVertical)
    {
      std::string output;
      serialize(UI::Orientation::kVertical, output);

      Assert::AreEqual("Vertical", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationSerializer_Serialize_InputtingkHorizontal_SetsOutputStringToHorizontal)
    {
      std::string output;
      serialize(UI::Orientation::kHorizontal, output);

      Assert::AreEqual("Horizontal", output.c_str());
    }

#pragma endregion

    };
  }
}