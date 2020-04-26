#include "ScriptCommands/Input/KeyboardActivatorScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Deserialization/InputDeserializers.h"
#include "Serialization/InputSerializers.h"
#include "Input/Key.h"
#include "Input/KeyboardActivator.h"

using Key = Celeste::Input::Key;
using InputMode = Celeste::Input::InputMode;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Input::KeyboardActivator> : std::false_type {};
}

namespace Celeste::Lua::Input::KeyboardActivatorScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getActivationKey(Celeste::Input::KeyboardActivator& activator)
    {
      std::string output;
      serialize<Key>(activator.getActivationKey(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setActivationKey(Celeste::Input::KeyboardActivator& activator, const std::string& text)
    {
      Key key;
      if (!deserialize<Key>(text, key))
      {
        ASSERT_FAIL();
        return;
      }

      activator.setActivationKey(key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    std::string getDeactivationKey(Celeste::Input::KeyboardActivator& activator)
    {
      std::string output;
      serialize<Key>(activator.getDeactivationKey(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setDeactivationKey(Celeste::Input::KeyboardActivator& activator, const std::string& text)
    {
      Key key;
      if (!deserialize<Key>(text, key))
      {
        ASSERT_FAIL();
        return;
      }

      activator.setDeactivationKey(key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    std::string getInputMode(Celeste::Input::KeyboardActivator& activator)
    {
      std::string output;
      serialize<InputMode>(activator.getInputMode(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setInputMode(Celeste::Input::KeyboardActivator& activator, const std::string& text)
    {
      InputMode inputMode = InputMode::kToggle;
      if (!deserialize<InputMode>(text, inputMode))
      {
        ASSERT_FAIL();
        return;
      }

      activator.setInputMode(inputMode);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using KeyboardActivator = Celeste::Input::KeyboardActivator;

    registerUserType<KeyboardActivator>(
      state,
      KeyboardActivator::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getActivationKey", &Internals::getActivationKey,
      "setActivationKey", &Internals::setActivationKey,
      "getDeactivationKey", &Internals::getDeactivationKey,
      "setDeactivationKey", &Internals::setDeactivationKey,
      "getInputMode", &Internals::getInputMode,
      "setInputMode", &Internals::setInputMode);
  }
}