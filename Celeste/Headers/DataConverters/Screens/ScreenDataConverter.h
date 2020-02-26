#pragma once

#include "FileSystem/Path.h"
#include "XML/ChildXMLElementWalker.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"


namespace Celeste
{
  class ScreenDataConverter : public EntityDataConverter<Screen>
  {
    private:
      using GameObjectDataConverters = typename XML::DataConverterListElement<GameObjectDataConverter>::Items;

    public:
      CelesteDllExport ScreenDataConverter(const std::string& elementName = SCREEN_ELEMENT_NAME);
      ScreenDataConverter(const ScreenDataConverter&) = delete;
      ScreenDataConverter& operator=(const ScreenDataConverter&) = delete;

      inline const std::string& getName() const { return m_name.getValue(); }
      inline const std::vector<std::string>& getPreloadableFonts() const { return m_fonts.getChildren(); }
      inline const std::vector<std::string>& getPreloadableVertexShaders() const { return m_vertexShaders.getChildren(); }
      inline const std::vector<std::string>& getPreloadableFragmentShaders() const { return m_fragmentShaders.getChildren(); }
      inline const std::vector<std::string>& getPreloadableData() const { return m_data.getChildren(); }
      inline const std::vector<std::string>& getPreloadableSounds() const { return m_sounds.getChildren(); }
      inline const std::vector<std::string>& getPreloadableTextures() const { return m_textures.getChildren(); }
      inline const GameObjectDataConverters& getGameObjects() const { return m_gameObjects.getItems(); }
      
      CelesteDllExport static const char* const SCREEN_ELEMENT_NAME;
      CelesteDllExport static const char* const NAME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const PRELOADABLE_FONTS_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_FONT_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_VERTEX_SHADERS_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_VERTEX_SHADER_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_FRAGMENT_SHADERS_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_FRAGMENT_SHADER_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_DATAS_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_DATA_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_SOUNDS_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_SOUND_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_TEXTURES_ELEMENT_NAME;
      CelesteDllExport static const char* const PRELOADABLE_TEXTURE_ELEMENT_NAME;

    protected:
      CelesteDllExport bool doConvertFromXML(const tinyxml2::XMLElement* element) override;
      CelesteDllExport void doSetValues(Screen& screen) const override;

    private:
      using Inherited = EntityDataConverter<Screen>;

      bool tryConvertResources(const tinyxml2::XMLElement* screenElement);

      XML::ReferenceAttribute<std::string>& m_name;
      XML::ListElement<std::string>& m_fonts;
      XML::ListElement<std::string>& m_vertexShaders;
      XML::ListElement<std::string>& m_fragmentShaders;
      XML::ListElement<std::string>& m_data;
      XML::ListElement<std::string>& m_sounds;
      XML::ListElement<std::string>& m_textures;
      XML::DataConverterListElement<GameObjectDataConverter>& m_gameObjects;
  };
}