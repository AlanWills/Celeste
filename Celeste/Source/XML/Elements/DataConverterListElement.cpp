#include "XML/Elements/DataConverterListElement.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "DataConverters/Resources/PrefabDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"


namespace Celeste
{
  namespace XML
  {
    //-------------------------------- GameObjectDataConverter Overload ------------------------------
    //------------------------------------------------------------------------------------------------
    const char* const DataConverterListElement<GameObjectDataConverter>::GAME_OBJECT_ELEMENT_NAME = "GameObject";
    const char* const DataConverterListElement<GameObjectDataConverter>::PREFAB_ELEMENT_NAME = "Prefab";

    //------------------------------------------------------------------------------------------------
    DataConverterListElement<GameObjectDataConverter>::~DataConverterListElement()
    {
      for (GameObjectDataConverter* converter : getItems())
      {
        delete converter;
      }
    }

    //------------------------------------------------------------------------------------------------
    DataConverterListElement<GameObjectDataConverter>* DataConverterListElement<GameObjectDataConverter>::clone() const
    {
      DataConverterListElement<GameObjectDataConverter>* clone = new DataConverterListElement<GameObjectDataConverter>(
        getElementName(), isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

      // Need to copy child data converters somehow
      return clone;
    }

    //------------------------------------------------------------------------------------------------
    bool DataConverterListElement<GameObjectDataConverter>::doConvertFromXML(const tinyxml2::XMLElement* listElement)
    {
      // Use temporary list to ensure that only elements will be added if all were converted successfully
      Items dataConverters;

      for (const tinyxml2::XMLElement* gameObjectElement : XML::children(listElement))
      {
        std::unique_ptr<GameObjectDataConverter> converter(nullptr);

        std::string name = gameObjectElement->Name();

        if (name == GAME_OBJECT_ELEMENT_NAME)
        {
          converter.reset(new GameObjectDataConverter(gameObjectElement->Name()));
        }
        else if (name == PREFAB_ELEMENT_NAME)
        {
          converter.reset(new PrefabDataConverter());
        }

        if (converter != nullptr && converter->convertFromXML(gameObjectElement))
        {
          dataConverters.push_back(converter.release());
        }
        else
        {
          ASSERT_FAIL();
          return false;
        }
      }

      m_items.assign(dataConverters.begin(), dataConverters.end());

      return !m_items.empty() || !isRequired();
    }

    //-------------------------------- ComponentDataConverter Overload ------------------------------
    //------------------------------------------------------------------------------------------------
    DataConverterListElement<ComponentDataConverter>::~DataConverterListElement()
    {
      for (ComponentDataConverter* converter : getItems())
      {
        delete converter;
      }
    }

    //------------------------------------------------------------------------------------------------
    DataConverterListElement<ComponentDataConverter>* DataConverterListElement<ComponentDataConverter>::clone() const
    {
      DataConverterListElement<ComponentDataConverter>* clone = new DataConverterListElement<ComponentDataConverter>(
        getElementName(), isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

      // Need to copy child data converters somehow
      return clone;
    }

    //------------------------------------------------------------------------------------------------
    bool DataConverterListElement<ComponentDataConverter>::doConvertFromXML(const tinyxml2::XMLElement* element)
    {
      for (const XMLElement* componentElement : children(element))
      {
        std::unique_ptr<ComponentDataConverter> converter(nullptr);
        if (Lua::LuaComponentDataConverterRegistry::hasConverter(componentElement->Name()))
        {
          Lua::LuaComponentDataConverterRegistry::getConverter(componentElement->Name(), converter);

          if (converter.get() && converter->convertFromXML(componentElement))
          {
            m_items.push_back(converter.release());
          }
        }
        else
        {
          ComponentDataConverterRegistry::getConverter(componentElement->Name(), converter);

          if (converter.get() && converter->convertFromXML(componentElement))
          {
            m_items.push_back(converter.release());
          }
        }
      }

      return !m_items.empty() || !isRequired();
    }
  }
}