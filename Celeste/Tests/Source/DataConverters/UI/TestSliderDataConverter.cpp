#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/UI/MockSliderDataConverter.h"
#include "Resources/UI/SliderLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"
#include "Rendering/SpriteRenderer.h"
#include "UI/Slider.h"
#include "AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSliderDataConverter)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<SliderDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Rendering::SpriteRenderer> spriteRenderer = gameObject.addComponent<Rendering::SpriteRenderer>();
    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getValidNoCallbacksFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Slider*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Instantiate_SetsInputtedPointer_ToNewSliderDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    SliderDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<SliderDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SliderDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    SliderDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsElementName_ToInput)
  {
    SliderDataConverter converter;

    Assert::AreEqual("Slider", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsMin_ToZero)
  {
    SliderDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsMax_ToZero)
  {
    SliderDataConverter converter;

    Assert::AreEqual(1.0f, converter.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_SetsValue_ToZero)
  {
    SliderDataConverter converter;

    Assert::AreEqual(0.0f, converter.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_AddsMinAttribute)
  {
    const MockSliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_AddsMaxAttribute)
  {
    const MockSliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_Constructor_AddsCurrentValueAttribute)
  {
    const MockSliderDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    SliderDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SliderDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    SliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    SliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getValidNoCallbacksFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    SliderDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getValidNoCallbacksFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Min Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_NoMinAttribute_DoesNothing_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getMin());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_MinAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME, "dhsa");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME));
    Assert::AreEqual("dhsa", static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME)->Value());
    Assert::AreEqual(0.0f, converter.getMin());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_MinAttribute_ValidText_SetsMinToCorrectNumber_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME, 0.1f);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MIN_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getMin());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.1f, converter.getMin());
  }

#pragma endregion

#pragma region Convert Max Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_NoMaxAttribute_DoesNothing_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getMax());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_MaxAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME, "dhsa");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME));
    Assert::AreEqual("dhsa", static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME)->Value());
    Assert::AreEqual(1.0f, converter.getMax());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_MaxAttribute_ValidText_SetsMaxToCorrectNumber_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME, 0.1f);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getMax());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.1f, converter.getMax());
  }

#pragma endregion

#pragma region Convert Current Value Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_NoCurrentValueAttribute_DoesNothing_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");

    Assert::IsNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::MAX_ATTRIBUTE_NAME));
    Assert::AreEqual(1.0f, converter.getMax());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_CurrentValueAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME, "dhsa");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME));
    Assert::AreEqual("dhsa", static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME)->Value());
    Assert::AreEqual(0.0f, converter.getValue());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_ConvertFromXML_CurrentValueAttribute_ValidText_SetsCurrentValueToCorrectNumber_ReturnsTrue)
  {
    SliderDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Slider");
    element->SetAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME, 0.1f);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(SliderDataConverter::VALUE_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getValue());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.1f, converter.getValue());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_SetValues_InputtingSlider_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<Rendering::SpriteRenderer> spriteRenderer = gameObject.addComponent<Rendering::SpriteRenderer>();
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();
    slider->setCurrentValue(0.5f);

    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getInvalidFullPath());

    SliderDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(*slider);

    Assert::AreEqual(0.5f, slider->getCurrentValue());
    AssertCel::IsActive(*slider);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderDataConverter_SetValues_InputtingSlider_DataLoadedCorrectly_ChangesSliderToMatchData)
  {
    GameObject gameObject;
    observer_ptr<Rendering::SpriteRenderer> spriteRenderer = gameObject.addComponent<Rendering::SpriteRenderer>();
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();
    slider->setCurrentValue(0.5f);
    slider->setActive(false);

    observer_ptr<Data> data = getResourceManager().load<Data>(SliderLoadingResources::getValidWithCallbacksFullPath());

    SliderDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(*slider);

    Assert::AreEqual(6.25f, slider->getCurrentValue());
    AssertCel::IsActive(*slider);
  }

#pragma endregion

  };
}