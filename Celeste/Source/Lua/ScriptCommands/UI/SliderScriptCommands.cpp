#include "Lua/ScriptCommands/UI/SliderScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/Slider.h"

using namespace Celeste::UI;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::UI::Slider> : std::false_type {};
}

namespace Celeste::Lua::UI::SliderScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnValueChangedCallback(
      Slider& slider, 
      sol::protected_function function,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<Slider::ValueChangedEvent, GameObject&, float>(
        slider.getValueChangedEvent(), function, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Slider>(
      Slider::type_name(),
      sol::base_classes, sol::bases<Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "setCurrentValue", &Slider::setCurrentValue,
      "subscribeOnValueChangedCallback", &Internals::subscribeOnValueChangedCallback);
  }
}