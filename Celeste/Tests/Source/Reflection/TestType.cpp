#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Objects/MockScriptableObject.h"
#include "Reflection/Type.h"

using namespace Celeste::Reflection;


namespace TestCeleste
{
  class NotNested { };

  namespace Reflection
  {
    // Put this before class declaration otherwise namespace will be different
    class Nested { };

    CELESTE_TEST_CLASS(TestType)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_Constructor_SetsNameToCorrectValue)
    {
      Assert::AreEqual("NotNested", Type<NotNested>().getName().c_str());
      Assert::AreEqual("Nested", Type<Nested>().getName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_Constructor_SetsAssemblyToCorrectValue)
    {
      Assert::AreEqual("TestCeleste", Type<NotNested>().getAssembly().c_str());
      Assert::AreEqual("TestCeleste", Type<Nested>().getAssembly().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_Constructor_SetsNamespaceToCorrectValue)
    {
      Assert::AreEqual("TestCeleste", Type<NotNested>().getNamespace().c_str());
      Assert::AreEqual("TestCeleste::Reflection", Type<Nested>().getNamespace().c_str());
    }

#pragma endregion

#pragma region Primitive and Special Types

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_Int)
    {
      Assert::AreEqual("int", Type<int>().getName().c_str());
      Assert::AreEqual("", Type<int>().getAssembly().c_str());
      Assert::AreEqual("", Type<int>().getNamespace().c_str());
    }

#pragma endregion

#pragma region Is Type In Namespace Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IsTypeInNamespace_InputtingTypeInNamespace_ShouldReturnTrue)
    {
      Assert::IsTrue(is_type_in_namespace<NotNested>("TestCeleste"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IsTypeInNamespace_InputtingTypeInNestedNamespace_ShouldReturnTrue)
    {
      Assert::IsTrue(is_type_in_namespace<Nested>("TestCeleste::Reflection"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IsTypeInNamespace_InputtingTypeNotInNamespace_ShouldReturnFalse)
    {
      Assert::IsFalse(is_type_in_namespace<NotNested>("WubbaLubbaDubDub"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IsTypeInNamespace_InputtingTypeNotInNestedNamespace_ShouldReturnFalse)
    {
      Assert::IsFalse(is_type_in_namespace<NotNested>("TestCeleste::Reflection"));
    }

#pragma endregion

#pragma region Is In Namespace Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_IsInNamespace_TypeInNamespace_ShouldReturnTrue)
    {
      Assert::IsTrue(Type<NotNested>().isInNamespace(std::string("TestCeleste")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_IsInNamespace_TypeInNestedNamespace_ShouldReturnTrue)
    {
      Assert::IsTrue(Type<Nested>().isInNamespace(std::string("TestCeleste::Reflection")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_IsInNamespace_TypeNotInNamespace_ShouldReturnFalse)
    {
      Assert::IsFalse(Type<NotNested>().isInNamespace(std::string("WubbaLubbaDubDub")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Type_IsInNamespace_TypeNotInNestedNamespace_ShouldReturnFalse)
    {
      Assert::IsFalse(Type<NotNested>().isInNamespace(std::string("TestCeleste::Reflection")));
    }

#pragma endregion

    };
  }
}