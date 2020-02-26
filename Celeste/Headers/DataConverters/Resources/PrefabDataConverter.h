#pragma once

#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "XML/Attributes/DataAttribute.h"


namespace Celeste::Resources
{
  class Prefab;
}

namespace Celeste
{
  class PrefabDataConverter : public GameObjectDataConverter
  {
    public:
      CelesteDllExport PrefabDataConverter(const std::string& elementName = XML::DataConverterListElement<GameObjectDataConverter>::PREFAB_ELEMENT_NAME);
      
      inline const Path& getPath() const { return m_path.getValue(); }

      inline observer_ptr<const Resources::Prefab> getPrefab() const { return m_prefab; }
      CelesteDllExport observer_ptr<GameObject> allocateGameObject(Screen& screen) const override;

      CelesteDllExport static const char* const PATH_ATTRIBUTE_NAME;

    protected:
      CelesteDllExport bool doConvertFromXML(const tinyxml2::XMLElement* prefabElement) override;

    private:
      using Inherited = GameObjectDataConverter;

      XML::ReferenceAttribute<Path>& m_path;

      observer_ptr<Resources::Prefab> m_prefab;
  };
}