#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Rendering/MockSpriteRendererDataConverter.h"
#include "TestResources/Rendering/SpriteRendererLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Scene/SceneUtils.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSpriteRendererDataConverter)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    SpriteRendererLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<SpriteRendererDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(SpriteRendererLoadingResources::getValidFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<SpriteRenderer*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Instantiate_SetsInputtedPointer_ToNewSpriteRendererDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    SpriteRendererDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<SpriteRendererDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SpriteRendererDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    SpriteRendererDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsElementName_ToInput)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual("SpriteRenderer", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsSprite_ToEmptyPath)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual("", converter.getSprite().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsSize_ToZero)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual(glm::vec2(), converter.getSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsColour_ToWhite)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsOpacity_ToOne)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsPreserveAspectRatio_ToFalse)
  {
    SpriteRendererDataConverter converter;

    Assert::IsFalse(converter.getPreserveAspectRatio());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsScissorRectangleDimensions_ToZeroVector)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsScissorRectangleCentre_ToZeroVector)
  {
    SpriteRendererDataConverter converter;

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsSpriteAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsSizeAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::SIZE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsColourAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::COLOUR_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsOpacityAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::OPACITY_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsPreserveAspectRatioAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsScissorRectangleDimensionsAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_AddsScissorRectangleCentreAttribute)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsSpriteAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsSizeAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::SIZE_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsColourAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::COLOUR_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsOpacityAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::OPACITY_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsPreserveAspectRatioAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsScissorRectangleDimensionsAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_Constructor_SetsScissorRectangleCentreAttribute_TokNotRequired)
  {
    const MockSpriteRendererDataConverter converter;

    Assert::IsFalse(converter.findAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    SpriteRendererDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SpriteRendererDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SpriteRendererLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SpriteRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SpriteRendererLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SpriteRendererLoadingResources::getValidFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    SpriteRendererDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(SpriteRendererLoadingResources::getValidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Sprite Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoSpriteAttribute_DoesNothing_ReturnsTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    SpriteRendererDataConverter converter;

    Assert::IsTrue(converter.getSprite().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSprite().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_SpriteAttribute_NoText_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME, "");

    Assert::IsTrue(converter.getSprite().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getSprite().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_SpriteAttribute_SetsSpriteToText_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME, "Test\\Path.xml");

    Assert::IsTrue(converter.getSprite().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("Test\\Path.xml", converter.getSprite().c_str());
  }

#pragma endregion

#pragma region Convert Size Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoSizeAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(glm::vec2(), converter.getSize());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_SizeAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SIZE_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(glm::vec2(), converter.getSize());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_SizeAttribute_SetsValuesCorrectly_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SIZE_ATTRIBUTE_NAME, "200, 300");

    Assert::AreEqual(glm::vec2(), converter.getSize());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(200, 300), converter.getSize());
  }

#pragma endregion

#pragma region Convert Colour Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoColourAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ColourAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::COLOUR_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(1), converter.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ColourAttribute_SetsValuesCorrectly_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::COLOUR_ATTRIBUTE_NAME, "0.2,0.1,0.6");

    Assert::AreEqual(glm::vec3(1), converter.getColour());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec3(0.2f, 0.1f, 0.6f), converter.getColour());
  }

#pragma endregion

#pragma region Convert Opacity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoOpacityAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_OpacityAttribute_InvalidText_SetsValueToOne_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::OPACITY_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(1.0f, converter.getOpacity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_OpacityAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::OPACITY_ATTRIBUTE_NAME, "0.2");

    Assert::AreEqual(1.0f, converter.getOpacity());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.2f, converter.getOpacity());
  }

#pragma endregion

#pragma region Convert Preserve Aspect Ratio Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoPreserveAspectRatioAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::IsFalse(converter.getPreserveAspectRatio());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getPreserveAspectRatio());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_PreserveAspectRatioAttribute_InvalidText_SetsValueToFalse_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME, "WubDubDub");

    Assert::IsFalse(converter.getPreserveAspectRatio());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsFalse(converter.getPreserveAspectRatio());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_PreserveAspectRatioAttribute_ValidText_SetsValueToText_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME, true);

    Assert::IsFalse(converter.getPreserveAspectRatio());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getPreserveAspectRatio());
  }

#pragma endregion

#pragma region Convert Scissor Rectangle Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoScissorRectangleDimensionsAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ScissorRectangleDimensionsAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ScissorRectangleDimensionsAttribute_SetsValuesCorrectly_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME, "200, 300");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleDimensions());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(200, 300), converter.getScissorRectangleDimensions());
  }

#pragma endregion

#pragma region Convert Scissor Rectangle Centre Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_NoScissorRectangleCentreAttribute_DoesNothing_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ScissorRectangleCentreAttribute_InvalidText_DoesNothing_AndReturnsFalse)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME, "WubDubDub");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_ConvertFromXML_ScissorRectangleCentreAttribute_SetsValuesCorrectly_AndReturnsTrue)
  {
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME, "200, 300");

    Assert::AreEqual(glm::vec2(), converter.getScissorRectangleCentre());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(glm::vec2(200, 300), converter.getScissorRectangleCentre());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_SetValues_InputtingSpriteRenderer_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    SpriteRenderer renderer(gameObject);
    renderer.shouldPreserveAspectRatio(RatioMode::kPreserveAspectRatio);
    renderer.setColour(0.1f, 0.2f, 0.3f, 0.4f);

    SpriteRendererDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(renderer);

    Assert::IsTrue(renderer.isPreservingAspectRatio());
    Assert::AreEqual(glm::vec4(0.1f, 0.2f, 0.3f, 0.4f), renderer.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_SetValues_InputtingSpriteRenderer_DataLoadedCorrectly_ChangesSpriteRendererToMatchData)
  {
    GameObject gameObject;
    SpriteRenderer renderer(gameObject);
    renderer.shouldPreserveAspectRatio(RatioMode::kPreserveAspectRatio);
    renderer.setColour(0.1f, 0.2f, 0.3f, 0.4f);

    // Valid.xml
    // <SpriteRenderer sprite = "block.png" size = "50,20" colour = "0.1%,0.2%,1%" opacity = "0.5" preserve_aspect_ratio = "true"
                    // scissor_rectangle_dimensions = "10,15"
                    // scissor_rectangle_centre = "-5,1" />

    SpriteRendererDataConverter converter;
    converter.convertFromXML(getResourceManager().load<Data>(SpriteRendererLoadingResources::getValidFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(renderer);

    Assert::IsTrue(getResourceManager().load<Texture2D>(Path("Textures", "block.png")) == renderer.getTexture());
    Assert::AreEqual(glm::vec2(20, 20), renderer.getDimensions());  // We are preserving aspect ratio remember
    Assert::AreEqual(glm::vec4(0.1f, 0.2f, 1, 0.5f), renderer.getColour());
    Assert::AreEqual(0.5f, renderer.getOpacity());
    Assert::IsTrue(renderer.isPreservingAspectRatio());
    Assert::AreEqual(glm::vec2(10, 15), renderer.getScissorRectangle().getDimensions());
    Assert::AreEqual(glm::vec2(-5, 1), renderer.getScissorRectangle().getCentre());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRendererDataConverter_SetValues_SizeNotSet_SetsSizeToTextureDimensions)
  {
    GameObject gameObject;
    SpriteRenderer renderer(gameObject);
    SpriteRendererDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("SpriteRenderer");
    element->SetAttribute(SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME, TestResources::getBlockPngRelativePath().c_str());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
    Assert::AreEqual(glm::vec2(), renderer.getDimensions());

    converter.setValues(renderer);

    Assert::IsNotNull(renderer.getTexture());
    Assert::AreEqual(renderer.getTexture()->getDimensions(), renderer.getDimensions());
  }

#pragma endregion

  };
}