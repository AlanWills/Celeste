#include "DataConverters/UI/SliderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"


namespace Celeste
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(SliderDataConverter);

  const char* const SliderDataConverter::MIN_ATTRIBUTE_NAME("min");
  const char* const SliderDataConverter::MAX_ATTRIBUTE_NAME("max");
  const char* const SliderDataConverter::VALUE_ATTRIBUTE_NAME("value");

  //------------------------------------------------------------------------------------------------
  SliderDataConverter::SliderDataConverter() :
    Inherited(UI::Slider::type_name()),
    m_min(createValueAttribute(MIN_ATTRIBUTE_NAME, 0.0f)),
    m_max(createValueAttribute(MAX_ATTRIBUTE_NAME, 1.0f)),
    m_value(createValueAttribute(VALUE_ATTRIBUTE_NAME, 0.0f))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SliderDataConverter::doSetValues(UI::Slider& slider) const
  {
    slider.setMin(getMin());
    slider.setMax(getMax());
    slider.setCurrentValue(getValue());
  }
}