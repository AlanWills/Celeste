#include "Resources/Data/Prefab.h"
#include "Resources/ResourceManager.h"
#include "DataConverters/Resources/PrefabDataConverter.h"
#include "XML/XMLObjectFactory.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  Prefab::Prefab() :
    m_gameObjects(XML::XMLObjectFactory::create<XML::DataConverterListElement, GameObjectDataConverter>(
      GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME,
      DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Prefab::doLoadFromFile(const Path& path)
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(path);
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    const XMLElement* root = data->getDocumentRoot();
    if (root == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    ASSERT(m_gameObjects != nullptr);
    if (!XML::hasChildElement(root, m_gameObjects->getElementName()))
    {
      ASSERT_FAIL();
      return false;
    }

    const tinyxml2::XMLElement* gameObjectsElement = root->FirstChildElement(m_gameObjects->getElementName().c_str());
    return m_gameObjects->convertFromXML(gameObjectsElement);
  }

  //------------------------------------------------------------------------------------------------
  void Prefab::doUnload()
  {
    m_gameObjects.swap(XML::XMLObjectFactory::create<XML::DataConverterListElement, GameObjectDataConverter>(
      GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME,
      DeserializationRequirement::kRequired));
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<GameObject> Prefab::instantiate(Screen& screen) const
  {
    // Can only have one root game object
    if (getGameObjects().size() != static_cast<size_t>(1))
    {
      ASSERT_FAIL();
      return observer_ptr<GameObject>();
    }

    return getGameObjects()[0]->allocateGameObject(screen);
  }
}