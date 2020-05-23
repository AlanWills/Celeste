#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "UI/Slider.h"


namespace Celeste
{
  class CallbackDataConverter;

  class SliderDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(SliderDataConverter, UI::Slider, CelesteDllExport)

    public:
      using CallbackDataConverters = typename XML::DataConverterListElement<CallbackDataConverter>::Items;

      inline float getMin() const { return m_min.getValue(); }
      inline float getMax() const { return m_max.getValue(); }
      inline float getValue() const { return m_value.getValue(); }

      CelesteDllExport static const char* const MIN_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MAX_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<float>& m_min;
      XML::ValueAttribute<float>& m_max;
      XML::ValueAttribute<float>& m_value;
  };
}