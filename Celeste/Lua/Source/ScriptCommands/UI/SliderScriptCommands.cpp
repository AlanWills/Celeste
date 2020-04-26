#include "ScriptCommands/UI/SliderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "UI/Slider.h"
#include "sol/sol.hpp"

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
  void initialize(sol::state& state)
  {
    registerUserType<Slider>(
      state,
      Slider::type_name(),
      sol::base_classes, sol::bases<Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "setCurrentValue", &Slider::setCurrentValue,
      "subscribeOnValueChangedCallback", &Internals::subscribeOnValueChangedCallback);
  }
}