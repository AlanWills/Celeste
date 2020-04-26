#include "ScriptCommands/Events/EventTriggererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Deserialization/InputDeserializers.h"
#include "Serialization/InputSerializers.h"
#include "Input/Key.h"
#include "Events/EventTriggerer.h"

using namespace Celeste::Events;

using Key = Celeste::Input::Key;
using InputMode = Celeste::Input::InputMode;
using EventTriggerer = Celeste::Events::EventTriggerer;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Events::EventTriggerer> : std::false_type {};
}

namespace Celeste::Lua::Events::EventTriggererScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getTriggerKey(EventTriggerer& eventTriggerer)
    {
      std::string output;
      serialize<Key>(eventTriggerer.getTriggerKey(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setTriggerKey(EventTriggerer& eventTriggerer, const std::string& text)
    {
      Key key;
      if (!deserialize<Key>(text, key))
      {
        ASSERT_FAIL();
        return;
      }

      eventTriggerer.setTriggerKey(key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    std::string getTriggerMode(EventTriggerer& eventTriggerer)
    {
      std::string output;
      serialize<TriggerMode>(eventTriggerer.getTriggerMode(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setTriggerMode(EventTriggerer& eventTriggerer, const std::string& text)
    {
      TriggerMode triggerMode = TriggerMode::kOnce;
      if (!deserialize<TriggerMode>(text, triggerMode))
      {
        ASSERT_FAIL();
        return;
      }

      eventTriggerer.setTriggerMode(triggerMode);
    }

    //------------------------------------------------------------------------------------------------
    void subscribeOnEventTriggeredCallback(
      EventTriggerer& eventTriggerer, 
      sol::protected_function callback,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<EventTriggerer::GameObjectEvent, GameObject&>(eventTriggerer.getEvent(), callback, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using EventTriggerer = Celeste::Events::EventTriggerer;

    registerUserType<EventTriggerer>(
      state,
      EventTriggerer::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getTriggerDelay", &EventTriggerer::getTriggerDelay,
      "setTriggerDelay", &EventTriggerer::setTriggerDelay,
      "getTriggerKey", &Internals::getTriggerKey,
      "setTriggerKey", &Internals::setTriggerKey,
      "getTriggerMode", &Internals::getTriggerMode,
      "setTriggerMode", &Internals::setTriggerMode,
      "subscribeOnEventTriggeredCallback", &Internals::subscribeOnEventTriggeredCallback);
  }
}