#pragma once

#include "DataConverters/Objects/EntityDataConverter.h"
#include "Deserialization/MathsDeserializers.h"
#include "Bindings/MathsDataBindingGenerators.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  class ComponentDataConverter;
  class Screen;

  class GameObjectDataConverter : public EntityDataConverter<GameObject>
  {
    private:
      using GameObjectDataConverters = typename XML::DataConverterListElement<GameObjectDataConverter>::Items;
      using ComponentDataConverters = typename XML::DataConverterListElement<ComponentDataConverter>::Items;

    public:
      CelesteDllExport GameObjectDataConverter(const std::string& elementName = XML::DataConverterListElement<GameObjectDataConverter>::GAME_OBJECT_ELEMENT_NAME);
      GameObjectDataConverter(const GameObjectDataConverter&) = delete;
      GameObjectDataConverter(GameObjectDataConverter&&) noexcept = default;
      ~GameObjectDataConverter() = default;

      GameObjectDataConverter& operator=(const GameObjectDataConverter&) = delete;

      CelesteDllExport virtual GameObject* allocateGameObject() const;
      CelesteDllExport GameObject* allocateGameObject(Transform& transform) const;

      inline const std::string& getName() const { return m_name.getValue(); }
      inline const std::string& getTag() const { return m_tag.getValue(); }
      inline const glm::vec3& getPosition() const { return m_position.getValue(); }
      inline const ComponentDataConverters& getComponents() const { return m_components.getItems(); }
      inline const GameObjectDataConverters& getChildGameObjects() const { return m_childGameObjects.getItems(); }
      
      CelesteDllExport static const char* const NAME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TAG_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const POSITION_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const COMPONENTS_ELEMENT_NAME;
      CelesteDllExport static const char* const CHILD_GAME_OBJECTS_ELEMENT_NAME;

    protected:
      CelesteDllExport void doSetValues(GameObject& gameObject) const override;

    private:
      using Inherited = EntityDataConverter<GameObject>;

      XML::ReferenceAttribute<std::string>& m_name;
      XML::ReferenceAttribute<std::string>& m_tag;
      XML::ReferenceAttribute<glm::vec3>& m_position;
      XML::DataConverterListElement<ComponentDataConverter>& m_components;
      XML::DataConverterListElement<GameObjectDataConverter>& m_childGameObjects;
  };
}