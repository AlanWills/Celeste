#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Input/Utils/GlfwKeyConverter.h"
#include "UtilityHeaders/GLHeaders.h"

using namespace Celeste::Input;


namespace TestCeleste
{
  namespace Input
  {
    CELESTE_TEST_CLASS(TestGlfwKeyConverter)

#pragma region Get Glfw Key From Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetGlfwKeyFromName_InputtingEmptyString_ReturnsGlfwKeyUnknown)
    {
      Assert::AreEqual(GLFW_KEY_UNKNOWN, GlfwKeyConverter::getGlfwKeyFromName(""));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetGlfwKeyFromName_InputtingSingleCharString_WithMatchingGlfwKey_ReturnsCorrectKey)
    {
      Assert::AreEqual(GLFW_KEY_C, GlfwKeyConverter::getGlfwKeyFromName(std::string("c")));
      Assert::AreEqual(GLFW_KEY_C, GlfwKeyConverter::getGlfwKeyFromName(std::string("C")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetGlfwKeyFromName_InputtingSingleCharString_WithoutMatchingGlfwKey_ReturnsGlfwKeyUnknown)
    {
      Assert::AreEqual(GLFW_KEY_UNKNOWN, GlfwKeyConverter::getGlfwKeyFromName(std::string("%")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetGlfwKeyFromName_InputtingMultiCharString_WithMatchingGlfwKey_ReturnsCorrectKey)
    {
      Assert::AreEqual(GLFW_KEY_SPACE, GlfwKeyConverter::getGlfwKeyFromName(std::string("space")));
      Assert::AreEqual(GLFW_KEY_LEFT_CONTROL, GlfwKeyConverter::getGlfwKeyFromName(std::string("left control")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetGlfwKeyFromName_InputtingMultiCharString_WithoutMatchingGlfwKey_ReturnsGlfwKeyUnknown)
    {
      Assert::AreEqual(GLFW_KEY_UNKNOWN, GlfwKeyConverter::getGlfwKeyFromName(std::string("wubbalubbadubdub")));
    }

#pragma endregion

#pragma region Get Name From Glfw Key Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetNameFromGlfwKey_InputtingSingleCharKey_ReturnsCorrectName)
    {
      Assert::AreEqual("F", GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_F).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetNameFromGlfwKey_InputtingNumber_ReturnsCorrectName)
    {
      Assert::AreEqual("1", GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_1).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetNameFromGlfwKey_InputtingModifier_ReturnsCorrectName)
    {
      Assert::AreEqual("left control", GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_LEFT_CONTROL).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetNameFromGlfwKey_InputtingGlfwKeyUnknown_ReturnsEmptyString)
    {
      Assert::IsTrue(GlfwKeyConverter::getNameFromGlfwKey(GLFW_KEY_UNKNOWN).empty());
    }

#pragma endregion

    };
  }
}