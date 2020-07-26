#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/UI/MockStackPanelDataConverter.h"
#include "TestResources/UI/StackPanelLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "UI/StackPanel.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "CelesteTestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestStackPanelDataConverter)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<StackPanelDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getValidRelativePath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<StackPanel*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Instantiate_SetsInputtedPointer_ToNewStackPanelDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    StackPanelDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<StackPanelDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    StackPanelDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    StackPanelDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsElementName_ToInput)
  {
    StackPanelDataConverter converter;

    Assert::AreEqual("StackPanel", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsOrientation_TokVertical)
  {
    StackPanelDataConverter converter;

    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsHorizontalAlignment_TokCentre)
  {
    StackPanelDataConverter converter;

    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsVerticalAlignment_TokCentre)
  {
    StackPanelDataConverter converter;

    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_SetsPadding_ToZero)
  {
    StackPanelDataConverter converter;

    Assert::AreEqual(0.0f, converter.getPadding());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_AddsOrientationAttribute)
  {
    const MockStackPanelDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_AddsHorizontalAlignmentAttribute)
  {
    const MockStackPanelDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_AddsVerticalAlignmentAttribute)
  {
    const MockStackPanelDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_Constructor_AddsPaddingAttribute)
  {
    const MockStackPanelDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    StackPanelDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    StackPanelDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    StackPanelDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    StackPanelDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getValidRelativePath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    StackPanelDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getValidRelativePath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Orientation Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_NoOrientationAttribute_DoesNothing_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("StackPanel");

    Assert::IsNull(element->FindAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_OrientationAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME, "Wuahdisaubd");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_OrientationAttribute_ValidText_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME, "horizontal");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getOrientation() == Orientation::kVertical);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOrientation() == Orientation::kHorizontal);
  }

#pragma endregion

#pragma region Convert Vertical Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_NoVerticalAlignmentAttribute_DoesNothing_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("StackPanel");

    Assert::IsNull(element->FindAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_VerticalAlignmentAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, "Wuahdisaubd");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_VerticalAlignmentAttribute_ValidText_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, "top");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kTop);
  }

#pragma endregion

#pragma region Horizontal Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_NoHorizontalAlignmentAttribute_DoesNothing_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("StackPanel");

    Assert::IsNull(element->FindAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_HorizontalAlignmentAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, "Wuahdisaubd");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_HorizontalAlignmentAttribute_ValidText_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, "left");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kLeft);
  }

#pragma endregion

#pragma region Padding Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_NoPaddingAttribute_DoesNothing_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("StackPanel");

    Assert::IsNull(element->FindAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getPadding());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getPadding());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_PaddingAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME, "Wuahdisaubd");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getPadding());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getPadding());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_ConvertFromXML_PaddingAttribute_ValidText_ReturnsTrue)
  {
    StackPanelDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("StackPanel");
    element->SetAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME, "12");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(StackPanelDataConverter::PADDING_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getPadding());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(12.0f, converter.getPadding());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_SetValues_InputtingStackPanel_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    stackPanel->setPadding(5);
    stackPanel->setOrientation(Orientation::kHorizontal);

    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getInvalidFullPath());

    StackPanelDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(*stackPanel);

    Assert::AreEqual(5.0f, stackPanel->getPadding());
    Assert::IsTrue(stackPanel->getOrientation() == Orientation::kHorizontal);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_SetValues_InputtingStackPanel_DataLoadedCorrectly_ChangesStackPanelToMatchData)
  {
    GameObject gameObject;
    observer_ptr<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    stackPanel->setPadding(5);
    stackPanel->setOrientation(Orientation::kHorizontal);

    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getValidRelativePath());

    StackPanelDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(*stackPanel);

    Assert::IsTrue(stackPanel->getOrientation() == Orientation::kHorizontal);
    Assert::IsTrue(stackPanel->getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(stackPanel->getVerticalAlignment() == VerticalAlignment::kTop);
    Assert::AreEqual(12.0f, stackPanel->getPadding());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelDataConverter_SetValues_InputtingStackPanel_DataLoadedCorrectly_AddsChildrenCorrectly)
  {
    GameObject gameObject, child, child2;
    child.addComponent<MockRenderer>();
    child2.addComponent<MockRenderer>();
    observer_ptr<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    child.setParent(&gameObject);
    child2.setParent(&gameObject);
    stackPanel->setPadding(5);
    stackPanel->setOrientation(Orientation::kHorizontal);

    observer_ptr<Data> data = getResourceManager().load<Data>(StackPanelLoadingResources::getValidRelativePath());

    StackPanelDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
    Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

    converter.setValues(*stackPanel);

    Assert::IsTrue(stackPanel->getOrientation() == Orientation::kHorizontal);
    Assert::IsTrue(stackPanel->getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(stackPanel->getVerticalAlignment() == VerticalAlignment::kTop);
    Assert::AreEqual(12.0f, stackPanel->getPadding());
    Assert::AreEqual(static_cast<size_t>(2), stackPanel->childCount());
  }

#pragma endregion

  };
}