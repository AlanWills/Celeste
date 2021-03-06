#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/UI/MockButtonDataConverter.h"
#include "TestResources/UI/ButtonLoadingResources.h"
#include "Input/MouseInteractionHandler.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "UI/Button.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "TestUtils/AssertSpecialization/FileSystem.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;
using namespace Celeste::Physics;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestButtonDataConverter)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<ButtonDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    gameObject.addComponent<Rendering::SpriteRenderer>();
    gameObject.addComponent<RectangleCollider>();
    gameObject.addComponent<MouseInteractionHandler>();

    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidNoCallbacksFullPath());
    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Button*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Instantiate_SetsInputtedPointer_ToNewButtonDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    ButtonDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<ButtonDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ButtonDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsElementName_ToInput)
  {
    ButtonDataConverter converter;

    Assert::AreEqual("Button", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsIdleTexturePath_ToEmptyPath)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsHighlightedTexturePath_ToEmptyPath)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsClickedTexturePath_ToEmptyPath)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsHighlightedSoundPath_ToEmptyPath)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsClickedSoundPath_ToEmptyPath)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsIdleTexturePathAttribute)
  {
    const MockButtonDataConverter converter;
    
    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsHighlightedTexturePathAttribute)
  {
    const MockButtonDataConverter converter;

    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsClickedTexturePathAttribute)
  {
    const MockButtonDataConverter converter;

    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsHighlightedSoundPathAttribute)
  {
    const MockButtonDataConverter converter;

    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsClickedSoundPathAttribute)
  {
    const MockButtonDataConverter converter;

    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    ButtonDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ButtonDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    ButtonDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ButtonDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    ButtonDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidNoCallbacksFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    ButtonDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidNoCallbacksFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Idle Texture Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoIdleTexturePathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_DefaultTexturePathAttribute_EmptyText_SetsDefaultTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_DefaultTexturePathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME, "TexturePath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getIdleTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("TexturePath.png", converter.getIdleTexturePath().c_str());
  }

#pragma endregion

#pragma region Convert Highlighted Texture Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoHighlightedTexturePathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedTexturePathAttribute_EmptyText_SetsHighlightedTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedTexturePathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME, "TexturePath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("TexturePath.png", converter.getHighlightedTexturePath().c_str());
  }

#pragma endregion

#pragma region Convert Clicked Texture Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoClickedTexturePathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedTexturePathAttribute_EmptyText_SetsClickedTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedTexturePathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME, "TexturePath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedTexturePath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("TexturePath.png", converter.getClickedTexturePath().c_str());
  }

#pragma endregion

#pragma region Convert Highlighted Sound Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoHighlightedSoundPathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedSoundPathAttribute_EmptyText_SetsHighlightedSoundPathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedSoundPathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME, "SoundPath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getHighlightedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("SoundPath.png", converter.getHighlightedSoundPath().c_str());
  }

#pragma endregion

#pragma region Convert Clicked Sound Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoClickedSoundPathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedSoundPathAttribute_EmptyText_SetsClickedSoundPathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedSoundPathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME, "SoundPath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getClickedSoundPath().as_string().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("SoundPath.png", converter.getClickedSoundPath().c_str());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_SetValues_InputtingButton_DataNotLoadedCorrectly_DoesNothing)
  {
    GameObject gameObject;
    gameObject.addComponent<Rendering::SpriteRenderer>();
    gameObject.addComponent<RectangleCollider>();
    gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<Button> button = gameObject.addComponent<Button>();

    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getInvalidFullPath());

    ButtonDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(*button);

    AssertCel::IsActive(*button);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_SetValues_InputtingButton_DataLoadedCorrectly_ChangesButtonToMatchData)
  {
    GameObject gameObject;
    gameObject.addComponent<Rendering::SpriteRenderer>();
    gameObject.addComponent<RectangleCollider>();
    gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<Button> button = gameObject.addComponent<Button>();
    button->setActive(false);

    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidWithCallbacksFullPath());

    ButtonDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(*button);

    AssertCel::IsActive(*button);
    Assert::IsNotNull(button->getIdleTexture());
    Assert::IsNotNull(button->getHighlightedTexture());
    Assert::IsNotNull(button->getClickedTexture());
    Assert::IsNotNull(button->getHighlightedSound());
    Assert::IsNotNull(button->getClickedSound());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getIdleTexturePath()) == button->getIdleTexture());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getHighlightedTexturePath()) == button->getHighlightedTexture());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getClickedTexturePath()) == button->getClickedTexture());
    Assert::IsTrue(getResourceManager().load<Sound>(converter.getHighlightedSoundPath()) == button->getHighlightedSound());
    Assert::IsTrue(getResourceManager().load<Sound>(converter.getClickedSoundPath()) == button->getClickedSound());
  }

#pragma endregion

  };
}