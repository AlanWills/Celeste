#include "DataConverters/UI/SliderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Registries/CallbackRegistry.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(SliderDataConverter);

  const char* const SliderDataConverter::MIN_ATTRIBUTE_NAME("min");
  const char* const SliderDataConverter::MAX_ATTRIBUTE_NAME("max");
  const char* const SliderDataConverter::VALUE_ATTRIBUTE_NAME("value");
  const char* const SliderDataConverter::VALUE_CHANGED_CALLBACKS_ELEMENT_NAME("ValueChangedCallbacks");
  const char* const SliderDataConverter::CALLBACK_ELEMENT_NAME("Callback");

  //------------------------------------------------------------------------------------------------
  SliderDataConverter::SliderDataConverter() :
    Inherited(UI::Slider::type_name()),
    m_min(createValueAttribute(MIN_ATTRIBUTE_NAME, 0.0f)),
    m_max(createValueAttribute(MAX_ATTRIBUTE_NAME, 1.0f)),
    m_value(createValueAttribute(VALUE_ATTRIBUTE_NAME, 0.0f)),
    m_valueChangedCallbacks(createDataConverterListElement<CallbackDataConverter>(VALUE_CHANGED_CALLBACKS_ELEMENT_NAME, XML::ChildElementName(CALLBACK_ELEMENT_NAME)))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SliderDataConverter::doSetValues(UI::Slider& slider) const
  {
    slider.setMin(getMin());
    slider.setMax(getMax());
    slider.setCurrentValue(getValue());

    for (CallbackDataConverter* converter : m_valueChangedCallbacks)
    {
      const std::string& name = converter->getName();
      const std::string& arg = converter->getArg();

      if (!CallbackRegistry::hasCallback(name))
      {
        ASSERT_FAIL();
        continue;
      }

      slider.subscribeValueChangedCallback([name, arg](GameObject& gameObject, float currentValue) -> void
      {
        CallbackRegistry::invokeCallback(name, gameObject, std::to_string(currentValue));
      });
    }
  }
}