#include "UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/InputSerializers.h"
#include "Utils/ToString.h"
#include "UI/LayoutEnums.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestVerticalAlignmentSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentSerializer_Serialize_InputtingkTop_SetsOutputStringToTop)
    {
      std::string output;
      serialize(VerticalAlignment::kTop, output);

      Assert::AreEqual("Top", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentSerializer_Serialize_InputtingkCentre_SetsOutputStringToCentre)
    {
      std::string output;
      serialize(VerticalAlignment::kCentre, output);

      Assert::AreEqual("Centre", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentSerializer_Serialize_InputtingkBottom_SetsOutputStringToBottom)
    {
      std::string output;
      serialize(VerticalAlignment::kBottom, output);

      Assert::AreEqual("Bottom", output.c_str());
    }

#pragma endregion

    };
  }
}