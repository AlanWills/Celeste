#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/InputSerializers.h"

using namespace Celeste;


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestIncrementModeSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeSerializer_Serialize_InputtingkToggle_SetsOutputStringToToggle)
    {
      std::string output;
      serialize(Input::IncrementMode::kToggle, output);

      Assert::AreEqual("Toggle", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeSerializer_Serialize_InputtingkContinuous_SetsOutputStringToContinuous)
    {
      std::string output;
      serialize(Input::IncrementMode::kContinuous, output);

      Assert::AreEqual("Continuous", output.c_str());
    }

#pragma endregion

    };
  }
}