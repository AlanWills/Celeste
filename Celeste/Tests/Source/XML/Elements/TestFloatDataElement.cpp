#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/Elements/DataElement.h"
#include "XML/XMLObjectFactory.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestFloatDataElement)

#pragma region Convert From XML Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDataElement_ConvertFromXML_InputtingNullptr_ReturnFalse)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::IsFalse(converter->convertFromXML(nullptr));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDataElement_ConvertFromXML_InputtingElement_NoTextSet_ReturnsFalse)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");

      Assert::IsNull(element->GetText());
      Assert::IsFalse(converter->convertFromXML(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDataElement_ConvertFromXML_InputtingElement_NoTextSet_DoesNotChangeValue)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");

      Assert::IsNull(element->GetText());
      Assert::AreEqual(0.0f, converter->getValue());

      converter->convertFromXML(element);

      Assert::AreEqual(0.0f, converter->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatElement_ConvertFromXML_InputtingElement_WithInvalidTextSet_ReturnsFalse)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");
      element->SetText("WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->GetText());
      Assert::IsFalse(converter->convertFromXML(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatElement_ConvertFromXML_InputtingElement_WithInvalidTextSet_DoesNotChangeValue)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("");
      element->SetText("WubbaLubbaDubDub");

      Assert::AreEqual("WubbaLubbaDubDub", element->GetText());
      Assert::AreEqual(0.0f, converter->getValue());

      converter->convertFromXML(element);

      Assert::AreEqual(0.0f, converter->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringElement_ConvertFromXML_InputtingElement_WithValidTextSet_ReturnsTrue)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("Text");
      element->SetText("0.05");

      Assert::AreEqual("0.05", element->GetText());
      Assert::IsTrue(converter->convertFromXML(element));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringElement_ConvertFromXML_InputtingElement_WithValidTextSet_SetsValueToCorrectNumber)
    {
      std::unique_ptr<ValueElement<float>> converter(XMLObjectFactory::create<ValueElement, float>(
        "Text", 0.0f, DeserializationRequirement::kNotRequired));
      XMLDocument document;
      XMLElement* element = document.NewElement("");
      element->SetText("0.05");

      Assert::AreEqual("0.05", element->GetText());
      Assert::AreEqual(0.0f, converter->getValue());

      converter->convertFromXML(element);

      Assert::AreEqual(0.05f, converter->getValue());
    }

#pragma endregion

    };
  }
}