#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"
#include "Screens/ScreenUtils.h"
#include "Screens/Screen.h"
#include "Registries/ComponentRegistry.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  const char* const GameObjectDataConverter::NAME_ATTRIBUTE_NAME = "name";
  const char* const GameObjectDataConverter::TAG_ATTRIBUTE_NAME = "tag";
  const char* const GameObjectDataConverter::POSITION_ATTRIBUTE_NAME = "position";
  const char* const GameObjectDataConverter::COMPONENTS_ELEMENT_NAME = "Components";
  const char* const GameObjectDataConverter::CHILD_GAME_OBJECTS_ELEMENT_NAME = "GameObjects";

  //------------------------------------------------------------------------------------------------
  GameObjectDataConverter::GameObjectDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_name(createReferenceAttribute<std::string>(NAME_ATTRIBUTE_NAME, "", DeserializationRequirement::kRequired)),
    m_tag(createReferenceAttribute<std::string>(TAG_ATTRIBUTE_NAME, "", DeserializationRequirement::kNotRequired)),
    m_position(createReferenceAttribute<glm::vec3>(POSITION_ATTRIBUTE_NAME)),
    m_components(createDataConverterListElement<ComponentDataConverter>(COMPONENTS_ELEMENT_NAME, DeserializationRequirement::kNotRequired)),
    m_childGameObjects(createDataConverterListElement<GameObjectDataConverter>(CHILD_GAME_OBJECTS_ELEMENT_NAME, DeserializationRequirement::kNotRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameObjectDataConverter::doSetValues(GameObject& gameObject) const
  {
    Inherited::doSetValues(gameObject);

    ASSERT(!getName().empty());

    gameObject.setName(getName());
    gameObject.getTransform()->setTranslation(getPosition());

    if (!getTag().empty())
    {
      gameObject.setTag(getTag());
    }

    // Set up the hierarchy here first
    // Components do name lookup and require these objects to all be created
    for (const auto& childGameObjectDataConverter : getChildGameObjects())
    {
      GameObject* childGameObject = childGameObjectDataConverter->allocateGameObject(*gameObject.getScreen());
      childGameObject->setParent(&gameObject);
    }

    // Iterate through all of the components that have been loaded from xml
    for (ComponentDataConverter* converter : getComponents())
    {
      // Allocate the appropriate component
      Component* component = ComponentRegistry::allocateComponent(converter->getElementName(), gameObject);
      if (component == nullptr)
      {
        ASSERT_FAIL();
        continue;
      }

      // Set the values from the loaded xml onto the component
      converter->setValues(*component);

      // If the gameobject is inactive and the component is active, we also set the component to be inactive
      if (!gameObject.isActive() && component->isActive())
      {
        component->setActive(false);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  GameObject* GameObjectDataConverter::allocateGameObject(Screen& screen) const
  {
    if (!isDataLoadedCorrectly())
    {
      ASSERT_FAIL();
      return nullptr;
    }

    GameObject* gameObject = screen.allocateGameObject();
    setValues(*gameObject);

    return gameObject;
  }
}