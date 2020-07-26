#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/InputSerializers.h"
#include "UI/LayoutEnums.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestHorizontalAlignmentSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentSerializer_Serialize_InputtingkLeft_SetsOutputStringToLeft)
    {
      std::string output;
      serialize(HorizontalAlignment::kLeft, output);

      Assert::AreEqual("Left", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentSerializer_Serialize_InputtingkCentre_SetsOutputStringToCentre)
    {
      std::string output;
      serialize(HorizontalAlignment::kCentre, output);

      Assert::AreEqual("Centre", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentSerializer_Serialize_InputtingkRight_SetsOutputStringToRight)
    {
      std::string output;
      serialize(HorizontalAlignment::kRight, output);

      Assert::AreEqual("Right", output.c_str());
    }

#pragma endregion

    };
  }
}