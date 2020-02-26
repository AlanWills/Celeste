#include "Lua/ScriptCommands/UI/SliderScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/Slider.h"

using namespace Celeste::UI;


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
    sol::state& state = Lua::LuaState::instance();
    registerUserType<Slider>(
      Slider::type_name(),
      sol::base_classes, sol::bases<Celeste::Script, Celeste::Component, Celeste::Entity, Celeste::Object>(),
      "allocate", sol::factories(&Slider::allocate),
      "setCurrentValue", &Slider::setCurrentValue,
      "subscribeOnValueChangedCallback", &Internals::subscribeOnValueChangedCallback);
  }
}