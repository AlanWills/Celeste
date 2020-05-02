#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "DataConverters/Scene/SceneDataConverter.h"
#include "TestResources/Scene/SceneLoadingResources.h"
#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Objects/GameObject.h"
#include "TestUtils/Utils/GameObjectXMLUtils.h"
#include "Scene/SceneManager.h"
#include "TestUtils/Assert/AssertCel.h"

#include <numeric>

using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreenDataConverter)

  class AutoDestroyer
  {
    public:
      AutoDestroyer(const std::vector<GameObject*>& gameObjects) :
        m_gameObjects()
      {
        for (GameObject* gameObject : gameObjects)
        {
          m_gameObjects.emplace_back(gameObject);
        }
      }

      std::vector<std::unique_ptr<GameObject>> m_gameObjects;
  };

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    SceneLoadingResources::unloadAllResources();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SceneDataConverter converter("Test");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsElementName_ToInput)
  {
    SceneDataConverter converter("Test");

    Assert::AreEqual("Test", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableFonts_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableVertexShaders_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableFragmentShaders_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableData_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableSounds_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsPreloadableTextures_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_ToEmptyVector)
  {
    SceneDataConverter converter("Test");

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableFontsElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableVertexShadersElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableFragmentShadersElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableDataElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableSoundsElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsPreloadableTexturesElement)
  {
    const SceneDataConverter converter("Test");

    Assert::IsNotNull(converter.findElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_ToEmptyList)
  {
    const SceneDataConverter converter("GameObject");

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_AddsGameObjectsElement)
  {
    const SceneDataConverter converter("GameObject");

    Assert::IsNotNull(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Constructor_SetsGameObjects_To_kNotRequired)
  {
    const SceneDataConverter converter("GameObject");

    Assert::IsFalse(converter.findElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME)->isRequired());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    SceneDataConverter converter("Test");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingNullptr_SetsIsDataLoadedCorrectly_ToFalse)
  {
    SceneDataConverter converter("Test");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    // Cannot create invalid XML but we leave this test to show we've considered the case
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    // Cannot create invalid XML but we leave this test to show we've considered the case
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Preloadable Fonts Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableFontsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFontsElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFontsElement_SetsPreloadableFontsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontsElement_NoFontElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontsElement_NoFontElement_SetsPreloadableFontsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    
    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNotNull(fonts->FirstChildElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFontElements_AddsElementTextToPreloadableFontsList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);
    font->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNotNull(fonts->FirstChildElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", font->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableFonts().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableFonts()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingFontsElement_OnlyGetsElementTextFromFontElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* fonts = document.NewElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME);
    XMLElement* font = document.NewElement("_Font");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(fonts);
    fonts->InsertFirstChild(font);
    font->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME));
    Assert::IsNull(fonts->FirstChildElement(SceneDataConverter::PRELOADABLE_FONT_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", font->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFonts().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Vertex Shaders Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableVertexShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoVertexShadersElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoVertexShadersElement_SetsPreloadableVertexShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShadersElement_NoVertexShaderElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShadersElement_NoVertexShaderElement_SetsPreloadableVertexShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShaderElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithVertexShaderElements_AddsElementTextToPreloadableVertexShadersList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableVertexShaders().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableVertexShaders()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingVertexShadersElement_OnlyGetsElementTextFromVertexShaderElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement("_Shader");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableVertexShaders().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Fragment Shaders Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFragmentShadersElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoFragmentShadersElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShadersElement_NoFragmentShaderElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShadersElement_NoFragmentShaderElement_SetsPreloadableFragmentShadersToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShaderElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithFragmentShaderElements_AddsElementTextToPreloadableFragmentShadersList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNotNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableFragmentShaders().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableFragmentShaders()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingFragmentShadersElement_OnlyGetsElementTextFromFragmentShaderElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* shaders = document.NewElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME);
    XMLElement* shader = document.NewElement("_Shader");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(shaders);
    shaders->InsertFirstChild(shader);
    shader->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
    Assert::IsNull(shaders->FirstChildElement(SceneDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", shader->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableFragmentShaders().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Datas Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableDataToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoDataElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoDataElement_SetsPreloadableDataToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElement_NoDataElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* data = document.NewElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(data->FirstChildElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElement_NoDataElement_SetsPreloadableDataToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* data = document.NewElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(data->FirstChildElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNotNull(datas->FirstChildElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithDataElements_AddsElementTextToPreloadableDataList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);
    data->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNotNull(datas->FirstChildElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", data->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableData().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableData()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingDataElement_OnlyGetsElementTextFromDataElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* datas = document.NewElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME);
    XMLElement* data = document.NewElement("_Shader");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(datas);
    datas->InsertFirstChild(data);
    data->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME));
    Assert::IsNull(datas->FirstChildElement(SceneDataConverter::PRELOADABLE_DATA_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", data->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Sounds Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableSoundsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoSoundsElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoSoundsElement_SetsPreloadableSoundsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundsElement_NoSoundElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundsElement_NoSoundElement_SetsPreloadableSoundsToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNotNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableData().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithSoundElements_AddsElementTextToPreloadableSoundsList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);
    sound->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNotNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", sound->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableSounds().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableSounds()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingSoundsElement_OnlyGetsElementTextFromSoundElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    XMLElement* sound = document.NewElement("_Sound");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);
    sounds->InsertFirstChild(sound);
    sound->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", sound->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

#pragma endregion

#pragma region Convert Preloadable Textures Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithNoResourcesElement_SetsPreloadableTexturesToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    
    converter.convertFromXML(element);

    Assert::IsNull(element->FirstChildElement("Resources"));
    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoTexturesElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithResourcesElement_NoTexturesElement_SetsPreloadableTexturesToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    
    element->InsertFirstChild(resources);
    converter.convertFromXML(element);

    Assert::IsNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTexturesElement_NoTextureElement_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNull(textures->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTexturesElement_NoTextureElement_SetsPreloadableTexturesToEmptyList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* sounds = document.NewElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(sounds);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME));
    Assert::IsNull(sounds->FirstChildElement(SceneDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME));

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableSounds().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTextureElements_ReturnsTrue)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNotNull(textures->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingElementWithTextureElements_AddsElementTextToPreloadableTexturesList)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME);
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);
    texture->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNotNull(textures->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", texture->GetText());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getPreloadableTextures().size());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getPreloadableTextures()[0].c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_ConvertFromXML_InputtingTexturesElement_OnlyGetsElementTextFromTextureElements)
  {
    SceneDataConverter converter("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    XMLElement* resources = document.NewElement("Resources");
    XMLElement* textures = document.NewElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME);
    XMLElement* texture = document.NewElement("_Texture");
    
    element->InsertFirstChild(resources);
    resources->InsertFirstChild(textures);
    textures->InsertFirstChild(texture);
    texture->SetText("WubbaLubbaDubDub");

    Assert::IsNotNull(resources->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME));
    Assert::IsNull(textures->FirstChildElement(SceneDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME));
    Assert::AreEqual("WubbaLubbaDubDub", texture->GetText());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPreloadableTextures().empty());
  }

#pragma endregion

#pragma region Convert GameObjects Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoGameObjectsElement_DoesNothing)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoGameObjectsElement_ReturnsTrue)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");

    Assert::IsNull(element->FirstChildElement(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoChildElements_DoesNothing)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    createGameObjectsElement(document, element);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_NoChildElements_ReturnsTrue)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);

    Assert::IsNull(gameObjects->FirstChildElement());
    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma region Game Object Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidGameObjectElement_DoesNothing)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* gameObject = createGameObjectElement(document, gameObjects);

    Assert::IsNull(gameObject->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidGameObjectElement_AddsGameObjectDataConverter)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(1), converter.getGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidGameObjectElement_SetsGameObjectDataConverterDataCorrectly)
  {
    SceneDataConverter converter("Screen");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AtLeastOneInvalid_DoesNotAddAnyGameObjectDataConverters)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createGameObjectElement(document, gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AtLeastOneInvalid_ReturnsFalse)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createGameObjectElement(document, gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AllValid_AddsGameObjectDataConverters)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultipleGameObjectElements_AllValid_SetsGameObjectDataConverterDataCorrectly)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Prefab Conversion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_InvalidPrefabElement_DoesNothing)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, gameObjects);

    Assert::IsNull(prefab->Attribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_ValidPrefabElement_AddsPrefabDataConverter)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createPrefabElement(document, "Child", PrefabLoadingResources::getValidSingleGameObjectRelativePath(), gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AtLeastOneInvalid_DoesNotAddAnyPrefabDataConverters)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createPrefabElement(document, "Child", gameObjects);
    createPrefabElement(document, gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AtLeastOneInvalid_ReturnsFalse)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createPrefabElement(document, "Child", gameObjects);
    createPrefabElement(document, gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MultiplePrefabElements_AllValid_AddsPrefabDataConverters)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createPrefabElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getGameObjects().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_OneInvalid_ReturnsFalse)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    createPrefabElement(document, "Child2", gameObjects);

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_AddsConverters)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.getGameObjects().empty());

    converter.convertFromXML(element);

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::IsNotNull(static_cast<GameObjectDataConverter*>(converter.getGameObjects()[0]));
    Assert::IsNotNull(static_cast<PrefabDataConverter*>(converter.getGameObjects()[1]));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_ReturnsTrue)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
    tinyxml2::XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child", gameObjects);
    tinyxml2::XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Convert_MixOfPrefabAndGameObjects_AllValid_SetsConverterDataCorrectly)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    tinyxml2::XMLElement* element = document.NewElement("Test");
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

#pragma region Instantiate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_DataNotLoadedCorrectly_DoesNothing)
  {
    SceneDataConverter converter("Screen");
    converter.convertFromXML(getResourceManager().load<Data>(SceneLoadingResources::getGameObjectsElementWithBadElementsFullPath())->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    // Check does not throw
    AutoDestroyer destroyer = converter.instantiate();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_NoGameObjectElements_DoesNotAddChildren)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");

    Assert::IsTrue(converter.convertFromXML(element));

    // Check does not throw
    AutoDestroyer destroyer = converter.instantiate();
  }

#pragma region GameObject Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_GameObjects_InstantiatesGameObjectsCorrectly)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child1", gameObjects);
    createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::AreEqual(internString("Child1"), destroyer.m_gameObjects[0]->getName());
    Assert::AreEqual(internString("Child2"), destroyer.m_gameObjects[1]->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_GameObjects_HaveNoParent)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child1", gameObjects);
    createGameObjectElement(document, "Child2", gameObjects);

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::IsNull(destroyer.m_gameObjects[0]->getParentTransform());
    Assert::IsNull(destroyer.m_gameObjects[1]->getParentTransform());
  }

#pragma endregion

#pragma region Prefab Instantiation

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_Prefabs_InstantiatesPrefabsCorrectly)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::AreEqual(internString("GameObject1"), destroyer.m_gameObjects[0]->getName());
    Assert::AreEqual(internString("GameObject1"), destroyer.m_gameObjects[1]->getName());
    Assert::AreNotEqual(destroyer.m_gameObjects[0].get(), destroyer.m_gameObjects[1].get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_Prefabs_HaveNoParent)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    XMLElement* prefab = createPrefabElement(document, "Child1", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());
    XMLElement* prefab2 = createPrefabElement(document, "Child2", gameObjects);
    prefab2->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::IsNull(destroyer.m_gameObjects[0]->getParentTransform());
    Assert::IsNull(destroyer.m_gameObjects[1]->getParentTransform());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_GameObjectsAndPrefabs_InstantiatesCorrectly)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = document.NewElement("Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::AreEqual(internString("Child1"), destroyer.m_gameObjects[0]->getName());
    Assert::AreEqual(internString("GameObject1"), destroyer.m_gameObjects[1]->getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenDataConverter_Instantiate_GameObjectsAndPrefabs_HaveNoParent)
  {
    SceneDataConverter converter("Screen");
    XMLDocument document;
    XMLElement* element = createGameObjectElement(document, "Name");
    XMLElement* gameObjects = createGameObjectsElement(document, element);
    createGameObjectElement(document, "Child1", gameObjects);
    XMLElement* prefab = createPrefabElement(document, "Child2", gameObjects);
    prefab->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, PrefabLoadingResources::getValidSingleGameObjectRelativePath().c_str());

    Assert::IsTrue(converter.convertFromXML(element));

    AutoDestroyer destroyer = converter.instantiate();

    Assert::AreEqual(static_cast<size_t>(2), converter.getGameObjects().size());
    Assert::AreEqual(static_cast<size_t>(2), destroyer.m_gameObjects.size());
    Assert::IsNull(destroyer.m_gameObjects[0]->getParentTransform());
    Assert::IsNull(destroyer.m_gameObjects[1]->getParentTransform());
  }

#pragma endregion

  };
}