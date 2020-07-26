#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/InputSerializers.h"


namespace TestCeleste
{
  namespace Serialization
  {
    CELESTE_TEST_CLASS(TestInputModeSerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeSerializer_Serialize_InputtingkToggle_SetsOutputStringToToggle)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::InputMode::kToggle, output);

      Assert::AreEqual("Toggle", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputModeSerializer_Serialize_InputtingkContinuous_SetsOutputStringToContinuous)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::InputMode::kContinuous, output);

      Assert::AreEqual("Continuous", output.c_str());
    }

#pragma endregion

    };
  }
}