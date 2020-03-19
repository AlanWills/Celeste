#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Rendering/MockTextRendererDataConverter.h"
#include "TestResources/Rendering/TextRendererLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Rendering/TextRenderer.h"
#include "AssertSpecialization/FileSystem.h"
#include "AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTextRendererDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestTextRendererDataConverter::testInitialize()
  {
    TextRendererLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<TextRendererDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(TextRendererLoadingResources::getValidNoLinesFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<TextRenderer*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Instantiate_SetsInputtedPointer_ToNewTextRendererDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    TextRendererDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<TextRendererDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    TextRendererDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsElementName_ToInput)
  {
    TextRendererDataConverter converter;

    Assert::AreEqual("TextRenderer", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsFont_ToCorrectDefault)
  {
    TextRendererDataConverter converter;

    Assert::AreEqual(Path("Fonts", "Arial.ttf"), converter.getFont());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsFontHeight_ToTwelve)
  {
    TextRendererDataConverter converter;

    Assert::AreEqual(12.0f, converter.getFontHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsHorizontalAlignment_TokCentre)
  {
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsVerticalAlignment_TokCentre)
  {
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsColour_ToWhite)
  {
    TextRendererDataConverter converter;

    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsOpacity_ToOne)
  {
    TextRendererDataConverter converter;

    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsRawText_ToEmptyString)
  {
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getRawText().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_SetsParsedText_ToEmptyString)
  {
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getParsedText().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsFontAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::FONT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsFontHeightAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::FONT_HEIGHT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsHorizontalAlignmentAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsVerticalAlignmentAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsColourAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::COLOUR_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsOpacityAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::OPACITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_Constructor_AddsTextAttribute)
  {
    const MockTextRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(TextRendererDataConverter::TEXT_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    TextRendererDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    TextRendererDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    TextRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(TextRendererLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    TextRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(TextRendererLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    TextRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(TextRendererLoadingResources::getValidNoLinesFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    TextRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(TextRendererLoadingResources::getValidNoLinesFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Font Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoFontAttribute_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;

    Assert::AreEqual(Path("Fonts", "Arial.ttf"), converter.getFont());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(Path("Fonts", "Arial.ttf"), converter.getFont());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_FontAttribute_NoText_DoesNothing_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    element->SetAttribute(TextRendererDataConverter::FONT_ATTRIBUTE_NAME, "");

    Assert::AreEqual(Path("Fonts", "Arial.ttf"), converter.getFont());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("", converter.getFont().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_FontAttribute_SetsFontToText_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    element->SetAttribute(TextRendererDataConverter::FONT_ATTRIBUTE_NAME, Path("Test", "Path.ttf").c_str());

    Assert::AreEqual(Path("Fonts", "Arial.ttf"), converter.getFont());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(Path("Test", "Path.ttf"), converter.getFont());
  }

#pragma endregion

#pragma region Convert Font Height Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoFontHeightAttribute_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;

    Assert::AreEqual(12.0f, converter.getFontHeight());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(12.0f, converter.getFontHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_FontHeightAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::FONT_HEIGHT_ATTRIBUTE_NAME, "whahdiuwa");

    Assert::AreEqual(12.0f, converter.getFontHeight());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(12.0f, converter.getFontHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_FontHeightAttribute_ValidText_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::FONT_HEIGHT_ATTRIBUTE_NAME, 20);

    Assert::AreEqual(12.0f, converter.getFontHeight());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(20.0f, converter.getFontHeight());
  }

#pragma endregion

#pragma region Convert Horizontal Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoHorizontalAlignmentAttribute_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_HorizontalAlignmentAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, "whahdiuwa");

    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_HorizontalAlignmentAttribute_ValidText_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, "left");

    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHorizontalAlignment() == HorizontalAlignment::kLeft);
  }

#pragma endregion

#pragma region Convert Vertical Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoVerticalAlignmentAttribute_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;

    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_VerticalAlignmentAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, "whahdiuwa");

    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_VerticalAlignmentAttribute_ValidText_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    TextRendererDataConverter converter;
    element->SetAttribute(TextRendererDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, "top");

    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kCentre);
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getVerticalAlignment() == VerticalAlignment::kTop);
  }

#pragma endregion

#pragma region Convert Colour Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoColourAttribute_DoesNothing_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_ColourAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(TextRendererDataConverter::COLOUR_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_ColourAttribute_SetsValuesCorrectly_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(TextRendererDataConverter::COLOUR_ATTRIBUTE_NAME, "0.2,0.1,0.6");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(0.2f, 0.1f, 0.6f), converter.getColour());
  }

#pragma endregion

#pragma region Convert Opacity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoOpacityAttribute_DoesNothing_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_OpacityAttribute_InvalidText_SetsValueToOne_AndReturnsFalse)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(TextRendererDataConverter::OPACITY_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_OpacityAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    TextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(TextRendererDataConverter::OPACITY_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getOpacity());
  }

#pragma endregion

#pragma region Convert Raw Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NoTextAttribute_DoesNothing_ReturnsTrue)
  {
    MockTextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");

    Assert::IsNull(element->Attribute(converter.TEXT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getRawText().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getRawText().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_EmptyTextAttribute_SetsTextToEmptyString)
  {
    MockTextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    element->SetAttribute(converter.TEXT_ATTRIBUTE_NAME, "");

    Assert::AreEqual("", element->Attribute(converter.TEXT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getRawText().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getRawText().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_ConvertFromXML_NonEmptyTextAttribute_SetsTextToCorrectValue)
  {
    MockTextRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextRenderer");
    element->SetAttribute(converter.TEXT_ATTRIBUTE_NAME, "Text 1\\Text 2");

    Assert::AreEqual("Text 1\\Text 2", element->Attribute(converter.TEXT_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getRawText().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("Text 1\\Text 2", converter.getRawText().c_str());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_SetValues_InputtingTextRenderer_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    TextRenderer renderer(gameObject);
    renderer.setColour(0.1f, 0.2f, 0.3f, 0.4f);
    renderer.setHorizontalAlignment(HorizontalAlignment::kLeft);

    TextRendererDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(renderer);

    Assert::IsTrue(renderer.getHorizontalAlignment() == HorizontalAlignment::kLeft);
    Assert::AreEqual(glm::vec4(0.1f, 0.2f, 0.3f, 0.4f), renderer.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_SetValues_InputtingTextRenderer_DataLoadedCorrectly_ChangesTextRendererToMatchData)
  {
    GameObject gameObject;
    TextRenderer renderer(gameObject);
    renderer.setColour(0.1f, 0.2f, 0.3f, 0.4f);
    renderer.setHorizontalAlignment(HorizontalAlignment::kLeft);

    TextRendererDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(TextRendererLoadingResources::getValidNoLinesFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(renderer);

    Assert::AreEqual(internString(Path(getResourcesDirectory(), "Fonts", "Arial.ttf").as_string()), renderer.getFont().getFontName());
    Assert::AreEqual(20.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec4(1), renderer.getColour());
    Assert::IsTrue(renderer.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(renderer.getVerticalAlignment() == VerticalAlignment::kTop);
    Assert::AreEqual("", renderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_SetValues_InputtingTextRenderer_DataLoadedCorrectlyWithLines_ChangesTextRendererToMatchData)
  {
    GameObject gameObject;
    TextRenderer renderer(gameObject);
    TextRendererDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(TextRendererLoadingResources::getValidWithLinesFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(renderer);

    Assert::AreEqual(internString(Path(getResourcesDirectory(), "Fonts", "Arial.ttf").as_string()), renderer.getFont().getFontName());
    Assert::AreEqual(20.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec4(1), renderer.getColour());
    Assert::IsTrue(renderer.getHorizontalAlignment() == HorizontalAlignment::kCentre);
    Assert::IsTrue(renderer.getVerticalAlignment() == VerticalAlignment::kTop);
    Assert::AreEqual("Line 1\nLine 2", renderer.getText().c_str());
  }

#pragma endregion

#pragma region Get Parsed Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToEmptyString_ReturnsEmptyString)
  {
    MockTextRendererDataConverter converter;

    Assert::IsTrue(converter.getRawText().empty());
    Assert::IsTrue(converter.getParsedText().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToSingleLineString_ReturnsSameString)
  {
    MockTextRendererDataConverter converter;
    converter.setRawText("Test");

    Assert::AreEqual("Test", converter.getRawText().c_str());
    Assert::AreEqual("Test", converter.getParsedText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToSingleLineString_EndingInBackslash_ReturnsSameString)
  {
    MockTextRendererDataConverter converter;
    converter.setRawText("Test\\");

    Assert::AreEqual("Test\\", converter.getRawText().c_str());
    Assert::AreEqual("Test\\", converter.getParsedText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToMultipleLineString_ReturnsCorrectString)
  {
    MockTextRendererDataConverter converter;
    converter.setRawText("Test\\nTest2");

    Assert::AreEqual("Test\\nTest2", converter.getRawText().c_str());
    Assert::AreEqual("Test\nTest2", converter.getParsedText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToMultipleLineString_EndingInBackslash_ReturnsCorrectString)
  {
    MockTextRendererDataConverter converter;
    converter.setRawText("Test\\nTest2\\");

    Assert::AreEqual("Test\\nTest2\\", converter.getRawText().c_str());
    Assert::AreEqual("Test\nTest2\\", converter.getParsedText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRendererDataConverter_GetParsedText_RawTextSetToMultipleLineString_EndingInNewLine_ReturnsCorrectString)
  {
    MockTextRendererDataConverter converter;
    converter.setRawText("Test\\nTest2\\n");

    Assert::AreEqual("Test\\nTest2\\n", converter.getRawText().c_str());
    Assert::AreEqual("Test\nTest2\n", converter.getParsedText().c_str());
  }

#pragma endregion

  };
}