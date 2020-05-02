#include "Input/Key.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  namespace Input
  {
    CELESTE_TEST_CLASS(TestKey)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_Constructor_Default_SetsKeyTo_GLFW_KEY_UNKNOWN)
    {
      Key key;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_Constructor_SetsKeyToInputtedValue)
    {
      Key key(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key.m_key);
    }

#pragma endregion

#pragma region To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_ToString_InputtingLetter_ReturnsCorrectString)
    {
      Key key(GLFW_KEY_A);

      Assert::AreEqual("A", to_string(key).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_ToString_InputtingNumber_ReturnsCorrectString)
    {
      Key key(GLFW_KEY_1);

      Assert::AreEqual("1", to_string(key).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_ToString_InputtingModifier_ReturnsCorrectString)
    {
      Key key(GLFW_KEY_LEFT_CONTROL);

      Assert::AreEqual("left control", to_string(key).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Key_ToString_InputtingGLFW_KEY_UNKNOWN_ReturnsEmptyString)
    {
      Key key(GLFW_KEY_UNKNOWN);

      Assert::IsTrue(to_string(key).empty());
    }

#pragma endregion

    };
  }
}