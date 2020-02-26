#include "UtilityHeaders/UnitTestHeaders.h"

#include "XML/Elements/ListElement.h"
#include "XML/XMLObjectFactory.h"
#include "XML/tinyxml2_ext.h"

using namespace tinyxml2;
using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestFloatListElement)

#pragma region Convert From XML Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_AllChildElementsHaveInvalidText_ReturnsFalse)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("Waiodssaod");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsFalse(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_AllChildElementsHaveInvalidText_DoesNotAddAnyValues)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("Waiodssaod");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::IsTrue(element->getChildren().empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_SomeChildElementsHaveInvalidText_ReturnsFalse)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("5");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsFalse(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_SomeChildElementsHaveValidText_AddsCorrectNumberForEachValidChild)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("5");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(1), element->getChildren().size());
      Assert::AreEqual(5.0f, element->getChildren()[0]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_AllChildElementsHaveValidText_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("5");
      child2->SetText("-0.123");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatListElement_ConvertFromXML_AllChildElementsHaveValidText_AddsCorrectNumberForEachChild)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("5");
      child2->SetText("-0.123");

      std::unique_ptr<ListElement<float>> element(XMLObjectFactory::create<ListElement, float>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(2), element->getChildren().size());
      Assert::AreEqual(5.0f, element->getChildren()[0]);
      Assert::AreEqual(-0.123f, element->getChildren()[1]);
    }

#pragma endregion

    };
  }
}