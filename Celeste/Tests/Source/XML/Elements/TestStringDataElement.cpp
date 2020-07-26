#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/Elements/DataElement.h"
#include "XML/XMLObjectFactory.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestStringDataElement)

#pragma region Convert From XML Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringDataElement_ConvertFromXML_InputtingNullptr_ReturnFalse)
    {
      std::unique_ptr<ValueElement<std::string>> converter(XMLObjectFactory::create<ValueElement, std::string>(
        "Text", "", DeserializationRequirement::kNotRequired));

      Assert::IsFalse(converter->convertFromXML(nullptr));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringDataElement_ConvertFromXML_InputtingElement_NoTextSet_ReturnsTrue)
    {
      std::unique_ptr<ValueElement<std::string>> converter(XMLObjectFactory::create<ValueElement, std::string>(
        "Text", "", DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");

      Assert::IsNull(element->GetText());
      Assert::IsTrue(converter->convertFromXML(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringDataElement_ConvertFromXML_InputtingElement_NoTextSet_SetsValueToEmptyString)
    {
      std::unique_ptr<ValueElement<std::string>> converter(XMLObjectFactory::create<ValueElement, std::string>(
        "Text", "", DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");

      Assert::IsNull(element->GetText());

      converter->convertFromXML(element);

      Assert::AreEqual("", converter->getValue().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringElement_ConvertFromXML_InputtingElement_WithTextSet_ReturnsTrue)
    {
      std::unique_ptr<ValueElement<std::string>> converter(XMLObjectFactory::create<ValueElement, std::string>(
        "Text", "", DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");
      element->SetText("WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->GetText());
      Assert::IsTrue(converter->convertFromXML(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringElement_ConvertFromXML_InputtingElement_WithTextSet_SetsValueToText)
    {
      std::unique_ptr<ValueElement<std::string>> converter(XMLObjectFactory::create<ValueElement, std::string>(
        "Text", "", DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("");
      element->SetText("WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->GetText());

      converter->convertFromXML(element);

      Assert::AreEqual("WubbaLubbaDubDub", converter->getValue().c_str());
    }

#pragma endregion

    };
  }
}