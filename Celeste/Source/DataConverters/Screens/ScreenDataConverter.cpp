#include "DataConverters/Screens/ScreenDataConverter.h"
#include "Resources/ResourceManager.h"
#include "Screens/Screen.h"


namespace Celeste
{
  using namespace Resources;

  const char* const ScreenDataConverter::SCREEN_ELEMENT_NAME("Screen");
  const char* const ScreenDataConverter::NAME_ATTRIBUTE_NAME("name");
  const char* const ScreenDataConverter::PRELOADABLE_FONTS_ELEMENT_NAME("Fonts");
  const char* const ScreenDataConverter::PRELOADABLE_FONT_ELEMENT_NAME("Font");
  const char* const ScreenDataConverter::PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME("VertexShaders");
  const char* const ScreenDataConverter::PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME("VertexShader");
  const char* const ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME("FragmentShaders");
  const char* const ScreenDataConverter::PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME("FragmentShader");
  const char* const ScreenDataConverter::PRELOADABLE_DATAS_ELEMENT_NAME("Data");
  const char* const ScreenDataConverter::PRELOADABLE_DATA_ELEMENT_NAME("Data");
  const char* const ScreenDataConverter::PRELOADABLE_SOUNDS_ELEMENT_NAME("Sounds");
  const char* const ScreenDataConverter::PRELOADABLE_SOUND_ELEMENT_NAME("Sound");
  const char* const ScreenDataConverter::PRELOADABLE_TEXTURES_ELEMENT_NAME("Textures");
  const char* const ScreenDataConverter::PRELOADABLE_TEXTURE_ELEMENT_NAME("Texture");

  //------------------------------------------------------------------------------------------------
  ScreenDataConverter::ScreenDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_name(createReferenceAttribute<std::string>(NAME_ATTRIBUTE_NAME, "", DeserializationRequirement::kRequired)),
    m_fonts(createListElement<std::string>(PRELOADABLE_FONTS_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_FONT_ELEMENT_NAME))),
    m_vertexShaders(createListElement<std::string>(PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME))),
    m_fragmentShaders(createListElement<std::string>(PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME))),
    m_data(createListElement<std::string>(PRELOADABLE_DATAS_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_DATA_ELEMENT_NAME))),
    m_sounds(createListElement<std::string>(PRELOADABLE_SOUNDS_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_SOUND_ELEMENT_NAME))),
    m_textures(createListElement<std::string>(PRELOADABLE_TEXTURES_ELEMENT_NAME, XML::ChildElementName(PRELOADABLE_TEXTURE_ELEMENT_NAME))),
    m_gameObjects(createDataConverterListElement<GameObjectDataConverter>(GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME, DeserializationRequirement::kNotRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ScreenDataConverter::doConvertFromXML(const tinyxml2::XMLElement* screenElement)
  {
    Inherited::doConvertFromXML(screenElement);

    if (!tryConvertResources(screenElement))
    {
      ASSERT_FAIL();
      return false;
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  bool ScreenDataConverter::tryConvertResources(const tinyxml2::XMLElement* screenElement)
  {
    if (XML::hasChildElement(screenElement, "Resources"))
    {
      // Load the resources if we have them
      const tinyxml2::XMLElement* resourcesElement = screenElement->FirstChildElement("Resources");

      // Load the fonts if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_FONTS_ELEMENT_NAME))
      {
        m_fonts.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_FONTS_ELEMENT_NAME));
      }

      // Load the vertex shaders if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME))
      {
        m_vertexShaders.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME));
      }

      // Load the fragment shaders if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME))
      {
        m_fragmentShaders.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME));
      }

      // Load the data if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_DATAS_ELEMENT_NAME))
      {
        m_data.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_DATAS_ELEMENT_NAME));
      }

      // Load the sounds if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_SOUNDS_ELEMENT_NAME))
      {
        m_sounds.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_SOUNDS_ELEMENT_NAME));
      }

      // Load the textures if we have the element for it
      if (XML::hasChildElement(resourcesElement, PRELOADABLE_TEXTURES_ELEMENT_NAME))
      {
        m_textures.convertFromXML(resourcesElement->FirstChildElement(PRELOADABLE_TEXTURES_ELEMENT_NAME));
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void ScreenDataConverter::doSetValues(Screen& screen) const
  {
    Inherited::doSetValues(screen);
    
    ResourceManager& resourceManager = getResourceManager();
    for (const std::string& data : getPreloadableData())
    {
      resourceManager.load<Data>(data);
    }

    for (const std::string& font : getPreloadableFonts())
    {
      resourceManager.load<Font>(font);
    }

    for (const std::string& fragmentShader : getPreloadableFragmentShaders())
    {
      resourceManager.load<FragmentShader>(fragmentShader);
    }

    for (const std::string& sound : getPreloadableSounds())
    {
      resourceManager.load<Sound>(sound);
    }

    for (const std::string& texture : getPreloadableTextures())
    {
      resourceManager.load<Texture2D>(texture);
    }

    for (const std::string& vertexShader : getPreloadableVertexShaders())
    {
      resourceManager.load<VertexShader>(vertexShader);
    }

    screen.setName(getName());

    for (const auto& gameObjectConverter : getGameObjects())
    {
      gameObjectConverter->allocateGameObject(screen.getScreenRoot());
    }
  }
}