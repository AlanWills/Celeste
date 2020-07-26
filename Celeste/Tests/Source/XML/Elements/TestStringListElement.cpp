#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

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
    CELESTE_TEST_CLASS(TestStringListElement)

#pragma region Convert From XML Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_AllChildElementsHaveEmptyText_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsNull(child1->GetText());
      Assert::IsNull(child2->GetText());
      Assert::IsTrue(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_AllChildElementsHaveEmptyText_IsNotRequired_AddsEmptyTextForEachChild)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsFalse(element->isRequired());
      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(2), element->getChildren().size());
      Assert::IsTrue(element->getChildren()[0].empty());
      Assert::IsTrue(element->getChildren()[1].empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_AllChildElementsHaveEmptyText_IsRequired_DoesNotChangeOutput)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::IsTrue(element->getChildren().empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_SomeChildElementsHaveNonEmptyText_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("sadnausd");

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_SomeChildElementsHaveNonEmptyText_IsNotRequired_AddsCorrectTextForEachChild)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("sadnausd");

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsFalse(element->isRequired());
      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(2), element->getChildren().size());
      Assert::AreEqual("sadnausd", element->getChildren()[0].c_str());
      Assert::IsTrue(element->getChildren()[1].empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_SomeChildElementsHaveNonEmptyText_IsRequired_DoesNothing)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("sadnausd");

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kRequired));

      Assert::IsTrue(element->isRequired());
      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(1), element->getChildren().size());
      Assert::AreEqual("sadnausd", element->getChildren()[0].c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_AllChildElementsHaveNonEmptyText_ReturnsTrue)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("sadnausd");
      child2->SetText("aqeojpeof");

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->convertFromXML(root));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringListElement_ConvertFromXML_AllChildElementsHaveNonEmptyText_AddsCorrectTextForEachChild)
    {
      XMLDocument document;
      XMLElement* root = document.NewElement("Test");
      XMLElement* child1 = document.NewElement("Child1");
      XMLElement* child2 = document.NewElement("Child2");
      document.InsertFirstChild(root);
      root->InsertFirstChild(child1);
      root->InsertEndChild(child2);
      child1->SetText("sadnausd");
      child2->SetText("aqeojpeof");

      std::unique_ptr<ListElement<std::string>> element(XMLObjectFactory::create<ListElement, std::string>(
        "Test", DeserializationRequirement::kNotRequired));

      Assert::IsTrue(element->getChildren().empty());

      element->convertFromXML(root);

      Assert::AreEqual(static_cast<size_t>(2), element->getChildren().size());
      Assert::AreEqual("sadnausd", element->getChildren()[0].c_str());
      Assert::AreEqual("aqeojpeof", element->getChildren()[1].c_str());
    }

#pragma endregion

    };
  }
}