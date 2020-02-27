#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/GraphicalFX/MockOpacityLerperDataConverter.h"
#include "Resources/GraphicalFX/OpacityLerperLoadingResources.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Resources/ResourceManager.h"
#include "GraphicalFX/OpacityLerper.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestOpacityLerperDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestOpacityLerperDataConverter::testInitialize()
  {
    OpacityLerperLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<OpacityLerperDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(OpacityLerperLoadingResources::getValidFullPath());
    AutoDeallocator<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<OpacityLerper*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Instantiate_SetsInputtedPointer_ToNewOpacityLerperDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    OpacityLerperDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<OpacityLerperDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    OpacityLerperDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    OpacityLerperDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsElementName_ToInput)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual("OpacityLerper", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsMinOpacity_ToZero)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMinOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsMaxOpacity_ToOne)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getMaxOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsLerpUpTime_ToOne)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getLerpUpTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsLerpDownTime_ToOne)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getLerpDownTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsMaxOpacityWaitTime_ToZero)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_SetsMinOpacityWaitTime_ToZero)
  {
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsMaxOpacityAttribute)
  {
    const MockOpacityLerperDataConverter converter;
    
    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::MAX_OPACITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsMinOpacityAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::MIN_OPACITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsLerpUpTimeAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::LERP_UP_TIME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsLerpDownTimeAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::LERP_DOWN_TIME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsMaxOpacityWaitTimeAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsMinOpacityWaitTimeAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_Constructor_AddsLerpingUpAttribute)
  {
    const MockOpacityLerperDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(OpacityLerperDataConverter::LERPING_UP_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    OpacityLerperDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    OpacityLerperDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(OpacityLerperLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    OpacityLerperDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(OpacityLerperLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(OpacityLerperLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    OpacityLerperDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(OpacityLerperLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Min Opacity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoMinOpacityAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMinOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMinOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MinOpacityAttribute_InvalidText_SetsValueToZero_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MIN_OPACITY_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(0.0f, converter.getMinOpacity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMinOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MinOpacityAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MIN_OPACITY_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(0.0f, converter.getMinOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getMinOpacity());
  }

#pragma endregion

#pragma region Convert Max Opacity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoMaxOpacityAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getMaxOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getMaxOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MaxOpacityAttribute_InvalidText_SetsValueToOne_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MAX_OPACITY_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(1.0f, converter.getMaxOpacity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getMaxOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MaxOpacityAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MAX_OPACITY_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(1.0f, converter.getMaxOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getMaxOpacity());
  }

#pragma endregion

#pragma region Convert Lerp Up Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoLerpUpTimeAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getLerpUpTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getLerpUpTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpUpTimeAttribute_InvalidText_SetsValueToOne_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERP_UP_TIME_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(1.0f, converter.getLerpUpTime());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getLerpUpTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpUpTimeAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERP_UP_TIME_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(1.0f, converter.getLerpUpTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getLerpUpTime());
  }

#pragma endregion

#pragma region Convert Lerp Down Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoLerpDownTimeAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(1.0f, converter.getLerpDownTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getLerpDownTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpDownTimeAttribute_InvalidText_SetsValueToOne_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERP_DOWN_TIME_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(1.0f, converter.getLerpDownTime());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getLerpDownTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpDownTimeAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERP_DOWN_TIME_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(1.0f, converter.getLerpDownTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getLerpDownTime());
  }

#pragma endregion

#pragma region Convert Max Opacity Wait Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoMaxOpacityWaitTimeAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MaxOpacityWaitTimeAttribute_InvalidText_SetsValueToZero_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MaxOpacityWaitTimeAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(0.0f, converter.getMaxOpacityWaitTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getMaxOpacityWaitTime());
  }

#pragma endregion

#pragma region Convert Min Opacity Wait Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoMinOpacityWaitTimeAttribute_DoesNothing_AndReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    OpacityLerperDataConverter converter;

    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MinOpacityWaitTimeAttribute_InvalidText_SetsValueToZero_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_MinOpacityWaitTimeAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(0.0f, converter.getMinOpacityWaitTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getMinOpacityWaitTime());
  }

#pragma endregion

#pragma region Convert Lerping Up Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_NoLerpingUpAttribute_DoesNothing_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");

    Assert::IsTrue(converter.getLerpingUp());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getLerpingUp());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpingUpAttribute_InvalidText_SetsValueToTrue_AndReturnsFalse)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERPING_UP_ATTRIBUTE_NAME, "WubDubDub");

    Assert::IsTrue(converter.getLerpingUp());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getLerpingUp());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_ConvertFromXML_LerpingUpAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    OpacityLerperDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("OpacityLerper");
    element->SetAttribute(OpacityLerperDataConverter::LERPING_UP_ATTRIBUTE_NAME, false);

    Assert::IsTrue(converter.getLerpingUp());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getLerpingUp());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_SetValues_InputtingNullOpacityLerper_DoesNothing)
  {
    OpacityLerperDataConverter converter;
    converter.setValues(OpacityLerper());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_SetValues_InputtingOpacityLerper_DataNotLoadedCorrectly_DoesNothing)
  {
    OpacityLerper lerper;
    lerper.setLerpingUp(false);
    lerper.setMaxOpacity(0.5f);
    lerper.setMinOpacity(0.1f);

    OpacityLerperDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(lerper);

    Assert::IsFalse(lerper.isLerpingUp());
    Assert::AreEqual(0.5f, lerper.getMaxOpacity());
    Assert::AreEqual(0.1f, lerper.getMinOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerperDataConverter_SetValues_InputtingOpacityLerper_DataLoadedCorrectly_ChangesOpacityLerperToMatchData)
  {
    OpacityLerper lerper;
    lerper.setLerpingUp(false);
    lerper.setMaxOpacity(0.5f);
    lerper.setMinOpacity(0.1f);

    // Valid.xml
    // <OpacityLerper min_opacity="0.1" max_opacity="0.8" lerp_up_time="0.5" lerp_down_time="1" 
    //                max_opacity_wait_time="1.5" min_opacity_wait_time="2.5" lerping_up="false"/>

    OpacityLerperDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(OpacityLerperLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(lerper);

    Assert::AreEqual(0.1f, lerper.getMinOpacity());
    Assert::AreEqual(0.8f, lerper.getMaxOpacity());
    Assert::AreEqual(0.5f, lerper.getLerpUpTime());
    Assert::AreEqual(1.0f, lerper.getLerpDownTime());
    Assert::AreEqual(1.5f, lerper.getMaxOpacityWaitTime());
    Assert::AreEqual(2.5f, lerper.getMinOpacityWaitTime());
    Assert::IsFalse(lerper.isLerpingUp());
  }

#pragma endregion

  };
}