#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/DataConverterListElement.h"
#include "Deserialization/InputDeserializers.h"
#include "Bindings/InputDataBindingGenerators.h"


namespace Celeste
{
  class LimitedLifeTime;
  class CallbackDataConverter;

  class LimitedLifeTimeDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(LimitedLifeTimeDataConverter, LimitedLifeTime, CelesteDllExport)

    private:
      using OnDeathCallbacks = typename XML::DataConverterListElement<CallbackDataConverter>::Items;

    public:      
      inline float getLifeTime() const { return m_lifeTime.getValue(); }
      inline int getTriggerKey() const { return m_triggerKey.getValue().m_key; }
      inline const OnDeathCallbacks& getOnDeathCallbacks() const { return m_onDeathCallbacks.getItems(); }

      CelesteDllExport static const char* const LIFE_TIME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TRIGGER_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ON_DEATH_CALLBACKS_ELEMENT_NAME;
      CelesteDllExport static const char* const CALLBACK_ELEMENT_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<float>& m_lifeTime;
      XML::ValueAttribute<Input::Key>& m_triggerKey;
      XML::DataConverterListElement<CallbackDataConverter>& m_onDeathCallbacks;
  };
}