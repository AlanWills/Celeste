#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Screens/MockScreenDataConverter.h"
#include "Resources/Screens/ScreenLoadingResources.h"
#include "Resources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Screens/Screen.h"
#include "Objects/GameObject.h"
#include "Utils/GameObjectXMLUtils.h"
#include "Utils/ScreenXMLUtils.h"
#include "AssertCel.h"

#include <numeric>

using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreenDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestScreenDataConverter::testCleanup()
  {
    ScreenLoadingResources::unloadAllResources();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ScreenDataConverter converter("Test");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsElementName_ToInput)
  {
    ScreenDataConverter converter("Test");

    Assert::AreEqual("Test", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getIsActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsName_ToEmptyString)
  {
    ScreenDataConverter converter("Test");

    Assert::AreEqual("", converter.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableFonts_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableVertexShaders_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableFragmentShaders_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableData_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableSounds_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableTextures_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_ToEmptyVector)
  {
    ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsNameAttribute)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsNameAttribute_ToRequired)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsTrue(converter.findAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME)->isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableFontsElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableVertexShadersElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableFragmentShadersElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableDataElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableSoundsElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableTexturesElement)
  {
    const ScreenDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_ToEmptyList)
  {
    const ScreenDataConverter converter("GameObject");

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsGameObjectsElement)
  {
    const ScreenDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_To_kNotRequired)
  {
    const ScreenDataConverter converter("GameObject");

    Assert::IsFalse(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    ScreenDataConverter converter("Test");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingNullptr_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ScreenDataConverter converter("Test");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    ScreenDataConverter converter("Test");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, "adhiashdiad");
    
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ScreenDataConverter converter("Test");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, "adhiashdiad");
    converter.convertFromXML(element);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "adhiashdiad");
    
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "adhiashdiad");
    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoNameAttribute_ReturnsFalse)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Test");
    converter.convertFromXML(element);

    Assert::IsNull(element->FindAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoNameAttribute_SetsNameToEmptyString)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    const XMLElement* element = document.NewElement("Test");
    converter.convertFromXML(element);

    Assert::IsNull(element->FindAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNameAttribute_SetToEmptyString_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "");
    converter.convertFromXML(element);

    Assert::AreEqual("", element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNameAttribute_SetToEmptyString_SetsNameToEmptyString)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "");
    converter.convertFromXML(element);

    Assert::AreEqual("", element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("", converter.getName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNameAttribute_SetToNonEmptyString_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "WubbaLubbaDubDub");
    converter.convertFromXML(element);

    Assert::AreEqual("WubbaLubbaDubDub", element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNameAttribute_SetToNonEmptyString_SetsNameToSameString)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "WubbaLubbaDubDub");
    converter.convertFromXML(element);

    Assert::AreEqual("WubbaLubbaDubDub", element->Attribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", converter.getName().c_str());
  }

#pragma endregion

#pragma region Convert Preloadable Fonts Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableFontsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFontsElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFontsElement_SetsPreloadableFontsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontsElement_NoFontElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontsElement_NoFontElement_SetsPreloadableFontsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    
    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNotNull(fonts->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontElements_AddsElementTextToPreloadableFontsList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);
    font->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNotNull(fonts->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", font->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableFonts().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableFonts()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingFontsElement_OnlyGetsElementTextFromFontElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement("_Font");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);
    font->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", font->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Vertex Shaders Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableVertexShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoVertexShadersElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoVertexShadersElement_SetsPreloadableVertexShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShadersElement_NoVertexShaderElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShadersElement_NoVertexShaderElement_SetsPreloadableVertexShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShaderElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShaderElements_AddsElementTextToPreloadableVertexShadersList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableVertexShaders().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableVertexShaders()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingVertexShadersElement_OnlyGetsElementTextFromVertexShaderElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement("_Shader");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Fragment Shaders Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFragmentShadersElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFragmentShadersElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShadersElement_NoFragmentShaderElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShadersElement_NoFragmentShaderElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShaderElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShaderElements_AddsElementTextToPreloadableFragmentShadersList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableFragmentShaders().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableFragmentShaders()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingFragmentShadersElement_OnlyGetsElementTextFromFragmentShaderElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement("_Shader");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Datas Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableDataToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoDataElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoDataElement_SetsPreloadableDataToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElement_NoDataElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* data = document.NewElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(data->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElement_NoDataElement_SetsPreloadableDataToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* data = document.NewElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(data->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNotNull(datas->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElements_AddsElementTextToPreloadableDataList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);
    data->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNotNull(datas->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", data->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableData().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableData()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingDataElement_OnlyGetsElementTextFromDataElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement("_Shader");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);
    data->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(datas->FirstChildElement(ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", data->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Sounds Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableSoundsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoSoundsElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoSoundsElement_SetsPreloadableSoundsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundsElement_NoSoundElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundsElement_NoSoundElement_SetsPreloadableSoundsToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNotNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundElements_AddsElementTextToPreloadableSoundsList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);
    sound->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNotNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", sound->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableSounds().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableSounds()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingSoundsElement_OnlyGetsElementTextFromSoundElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement("_Sound");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);
    sound->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", sound->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Textures Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableTexturesToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoTexturesElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoTexturesElement_SetsPreloadableTexturesToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTexturesElement_NoTextureElement_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNull(textures->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTexturesElement_NoTextureElement_SetsPreloadableTexturesToEmptyList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTextureElements_ReturnsTrue)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNotNull(textures->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTextureElements_AddsElementTextToPreloadableTexturesList)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME);
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);
    texture->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNotNull(textures->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", texture->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableTextures().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableTextures()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingTexturesElement_OnlyGetsElementTextFromTextureElements)
  {
    ScreenDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement("_Texture");
    element->SetAttribute(ScreenDataConverter::NAME_ATTRIBUTE_NAME, "Name");
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);
    texture->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNull(textures->FirstChildElement(ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", texture->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

#pragma endregion

#pragma region Convert GameObjects Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoGameObjectsElement_DoesNothing)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoGameObjectsElement_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoChildElements_DoesNothing)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoChildElements_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);

    Assert::IsNull(gameObjects->FirstChildElement());
    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma region Game Object Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidGameObjectElement_DoesNothing)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, gameObjects);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidGameObjectElement_ReturnsFalse)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, gameObjects);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidGameObjectElement_AddsGameObjectDataConverter)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidGameObjectElement_SetsGameObjectDataConverterDataCorrectly)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createGameObjectElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    gameObject->SetAttribute(GameObjectDataConverter::TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getGameObjects().size());

    const GameObjectDataConverter& childConverter = *converter.getGameObjects()[0];

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual("UI", childConverter.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidGameObjectElement_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AtLeastOneInvalid_DoesNotAddAnyGameObjectDataConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AtLeastOneInvalid_ReturnsFalse)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AllValid_AddsGameObjectDataConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AllValid_SetsGameObjectDataConverterDataCorrectly)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child1", gameObjects);
    gameObject->SetAttribute(GameObjectDataConverter::TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);
    gameObject2->SetAttribute(GameObjectDataConverter::TAG_ATTRIBUTE_NAME, "World");
    gameObject2->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "4, 5, 6");

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());

    const GameObjectDataConverter& childConverter1 = *converter.getGameObjects()[0];

    Assert::AreEqual("Child1", childConverter1.getName().c_str());
    Assert::AreEqual("UI", childConverter1.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), childConverter1.getPosition());

    const GameObjectDataConverter& childConverter2 = *converter.getGameObjects()[1];

    Assert::AreEqual("Child2", childConverter2.getName().c_str());
    Assert::AreEqual("World", childConverter2.getTag().c_str());
    Assert::AreEqual(glm::vec3(4, 5, 6), childConverter2.getPosition());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AllValid_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Prefab Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidPrefabElement_DoesNothing)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, gameObjects);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidPrefabElement_ReturnsFalse)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, gameObjects);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidPrefabElement_AddsPrefabDataConverter)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getGameObjects().size());
    Assert::IsNotNull(dynamic_cast<PrefabDataConverter*>(converter.getGameObjects()[0]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidPrefabElement_SetsPrefabDataConverterDataCorrectly)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getGameObjects().size());

    const PrefabDataConverter& childConverter = static_cast<const PrefabDataConverter&>(*converter.getGameObjects()[0]);

    Assert::AreEqual("Child", childConverter.getName().c_str());
    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidPrefabElement_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AtLeastOneInvalid_DoesNotAddAnyPrefabDataConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AtLeastOneInvalid_ReturnsFalse)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AllValid_AddsPrefabDataConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getGameObjects()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AllValid_SetsPrefabDataConverterDataCorrectly)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());

    const PrefabDataConverter& childConverter1 = static_cast<const PrefabDataConverter&>(*converter.getGameObjects()[0]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter1.getPath().c_str());

    const PrefabDataConverter& childConverter2 = static_cast<const PrefabDataConverter&>(*converter.getGameObjects()[1]);

    Assert::AreEqual(PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str(), childConverter2.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AllValid_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    tinyxml2::XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_OneInvalid_DoesNotAddAnyConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_OneInvalid_ReturnsFalse)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_AddsConverters)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::AreEqual("Test", element->Attribute("name"));
    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(converter.getGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getGameObjects()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_ReturnsTrue)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_SetsConverterDataCorrectly)
  {
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = createScreenElement(document, "Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, "Child", gameObjects);
    gameObject->SetAttribute(GameObjectDataConverter::TAG_ATTRIBUTE_NAME, "UI");
    gameObject->SetAttribute(GameObjectDataConverter::POSITION_ATTRIBUTE_NAME, "1, 2, 3");
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(converter.getGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getGameObjects()[1]));

    const GameObjectDataConverter& gameObjectConverter = *converter.getGameObjects()[0];

    Assert::AreEqual("Child", gameObjectConverter.getName().c_str());
    Assert::AreEqual("UI", gameObjectConverter.getTag().c_str());
    Assert::AreEqual(glm::vec3(1, 2, 3), gameObjectConverter.getPosition());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_InputtingNullScreenHandle_DoesNothing)
  {
    ScreenDataConverter converter("Screen");
    converter.convertFromXML(getResourceManager().load<Data>(ScreenLoadingResources::getGameObjectsElementFullPath())->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
    
    converter.setValues(Screen());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_DataNotLoadedCorrectly_DoesNothing)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    converter.convertFromXML(getResourceManager().load<Data>(ScreenLoadingResources::getGameObjectsElementWithBadElementsFullPath())->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(screen);

    Assert::IsNull(screen.findGameObject([](const GameObject&) -> bool { return true; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_NoGameObjectElements_DoesNotAddChildren)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);
    
    Assert::IsTrue(converter.getGameObjects().empty());
    Assert::AreEqual(static_cast<size_t>(0), screen.getScreenRoot().getChildCount());
  }

#pragma region GameObject Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_GameObjects_InstantiatesGameObjectsCorrectly)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObject1 = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::AreEqual(internString("Child1"), screen.getScreenRoot().getChildGameObject(0)->getName());
    Assert::AreEqual(internString("Child2"), screen.getScreenRoot().getChildGameObject(1)->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_GameObjects_ParentedToScreenRoot)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObject1 = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* gameObject2 = createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(0)->getParentTransform());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(1)->getParentTransform());
  }

#pragma endregion

#pragma region Prefab Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_Prefabs_InstantiatesPrefabsCorrectly)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::AreEqual(internString("GameObject1"), screen.getScreenRoot().getChildGameObject(0)->getName());
    Assert::AreEqual(internString("GameObject1"), screen.getScreenRoot().getChildGameObject(1)->getName());
    Assert::AreNotEqual(screen.getScreenRoot().getChildGameObject(0), screen.getScreenRoot().getChildGameObject(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_Prefabs_ParentedToScreenRoot)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(0)->getParentTransform());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(1)->getParentTransform());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_GameObjectsAndPrefabs_InstantiatesCorrectly)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createScreenElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObjectElement = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::AreEqual(internString("Child1"), screen.getScreenRoot().getChildGameObject(0)->getName());
    Assert::AreEqual(internString("GameObject1"), screen.getScreenRoot().getChildGameObject(1)->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_SetValues_GameObjectsAndPrefabs_ParentedToScreenRoot)
  {
    Screen screen;
    ScreenDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* gameObjectElement = createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    converter.setValues(screen);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), screen.getScreenRoot().getChildCount());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(0)->getParentTransform());
    Assert::IsTrue(&screen.getScreenRoot() == screen.getScreenRoot().getChildGameObject(1)->getParentTransform());
  }

#pragma endregion

  };
}