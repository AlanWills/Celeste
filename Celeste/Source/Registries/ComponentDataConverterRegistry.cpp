#include "Registries/ComponentDataConverterRegistry.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Objects/Component.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  ComponentDataConverterRegistry::ConverterMap& ComponentDataConverterRegistry::getConverters()
  {
    static ComponentDataConverterRegistry::ConverterMap converters;
    return converters;
  }

  //------------------------------------------------------------------------------------------------
  void ComponentDataConverterRegistry::removeConverter(const std::string& name)
  {
    if (!hasCustomConverter(name))
    {
      return;
    }

    getConverters().erase(name);
  }

  //------------------------------------------------------------------------------------------------
  void ComponentDataConverterRegistry::getConverter(
    const std::string& componentName, 
    std::unique_ptr<ComponentDataConverter>& outputConverter)
  {
    if (hasCustomConverter(componentName))
    {
      getConverters()[componentName]->instantiate(outputConverter);
    }
    else
    {
      outputConverter.reset(new ComponentDataConverter(componentName));
    }
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Component> ComponentDataConverterRegistry::convert(
    const tinyxml2::XMLElement* componentElement,
    GameObject& gameObject)
  {
    if (componentElement == nullptr)
    {
      ASSERT_FAIL();
      return observer_ptr<Component>();
    }

    const std::string& componentName = componentElement->Name();
    if (!ComponentRegistry::hasComponent(componentName))
    {
      ASSERT_FAIL();
      return observer_ptr<Component>();
    }

    observer_ptr<Component> component = ComponentRegistry::createComponent(componentName, gameObject);
    if (component == nullptr)
    {
      ASSERT_FAIL();
      return observer_ptr<Component>();
    }

    // Get our converter for this component
    std::unique_ptr<ComponentDataConverter> converter(nullptr);
    getConverter(componentName, converter);

    ASSERT_NOT_NULL(converter.get());
    if (!converter->convertFromXML(componentElement))
    {
      ASSERT_FAIL();
      return observer_ptr<Component>();
    }

    ASSERT(converter->isDataLoadedCorrectly());
    converter->setValues(*component);

    return component;
  }
}