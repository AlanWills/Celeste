#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/tinyxml2_ext.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(Test_tinyxml2_ext)

#pragma region Get Child Element Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GetChildElementCount_InputtingNullptr_ReturnsZero)
  {
    Assert::AreEqual((size_t)0, getChildElementCount(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GetChildElementCount_InputtingElementWithNoChildren_ReturnsZero)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");

    Assert::IsTrue(element->NoChildren());
    Assert::AreEqual((size_t)0, getChildElementCount(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GetChildElementCount_InputtingElementWithChildren_ReturnsCorrectNumberOfChildren)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->InsertFirstChild(document.NewElement("TestChild1"));
    element->InsertFirstChild(document.NewElement("TestChild2"));
    element->InsertFirstChild(document.NewElement("TestChild3"));

    Assert::IsFalse(element->NoChildren());
    Assert::AreEqual((size_t)3, getChildElementCount(element));
  }

#pragma endregion

#pragma region Get Element Data Tests (String Template)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_StringTemplate_InputtingNullElement_ReturnskError_AndDoesNotChangeInput)
    {
      std::string string;

      Assert::IsTrue(getElementData(nullptr, string) == XMLValueError::kError);
      Assert::IsTrue(string.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_StringTemplate_InputtingNonNullElement_ButNoElementText_ReturnskDoesNotExist_AndDoesNotChangeInput)
    {
      std::string string;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");

      Assert::IsTrue(getElementData(root, string) == XMLValueError::kDoesNotExist);
      Assert::IsTrue(string.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_StringTemplate_InputtingNonNullElement_WithElementText_ReturnskSuccess_AndDoesNotChangeInput)
    {
      std::string string;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->SetText("InnerText");

      Assert::IsTrue(getElementData(root, string) == XMLValueError::kSuccess);
      Assert::AreEqual("InnerText", string.c_str());
    }

#pragma endregion

#pragma region Get Element Data Tests (Float Template)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_FloatTemplate_InputtingNullElement_ReturnskError_AndDoesNotChangeInput)
    {
      float output = 0;

      Assert::IsTrue(getElementData(nullptr, output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_FloatTemplate_InputtingNonNullElement_ButNoElementText_ReturnskErrorAndDoesNotChangeInput)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");

      Assert::IsTrue(getElementData(root, output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_FloatTemplate_InputtingNonNullElement_WithElementTextButNotNumber_ReturnskError_AndDoesNotChangeInput)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->SetText("InnerText");

      Assert::IsTrue(getElementData(root, output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetElementData_FloatTemplate_InputtingNonNullElement_WithElementTextAsNumber_ReturnskSuccess_AndNumber)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->SetText("12.11");

      Assert::IsTrue(getElementData(root, output) == XMLValueError::kSuccess);
      Assert::AreEqual(12.11f, output);
    }

#pragma endregion

#pragma region Has Child Element Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HasChildElement_InputtingNullElement_ReturnsFalse)
    {
      Assert::IsFalse(hasChildElement(nullptr, "Child"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HasChildElement_InputtingElement_ButNonExistentChildElementName_ReturnsFalse)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");

      Assert::IsFalse(hasChildElement(root, "Child"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HasChildElement_InputtingElement_ButExistentChildElementName_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->InsertFirstChild(document.NewElement("Child"));

      Assert::IsTrue(hasChildElement(root, "Child"));
    }

#pragma endregion

#pragma region Get Child Element Data Tests (String Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_StringTemplate_InputtingNullElement_ReturnskError_AndDoesNotChangeInput)
    {
      std::string string;

      Assert::IsTrue(getChildElementData(nullptr, "Root", string) == XMLValueError::kError);
      Assert::IsTrue(string.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_StringTemplate_InputtingNonExistentChildElementName_ReturnskDoesNotExist_AndDoesNotChangeInput)
    {
      std::string string;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");

      Assert::IsTrue(getChildElementData(root, "Child", string) == XMLValueError::kDoesNotExist);
      Assert::IsTrue(string.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_StringTemplate_InputtingExistentChildElementName_ButNoElementText_ReturnskDoesNotExist_AndDoesNotChangeInput)
    {
      std::string string;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->InsertFirstChild(document.NewElement("Child"));

      Assert::IsTrue(getChildElementData(root, "Child", string) == XMLValueError::kDoesNotExist);
      Assert::IsTrue(string.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_StringTemplate_InputtingExistentChildElementName_WithElementText_ReturnskSuccess_AndDoesNotChangeInput)
    {
      std::string string;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      child->SetText("InnerText");
      root->InsertFirstChild(child);

      Assert::IsTrue(getChildElementData(root, "Child", string) == XMLValueError::kSuccess);
      Assert::AreEqual("InnerText", string.c_str());
    }

#pragma endregion

#pragma region Get Child Element Data Tests (Float Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_FloatTemplate_InputtingNullElement_ReturnskError_AndDoesNotChangeInput)
    {
      float output = 0;

      Assert::IsTrue(getChildElementData(nullptr, "Root", output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_FloatTemplate_InputtingNonExistentChildElementName_ReturnskDoesNotExist_AndDoesNotChangeInput)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");

      Assert::IsTrue(getChildElementData(root, "Child", output) == XMLValueError::kDoesNotExist);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_FloatTemplate_InputtingExistentChildElementName_ButNoElementText_ReturnskError_AndDoesNotChangeInput)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      root->InsertFirstChild(document.NewElement("Child"));

      Assert::IsTrue(getChildElementData(root, "Child", output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_FloatTemplate_InputtingExistentChildElementName_WithElementTextButNotNumber_ReturnskError_AndDoesNotChangeInput)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      child->SetText("InnerText");
      root->InsertFirstChild(child);

      Assert::IsTrue(getChildElementData(root, "Child", output) == XMLValueError::kError);
      Assert::AreEqual(0.0f, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementData_FloatTemplate_InputtingExistentChildElementName_WithElementTextAsNumber_ReturnskSuccess_AndNumber)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* root = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      child->SetText("12.11");
      root->InsertFirstChild(child);

      Assert::IsTrue(getChildElementData(root, "Child", output) == XMLValueError::kSuccess);
      Assert::AreEqual(12.11f, output);
    }

#pragma endregion

#pragma region Get Child Element Data As Vector (Float Template)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_FloatTemplate_InputtingNullElement_ReturnskError_AndDoesNotModifyList)
    {
      std::vector<float> output;

      Assert::IsTrue(getChildElementDataAsVector(nullptr, "Root", "Item", output) == XML::XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_FloatTemplate_InputtingElementWithNoMatchingChild_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->InsertFirstChild(document.NewElement("Child2"));
      std::vector<float> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_FloatTemplate_InputtingElementWithNoMatchingItemElements_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->InsertFirstChild(document.NewElement("Child"));
      std::vector<float> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_FloatTemplate_InputtingElementWithMatchingItemElements_AllElementsValid_ReturnskSuccess_AndAddsCorrectValues)
    {
      // Test empty element text & non-float element text
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      XMLElement* positiveFloat = document.NewElement("Item");
      positiveFloat->SetText("12.02");
      XMLElement* negativeFloat = document.NewElement("Item");
      negativeFloat->SetText("-6.661");
      element->InsertFirstChild(child);
      child->InsertEndChild(positiveFloat);
      child->InsertEndChild(negativeFloat);
      std::vector<float> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kSuccess);
      Assert::AreEqual((size_t)2, output.size());
      Assert::AreEqual(12.02f, output[0]);
      Assert::AreEqual(-6.661f, output[1]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_FloatTemplate_InputtingElementWithMatchingItemElements_AtLeastOneInvalidElement_ReturnskError_AddsDoesNotChangeOutputList)
    {
      // Test empty element text & non-float element text
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      XMLElement* empty = document.NewElement("Item");  // Empty
      XMLElement* nonFloat = document.NewElement("Item");
      nonFloat->SetText("pagsda");
      XMLElement* positiveFloat = document.NewElement("Item");
      positiveFloat->SetText("12.02");
      XMLElement* negativeFloat = document.NewElement("Item");
      negativeFloat->SetText("-6.661");
      element->InsertFirstChild(child);
      child->InsertEndChild(empty);
      child->InsertEndChild(nonFloat);
      child->InsertEndChild(positiveFloat);
      child->InsertEndChild(negativeFloat);
      std::vector<float> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

#pragma endregion

#pragma region Get Child Element Data As Vector (String Template)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingNullElement_ReturnskError_AndDoesNotModifyList)
    {
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(nullptr, "Root", "Item", output) == XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingElementWithNoMatchingChild_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->InsertFirstChild(document.NewElement("Child2"));
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingElementWithNoMatchingItemElements_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->InsertFirstChild(document.NewElement("Child"));
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingElementWithEmptyItemElements_DontAllowEmptyElements_ReturnskSuccess_DoesNotAddEmptyChildren)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      XMLElement* empty = document.NewElement("Item");  // Empty
      XMLElement* empty2 = document.NewElement("Item");  // Empty
      element->InsertFirstChild(child);
      child->InsertEndChild(empty);
      child->InsertEndChild(empty2);
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output, false) == XML::XMLValueError::kSuccess);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingElementWithEmptyItemElements_AllowEmptyElements_ReturnskSuccess_AddsEmptyChildren)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      XMLElement* empty = document.NewElement("Item");  // Empty
      XMLElement* empty2 = document.NewElement("Item");  // Empty
      element->InsertFirstChild(child);
      child->InsertEndChild(empty);
      child->InsertEndChild(empty2);
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output, true) == XML::XMLValueError::kSuccess);
      Assert::AreEqual(static_cast<size_t>(2), output.size());
      Assert::IsTrue(output[0].empty());
      Assert::IsTrue(output[1].empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetChildElementDataAsVector_StringTemplate_InputtingElementWithMatchingItemElements_ReturnskSuccess_AndAddsAllChildrenWhichAreConvertibleToStrings)
    {
      // Test empty element text & non-float element text
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      XMLElement* child = document.NewElement("Child");
      XMLElement* empty = document.NewElement("Item");  // Empty
      XMLElement* nonFloat = document.NewElement("Item");
      nonFloat->SetText("pagsda");
      XMLElement* positiveFloat = document.NewElement("Item");
      positiveFloat->SetText("12.02");
      XMLElement* negativeFloat = document.NewElement("Item");
      negativeFloat->SetText("-6.661");
      element->InsertFirstChild(child);
      child->InsertEndChild(empty);
      child->InsertEndChild(nonFloat);
      child->InsertEndChild(positiveFloat);
      child->InsertEndChild(negativeFloat);
      std::vector<std::string> output;

      Assert::IsTrue(getChildElementDataAsVector(element, "Child", "Item", output) == XML::XMLValueError::kSuccess);
      Assert::AreEqual((size_t)3, output.size());
      Assert::AreEqual("pagsda", output[0].c_str());
      Assert::AreEqual("12.02", output[1].c_str());
      Assert::AreEqual("-6.661", output[2].c_str());
    }

#pragma endregion

#pragma region Get Attribute Data (Bool Overload)
    
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingNullElement_ReturnskError)
    {
      bool output = false;

      Assert::IsTrue(getAttributeData(nullptr, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingElementWithNoMatchingAttribute_ReturnskDoesNotExist)
    {
      bool output = false;
      XMLDocument document;
      const XMLElement* element = document.NewElement("Root");

      Assert::IsNull(element->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kDoesNotExist);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingElementWithAttributeButNoText_ReturnskError)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_AttributeHasInvalidValue_ReturnskError_AndDoesNotChangeValue)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "wubdubdub");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("wubdubdub", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_AttributeHasTrueValue_ReturnskSuccess_AndTrue)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "true");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("true", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::IsTrue(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_AttributeHasFalseValue_ReturnskSuccess_AndFalse)
    {
      bool output = true;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "false");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("false", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingNullAttribute_ReturnskError)
    {
      bool output = false;

      Assert::IsTrue(getAttributeData(nullptr, output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingNullAttribute_DoesNotChangeInputtedBool)
    {
      bool output = false;
      getAttributeData(nullptr, output);

      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithInvalidValue_ReturnskError)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", "WubbaLubbaDubDub");

      Assert::IsTrue(getAttributeData(element->FindAttribute("BoolAttr"), output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithInvalidValue_DoesNotChangeInputtedBool)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", "WubbaLubbaDubDub");

      getAttributeData(element->FindAttribute("BoolAttr"), output);

      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithFalseValue_ReturnskSuccess)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", false);

      Assert::IsTrue(getAttributeData(element->FindAttribute("BoolAttr"), output) == XMLValueError::kSuccess);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithFalseValue_SetsInputtedBoolToFalse)
    {
      bool output = true;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", false);

      getAttributeData(element->FindAttribute("BoolAttr"), output);

      Assert::IsFalse(output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithTrueValue_ReturnskSuccess)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", true);

      Assert::IsTrue(getAttributeData(element->FindAttribute("BoolAttr"), output) == XMLValueError::kSuccess);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_BoolOverload_InputtingAttribute_WithTrueValue_SetsInputtedBoolToTrue)
    {
      bool output = false;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("BoolAttr", true);

      getAttributeData(element->FindAttribute("BoolAttr"), output);

      Assert::IsTrue(output);
    }

#pragma endregion

#pragma region Get Attribute Data (Int Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingNullAttribute_ReturnskError)
    {
      int output = false;

      Assert::IsTrue(getAttributeData(nullptr, output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingNullAttribute_DoesNotChangeInputtedInt)
    {
      int output = 5;
      getAttributeData(nullptr, output);

      Assert::AreEqual(5, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingAttribute_WithInvalidValue_ReturnskError)
    {
      int output = 5;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("IntAttr", "WubbaLubbaDubDub");

      Assert::IsTrue(getAttributeData(element->FindAttribute("IntAttr"), output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingAttribute_WithInvalidValue_DoesNotChangeInputtedInt)
    {
      int output = 5;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("IntAttr", "WubbaLubbaDubDub");

      getAttributeData(element->FindAttribute("IntAttr"), output);

      Assert::AreEqual(5, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingAttribute_WithValidValue_ReturnskSuccess)
    {
      int output = 5;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("IntAttr", 10);

      Assert::IsTrue(getAttributeData(element->FindAttribute("IntAttr"), output) == XMLValueError::kSuccess);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_IntOverload_InputtingAttribute_WithValidValue_SetsInputtedIntToCorrectValue)
    {
      int output = 5;
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("IntAttr", 10);

      getAttributeData(element->FindAttribute("IntAttr"), output);

      Assert::AreEqual(10, output);
    }

#pragma endregion

#pragma region Get Attribute Data (Float Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_FloatOverload_InputtingNullptr_ReturnskError)
    {
      float output = 0;

      Assert::IsTrue(getAttributeData(nullptr, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_FloatOverload_InputtingElementMatchingAttribute_ReturnskDoesNotExist)
    {
      float output = 0;
      XMLDocument document;
      const XMLElement* element = document.NewElement("Root");

      Assert::IsNull(element->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kDoesNotExist);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_FloatOverload_InputtingElementWithAttributeButNoText_ReturnskError)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_FloatOverload_AttributeHasInvalidValue_ReturnskError_AndDoesNotChangeValue)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "wubdubdub");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("wubdubdub", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_FloatOverload_AttributeHasValidValue_ReturnskSuccess_AndValue)
    {
      float output = 0;
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "-0.1");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("-0.1", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::AreEqual(-0.1f, output);
    }

#pragma endregion

#pragma region Get Attribute Data (String Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_StringOverload_InputtingNullElement_ReturnskError)
    {
      std::string output;

      Assert::IsTrue(getAttributeData(nullptr, "test", output) == XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_StringOverload_InputtingElement_WithNoAttribute_ReturnskDoesNotExist)
    {
      XMLDocument document;
      const XMLElement* element = document.NewElement("Element");
      std::string output;

      Assert::IsNull(element->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_StringOverload_InputtingElement_WithAttribute_EmptyValue_ReturnskSuccess)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      element->SetAttribute("test", "");
      std::string output;

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_StringOverload_InputtingElement_WithAttribute_NonEmptyValue_ReturnskSuccess)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      element->SetAttribute("test", "WubDubDub");
      std::string output;

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::AreEqual("WubDubDub", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_StringOverload_InputtingElement_WithAttribute_NonEmptyValue_AssignsValueToOutput)
    {
      XMLDocument document;
      XMLElement* element = document.NewElement("Element");
      element->SetAttribute("test", "WubDubDub");
      std::string output;
      output.append("Test");

      Assert::AreEqual("Test", output.c_str());
      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
      Assert::AreEqual("WubDubDub", output.c_str());
    }

#pragma endregion

#pragma region Get Attribute Data (Vec3 Overload)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingNullElement_ReturnskError)
    {
      glm::vec3 output = glm::vec3();

      Assert::IsTrue(getAttributeData(nullptr, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingElementWithNoMatchingAttribute_ReturnskDoesNotExist)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      const XMLElement* element = document.NewElement("Root");

      Assert::IsNull(element->FindAttribute("test"));
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kDoesNotExist);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingElementWithAttributeButNoText_ReturnskError)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_AttributeHasInvalidValue_ReturnskError_AndDoesNotChangeValue)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "wubdubdub");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("wubdubdub", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kError);
      Assert::AreEqual(glm::vec3(), output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_AttributeHasValidValue_ReturnskSuccess)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "1, -2, 3.123");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("true", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      Assert::IsTrue(getAttributeData(element, "test", output) == XMLValueError::kSuccess);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_AttributeHasValidValue_SetsOutputToCorrectValue)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Root");
      element->SetAttribute("test", "1, -2, 3.123");

      Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute("test"));
      Assert::AreEqual("true", static_cast<const XMLElement*>(element)->FindAttribute("test")->Value());
      
      getAttributeData(element, "test", output);

      Assert::AreEqual(glm::vec3(1, -2, 3.123f), output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingNullAttribute_ReturnskError)
    {
      glm::vec3 output = glm::vec3();

      Assert::IsTrue(getAttributeData(nullptr, output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingNullAttribute_DoesNotChangeInputtedVec3)
    {
      glm::vec3 output = glm::vec3();
      getAttributeData(nullptr, output);

      Assert::AreEqual(glm::vec3(), output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingAttribute_WithInvalidValue_ReturnskError)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("Vec3Attr", "WubbaLubbaDubDub");

      Assert::IsTrue(getAttributeData(element->FindAttribute("Vec3Attr"), output) == XMLValueError::kError);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingAttribute_WithInvalidValue_DoesNotChangeInputtedVec3)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("Vec3Attr", "WubbaLubbaDubDub");

      getAttributeData(element->FindAttribute("Vec3Attr"), output);

      Assert::AreEqual(glm::vec3(), output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingAttribute_WithValidValue_ReturnskSuccess)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("Vec3Attr", "1, -2, 3.123");

      Assert::IsTrue(getAttributeData(element->FindAttribute("Vec3Attr"), output) == XMLValueError::kSuccess);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetAttributeData_Vec3Overload_InputtingAttribute_WithValidValue_SetsInputtedVec3ToCorrectValue)
    {
      glm::vec3 output = glm::vec3();
      XMLDocument document;
      XMLElement* element = document.NewElement("Test");
      element->SetAttribute("Vec3Attr", "1, -2, 3.123");

      getAttributeData(element->FindAttribute("Vec3Attr"), output);

      Assert::AreEqual(glm::vec3(1, -2, 3.123f), output);
    }

#pragma endregion

  };
}