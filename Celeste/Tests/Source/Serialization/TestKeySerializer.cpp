#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/InputSerializers.h"


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestKeySerializer)

#pragma region Serialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingLetterKey_SetsOutputToCorrectValue)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_A), output);

      Assert::AreEqual("A", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingLetterKey_ClearsInputtedOutputText)
    {
      std::string output("Test");
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_A), output);

      Assert::AreEqual("A", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingNumberKey_SetsOutputToCorrectValue)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_1), output);

      Assert::AreEqual("1", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingNumberKey_ClearsInputtedOutputText)
    {
      std::string output("Test");
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_1), output);

      Assert::AreEqual("1", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingModifierKey_SetsOutputToCorrectValue)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_LEFT_CONTROL), output);

      Assert::AreEqual("left control", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingModifierKey_ClearsInputtedOutputText)
    {
      std::string output("Test");
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_LEFT_CONTROL), output);

      Assert::AreEqual("left control", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingUnknownKey_SetsOutputToEmptyString)
    {
      std::string output;
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_UNKNOWN), output);

      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeySerializer_Serialize_InputtingUnknownKey_ClearsInputtedOutputText)
    {
      std::string output("Test");
      Celeste::serialize(Celeste::Input::Key(GLFW_KEY_UNKNOWN), output);

      Assert::IsTrue(output.empty());
    }

#pragma endregion

    };
  }
}