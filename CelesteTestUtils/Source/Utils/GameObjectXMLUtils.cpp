#include "Utils/GameObjectXMLUtils.h"
#include "Utils/XMLUtils.h"
#include "XML/Elements/DataConverterListElement.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace CelesteTestUtils
{
  using GameObjectDataConverterList = DataConverterListElement<GameObjectDataConverter>;

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectsElement(tinyxml2::XMLDocument& document)
  {
    return createElement(document, GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectsElement(tinyxml2::XMLDocument& document, tinyxml2::XMLElement* parent)
  {
    return createElement(document, GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME, parent);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectElement(tinyxml2::XMLDocument& document)
  {
    return createElement(document, GameObjectDataConverterList::GAME_OBJECT_ELEMENT_NAME);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectElement(tinyxml2::XMLDocument& document, const std::string& name)
  {
    tinyxml2::XMLElement* element = createGameObjectElement(document);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());

    return element;
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document,
    tinyxml2::XMLElement* parent)
  {
    return createElement(document, GameObjectDataConverterList::GAME_OBJECT_ELEMENT_NAME, parent);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document,
    const std::string& name,
    tinyxml2::XMLElement* parent)
  {
    tinyxml2::XMLElement* element = createGameObjectElement(document, parent);
    element->SetAttribute(GameObjectDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());

    return element;
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createPrefabElement(tinyxml2::XMLDocument& document)
  {
    return createElement(document, GameObjectDataConverterList::PREFAB_ELEMENT_NAME);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createPrefabElement(tinyxml2::XMLDocument& document, const std::string& name)
  {
    tinyxml2::XMLElement* element = createPrefabElement(document);
    element->SetAttribute(PrefabDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());

    return element;
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    tinyxml2::XMLElement* parent)
  {
    return createElement(document, GameObjectDataConverterList::PREFAB_ELEMENT_NAME, parent);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    const std::string& name,
    tinyxml2::XMLElement* parent)
  {
    tinyxml2::XMLElement* element = createPrefabElement(document, parent);
    element->SetAttribute(PrefabDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());

    return element;
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    const std::string& name,
    const std::string& path,
    tinyxml2::XMLElement* parent)
  {
    tinyxml2::XMLElement* element = createPrefabElement(document, parent);
    element->SetAttribute(PrefabDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());
    element->SetAttribute(PrefabDataConverter::PATH_ATTRIBUTE_NAME, path.c_str());

    return element;
  }
}