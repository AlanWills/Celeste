#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/BindingUtils.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestBindingUtils)

#pragma region Display Name To Variable Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingEmptyString_ReturnsEmptyString)
    {
      Assert::IsTrue(displayNameToVariableName("").empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingSingleCapitalisedWord_ReturnsSameWord)
    {
      Assert::AreEqual("Test", displayNameToVariableName("Test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingSingleUncapitalisedWord_ReturnsCapitalisedWord)
    {
      Assert::AreEqual("Test", displayNameToVariableName("test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingMultipleCapitalisedWords_ReturnsSameWord)
    {
      Assert::AreEqual("TestVariableName", displayNameToVariableName("Test Variable Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingMultipleUncapitalisedWords_ReturnsCapitalisedWords)
    {
      Assert::AreEqual("TestVariableName", displayNameToVariableName("test variable name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingMixOfCapitalisedAndUncapitalisedWords_ReturnsCapitalisedWords)
    {
      Assert::AreEqual("TestVariableName", displayNameToVariableName("test Variable name").c_str());
    } 

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_IgnoresWhitespaceAtBeginningAndEnd)
    {
      Assert::AreEqual("TestVariableName", displayNameToVariableName("   test variable name    ").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_DisplayNameToVariableName_InputtingAllWhitespace_ReturnsEmptyString)
    {
      Assert::IsTrue(displayNameToVariableName("   ").empty());
    }

#pragma endregion

#pragma region Xml Attribute Name To Variable Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingEmptyString_ReturnsEmptyString)
    {
      Assert::IsTrue(xmlAttributeNameToVariableName("").empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingSingleCapitalised_ReturnsSameWord)
    {
      Assert::AreEqual("Test", xmlAttributeNameToVariableName("Test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingSingleUncapitalised_ReturnsCapitalisedWord)
    {
      Assert::AreEqual("Test", xmlAttributeNameToVariableName("test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingCapitalisedWordsSeparatedByUnderscores_ReturnsCapitalisedWords)
    {
      Assert::AreEqual("TestVariableName", xmlAttributeNameToVariableName("Test_Variable_Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingUncapitalisedWordsSeparatedByUnderscores_ReturnsCapitalisedWords)
    {
      Assert::AreEqual("TestVariableName", xmlAttributeNameToVariableName("test_variable_name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingMixOfCapitalisedAndUncapitalisedWordsSeparatedByUnderscores_ReturnsCapitalisedWords)
    {
      Assert::AreEqual("TestVariableName", xmlAttributeNameToVariableName("test_Variable_Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_IgnoresWhitespaceAtBeginningAndEnd)
    {
      Assert::AreEqual("TestVariableName", xmlAttributeNameToVariableName("   test_variable_name    ").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToVariableName_InputtingAllWhitespace_ReturnsEmptyString)
    {
      Assert::IsTrue(xmlAttributeNameToVariableName("   ").empty());
    }

#pragma endregion

#pragma region Xml Attribute Name To Display Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingEmptyString_ReturnsEmptyString)
    {
      Assert::IsTrue(xmlAttributeNameToDisplayName("").empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingSingleCapitalised_ReturnsSameWord)
    {
      Assert::AreEqual("Test", xmlAttributeNameToDisplayName("Test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingSingleUncapitalised_ReturnsCapitalisedWord)
    {
      Assert::AreEqual("Test", xmlAttributeNameToDisplayName("test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingCapitalisedWordsSeparatedByUnderscores_ReturnsWordsSeparatedBySpace)
    {
      Assert::AreEqual("Test Variable Name", xmlAttributeNameToDisplayName("Test_Variable_Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingUncapitalisedWordsSeparatedByUnderscores_ReturnsCapitalisedWordsSeparatedBySpace)
    {
      Assert::AreEqual("Test Variable Name", xmlAttributeNameToDisplayName("test_variable_name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingMixOfCapitalisedAndUncapitalisedWordsSeparatedByUnderscores_ReturnsCapitalisedWordsSeparatedBySpace)
    {
      Assert::AreEqual("Test Variable Name", xmlAttributeNameToDisplayName("test_Variable_Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_IgnoresWhitespaceAtBeginningAndEnd)
    {
      Assert::AreEqual("Test Variable Name", xmlAttributeNameToDisplayName("   test_variable_name    ").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_XmlAttributeNameToDisplayName_InputtingAllWhitespace_ReturnsEmptyString)
    {
      Assert::IsTrue(xmlAttributeNameToDisplayName("   ").empty());
    }

#pragma endregion

#pragma region Variable Name To Display Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingEmptyString_ReturnsEmptyString)
    {
      Assert::IsTrue(variableNameToDisplayName("").empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingSingleCapitalised_ReturnsSameWord)
    {
      Assert::AreEqual("Test", variableNameToDisplayName("Test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingSingleUncapitalised_ReturnsUncapitalisedWord)
    {
      Assert::AreEqual("test", variableNameToDisplayName("test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingCapitalisedWordsConcatenatedTogether_ReturnsWordsSeparatedBySpaces)
    {
      Assert::AreEqual("Test Variable Name", variableNameToDisplayName("TestVariableName").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingWordSeparatedBySpaces_DoesNothing)
    {
      Assert::AreEqual("Test Variable Name", variableNameToDisplayName("Test Variable Name").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_IgnoresWhitespaceAtBeginningAndEnd)
    {
      Assert::AreEqual("Test Variable Name", variableNameToDisplayName("   TestVariableName    ").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_VariableNameToDisplayName_InputtingAllWhitespace_ReturnsEmptyString)
    {
      Assert::IsTrue(variableNameToDisplayName("   ").empty());
    }

#pragma endregion

#pragma region Cpp Namespace To Cs Namespace Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_CppNamespaceToCsNamespace_InputtingEmptyString_ReturnsEmptyString)
    {
      Assert::IsTrue(cppNamespaceToCsNamespace("").empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_CppNamespaceToCsNamespace_InputtingWhitespaceString_ReturnsInputtedString)
    {
      Assert::AreEqual("    ", cppNamespaceToCsNamespace("    ").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_CppNamespaceToCsNamespace_InputtingSingleName_ReturnsInputtedString)
    {
      Assert::AreEqual("Test", cppNamespaceToCsNamespace("Test").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_CppNamespaceToCsNamespace_InputtingNestedName_ReturnsCorrectNamespaceName)
    {
      Assert::AreEqual("Test.Namespace", cppNamespaceToCsNamespace("Test::Namespace").c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BindingUtils_CppNamespaceToCsNamespace_InputtingMultiplyNestedName_ReturnsCorrectNamespaceName)
    {
      Assert::AreEqual("Test.Namespace.To.Another.Level", cppNamespaceToCsNamespace("Test::Namespace::To::Another::Level").c_str());
    }

#pragma endregion

    };
  }
}