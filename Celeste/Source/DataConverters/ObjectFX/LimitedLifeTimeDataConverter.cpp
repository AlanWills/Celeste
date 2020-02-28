#include "DataConverters/ObjectFX/LimitedLifeTimeDataConverter.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Input/Utils/GlfwKeyConverter.h"
#include "ObjectFX/LimitedLifeTime.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(LimitedLifeTimeDataConverter)

  const char* const LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME("lifetime");
  const char* const LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME("trigger_key");

  //------------------------------------------------------------------------------------------------
  LimitedLifeTimeDataConverter::LimitedLifeTimeDataConverter() :
    Inherited(LimitedLifeTime::type_name()),
    m_lifeTime(createValueAttribute(LIFE_TIME_ATTRIBUTE_NAME, 0.0f)),
    m_triggerKey(createValueAttribute<Input::Key>(TRIGGER_KEY_ATTRIBUTE_NAME, GLFW_KEY_UNKNOWN))
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
  }
}