#include "DataConverters/ObjectFX/LimitedLifeTimeDataConverter.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"
#include "Registries/CallbackRegistry.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Input/Utils/GlfwKeyConverter.h"
#include "ObjectFX/LimitedLifeTime.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(LimitedLifeTimeDataConverter)

  const char* const LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME("lifetime");
  const char* const LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME("trigger_key");
  const char* const LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME("OnDeathCallbacks");
  const char* const LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME("Callback");

  //------------------------------------------------------------------------------------------------
  LimitedLifeTimeDataConverter::LimitedLifeTimeDataConverter() :
    Inherited(LimitedLifeTime::type_name()),
    m_lifeTime(createValueAttribute(LIFE_TIME_ATTRIBUTE_NAME, 0.0f)),
    m_triggerKey(createValueAttribute<Input::Key>(TRIGGER_KEY_ATTRIBUTE_NAME, GLFW_KEY_UNKNOWN)),
    m_onDeathCallbacks(createDataConverterListElement<CallbackDataConverter>(ON_DEATH_CALLBACKS_ELEMENT_NAME, XML::ChildElementName(CALLBACK_ELEMENT_NAME)))
  {
  }

  //------------------------------------------------------------------------------------------------
  void LimitedLifeTimeDataConverter::doSetValues(LimitedLifeTime& limitedLifeTime) const
  {
    limitedLifeTime.setLifeTime(getLifeTime());
    
    if (getTriggerKey() != GLFW_KEY_UNKNOWN)
    {
      limitedLifeTime.setTriggerKey(getTriggerKey());
    }

    for (CallbackDataConverter* callbackInfo : m_onDeathCallbacks)
    {
      const std::string& callbackName = callbackInfo->getName();
      const std::string& callbackArg = callbackInfo->getArg();

      // Check if callback exists in registry
      if (!CallbackRegistry::hasCallback(callbackInfo->getName()))
      {
        ASSERT_FAIL();
        continue;
      }

      // Think we want to pass callbackInfo by value so we don't have to rely on this converter?
      limitedLifeTime.subscribeOnDeathCallback([callbackName, callbackArg](GameObject& gameObject) -> void
      {
        CallbackRegistry::invokeCallback(callbackName, gameObject, callbackArg);
      });
    }
  }
}