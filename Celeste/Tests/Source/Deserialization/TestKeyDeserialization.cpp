#include "Deserialization/InputDeserializers.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  namespace Deserialization
  {
    CELESTE_TEST_CLASS(TestKeyDeserializer)

#pragma region Deserialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDeserializer_InputtingLowerCaseLetter_ReturnsCorrectValue)
    {
      Key key;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);

      Celeste::deserialize("a", key);

      Assert::AreEqual(GLFW_KEY_A, key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDeserializer_InputtingUpperCaseLetter_ReturnsCorrectValue)
    {
      Key key;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);

      Celeste::deserialize("A", key);

      Assert::AreEqual(GLFW_KEY_A, key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDeserializer_InputtingNumber_ReturnsCorrectValue)
    {
      Key key;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);

      Celeste::deserialize("1", key);

      Assert::AreEqual(GLFW_KEY_1, key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDeserializer_InputtingModifier_ReturnsCorrectValue)
    {
      Key key;

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);

      Celeste::deserialize("left control", key);

      Assert::AreEqual(GLFW_KEY_LEFT_CONTROL, key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDeserializer_InputtingInvalidText_ReturnsGLFW_KEY_UNKNOWN)
    {
      Key key(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, key.m_key);

      Celeste::deserialize("wubbalubbadubdub", key);

      Assert::AreEqual(GLFW_KEY_UNKNOWN, key.m_key);
    }

#pragma endregion

    };
  }
}