#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/UI/MockButtonDataConverter.h"
#include "Screens/Screen.h"
#include "Resources/UI/ButtonLoadingResources.h"
#include "Input/MouseInteractionHandler.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "UI/Button.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "AssertSpecialization/FileSystem.h"
#include "AssertCel.h"

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
    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<Rendering::SpriteRenderer> renderer = gameObject->addComponent<Rendering::SpriteRenderer>();
    AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject->addComponent<MouseInteractionHandler>();
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidNoCallbacksFullPath());
    AutoDeallocator<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), *gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<Button*>(component.get()));
    Assert::AreEqual(gameObject.get(), component->getGameObject());
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
  TEST_METHOD(ButtonDataConverter_Constructor_SetsDefaultTexturePath_ToDefaultTextureDefaultPath)
  {
    ButtonDataConverter converter;

    Assert::AreEqual(ButtonDataConverter::getDefaultTextureDefaultPath(), converter.getDefaultTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsHighlightedTexturePath_ToHighlightedTextureDefaultPath)
  {
    ButtonDataConverter converter;

    Assert::AreEqual(ButtonDataConverter::getHighlightedTextureDefaultPath(), converter.getHighlightedTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsClickedTexturePath_ToClickedTextureDefaultPath)
  {
    ButtonDataConverter converter;

    Assert::AreEqual(ButtonDataConverter::getClickedTextureDefaultPath(), converter.getClickedTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsHighlightedSoundPath_ToHighlightedSoundDefaultPath)
  {
    ButtonDataConverter converter;

    Assert::AreEqual(ButtonDataConverter::getHighlightedSoundDefaultPath(), converter.getHighlightedSoundPath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsClickedSoundPath_ToClickedSoundDefaultPath)
  {
    ButtonDataConverter converter;

    Assert::AreEqual(ButtonDataConverter::getClickedSoundDefaultPath(), converter.getClickedSoundPath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_SetsLeftClickCallbacks_ToEmptyVector)
  {
    ButtonDataConverter converter;

    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsDefaultTexturePathAttribute)
  {
    const MockButtonDataConverter converter;
    
    Assert::IsTrue(converter.findAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME));
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

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_Constructor_AddsLeftClickCallbacksElement)
  {
    const MockButtonDataConverter converter;

    Assert::IsTrue(converter.findElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
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

#pragma region Convert Default Texture Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoDefaultTexturePathAttribute_DoesNothing_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FindAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getDefaultTextureDefaultPath(), converter.getDefaultTexturePath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(ButtonDataConverter::getDefaultTextureDefaultPath(), converter.getDefaultTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_DefaultTexturePathAttribute_EmptyText_SetsDefaultTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getDefaultTextureDefaultPath(), converter.getDefaultTexturePath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getDefaultTexturePath().as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_DefaultTexturePathAttribute_NonEmptyText_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME, "TexturePath.png");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getDefaultTextureDefaultPath(), converter.getDefaultTexturePath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("TexturePath.png", converter.getDefaultTexturePath().c_str());
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
    Assert::AreEqual(ButtonDataConverter::getHighlightedTextureDefaultPath(), converter.getHighlightedTexturePath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(ButtonDataConverter::getHighlightedTextureDefaultPath(), converter.getHighlightedTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedTexturePathAttribute_EmptyText_SetsHighlightedTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getHighlightedTextureDefaultPath(), converter.getHighlightedTexturePath());
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
    Assert::AreEqual(ButtonDataConverter::getHighlightedTextureDefaultPath(), converter.getHighlightedTexturePath());
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
    Assert::AreEqual(ButtonDataConverter::getClickedTextureDefaultPath(), converter.getClickedTexturePath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(ButtonDataConverter::getClickedTextureDefaultPath(), converter.getClickedTexturePath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedTexturePathAttribute_EmptyText_SetsClickedTexturePathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getClickedTextureDefaultPath(), converter.getClickedTexturePath());
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
    Assert::AreEqual(ButtonDataConverter::getClickedTextureDefaultPath(), converter.getClickedTexturePath());
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
    Assert::AreEqual(ButtonDataConverter::getHighlightedSoundDefaultPath(), converter.getHighlightedSoundPath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(ButtonDataConverter::getHighlightedSoundDefaultPath(), converter.getHighlightedSoundPath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_HighlightedSoundPathAttribute_EmptyText_SetsHighlightedSoundPathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getHighlightedSoundDefaultPath(), converter.getHighlightedSoundPath());
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
    Assert::AreEqual(ButtonDataConverter::getHighlightedSoundDefaultPath(), converter.getHighlightedSoundPath());
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
    Assert::AreEqual(ButtonDataConverter::getClickedSoundDefaultPath(), converter.getClickedSoundPath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(ButtonDataConverter::getClickedSoundDefaultPath(), converter.getClickedSoundPath());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_ClickedSoundPathAttribute_EmptyText_SetsClickedSoundPathToEmptyString_ReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    element->SetAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME, "");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME));
    Assert::AreEqual(ButtonDataConverter::getClickedSoundDefaultPath(), converter.getClickedSoundPath());
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
    Assert::AreEqual(ButtonDataConverter::getClickedSoundDefaultPath(), converter.getClickedSoundPath());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual("SoundPath.png", converter.getClickedSoundPath().c_str());
  }

#pragma endregion

#pragma region Convert Callbacks Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_NoCallbacksElement_DoesNothing_AndReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");

    Assert::IsNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_CallbacksElement_NoCallbackElement_DoesNothing_AndReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    XMLElement* callbacks = document.NewElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);

    Assert::IsNotNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsNull(callbacks->FirstChildElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNoNameAttribute_DoesNothing_AndReturnsFalse)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    XMLElement* callbacks = document.NewElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);

    Assert::IsNotNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNameAttribute_AddsCallback_AndReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    XMLElement* callbacks = document.NewElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");

    Assert::IsNotNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getLeftClickCallbacks().size());
    Assert::AreEqual("Test", converter.getLeftClickCallbacks()[0]->getName().c_str());
    Assert::AreEqual("", converter.getLeftClickCallbacks()[0]->getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNameAndArgsAttributes_AddsCallback_AndReturnsTrue)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    XMLElement* callbacks = document.NewElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");
    callback->SetAttribute("arg", "WubbaLubbaDubDub");

    Assert::IsNotNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getLeftClickCallbacks().size());
    Assert::AreEqual("Test", converter.getLeftClickCallbacks()[0]->getName().c_str());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getLeftClickCallbacks()[0]->getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_ConvertFromXML_CallbacksElement_OnlyConvertsCallbackElements)
  {
    ButtonDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Button");
    XMLElement* callbacks = document.NewElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME);
    XMLElement* callback2 = document.NewElement("_Callback");
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");
    callback->SetAttribute("arg", "WubbaLubbaDubDub");
    callback2->SetAttribute("name", "Test2");
    callback2->SetAttribute("arg", "RickyTickyTappy");

    Assert::IsNotNull(element->FirstChildElement(ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(ButtonDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getLeftClickCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getLeftClickCallbacks().size());
    Assert::AreEqual("Test", converter.getLeftClickCallbacks()[0]->getName().c_str());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getLeftClickCallbacks()[0]->getArg().c_str());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_SetValues_InputtingNullButton_DoesNothing)
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidNoCallbacksFullPath());

    ButtonDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    // Check doesn't throw
    converter.setValues(Button());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ButtonDataConverter_SetValues_InputtingButton_DataNotLoadedCorrectly_DoesNothing)
  {
    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<Rendering::SpriteRenderer> renderer = gameObject->addComponent<Rendering::SpriteRenderer>();
    AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject->addComponent<MouseInteractionHandler>();
    AutoDeallocator<Button> button = gameObject->addComponent<Button>();

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
    Screen screen;
    AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
    AutoDeallocator<Rendering::SpriteRenderer> renderer = gameObject->addComponent<Rendering::SpriteRenderer>();
    AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
    AutoDeallocator<MouseInteractionHandler> mouseInteractionHandler = gameObject->addComponent<MouseInteractionHandler>();
    AutoDeallocator<Button> button = gameObject->addComponent<Button>();
    button->setActive(false);

    observer_ptr<Data> data = getResourceManager().load<Data>(ButtonLoadingResources::getValidWithCallbacksFullPath());

    ButtonDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(*button);

    AssertCel::IsActive(*button);
    Assert::IsNotNull(button->getDefaultTexture());
    Assert::IsNotNull(button->getHighlightedTexture());
    Assert::IsNotNull(button->getClickedTexture());
    Assert::IsNotNull(button->getHighlightedSound());
    Assert::IsNotNull(button->getClickedSound());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getDefaultTexturePath()) == button->getDefaultTexture());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getHighlightedTexturePath()) == button->getHighlightedTexture());
    Assert::IsTrue(getResourceManager().load<Texture2D>(converter.getClickedTexturePath()) == button->getClickedTexture());
    Assert::IsTrue(getResourceManager().load<Sound>(converter.getHighlightedSoundPath()) == button->getHighlightedSound());
    Assert::IsTrue(getResourceManager().load<Sound>(converter.getClickedSoundPath()) == button->getClickedSound());
  }

#pragma endregion

  };
}