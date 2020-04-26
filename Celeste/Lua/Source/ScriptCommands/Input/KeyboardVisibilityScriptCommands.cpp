#include "ScriptCommands/Input/KeyboardVisibilityScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Deserialization/InputDeserializers.h"
#include "Serialization/InputSerializers.h"
#include "Input/Key.h"
#include "Input/KeyboardVisibility.h"

using Key = Celeste::Input::Key;
using InputMode = Celeste::Input::InputMode;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Input::KeyboardVisibility> : std::false_type {};
}

namespace Celeste::Lua::Input::KeyboardVisibilityScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getVisibilityKey(Celeste::Input::KeyboardVisibility& visibility)
    {
      std::string output;
      serialize<Key>(visibility.getVisibilityKey(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setVisibilityKey(Celeste::Input::KeyboardVisibility& visibility, const std::string& text)
    {
      Key key;
      if (!deserialize<Key>(text, key))
      {
        ASSERT_FAIL();
        return;
      }

      visibility.setVisibilityKey(key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    std::string getInvisibilityKey(Celeste::Input::KeyboardVisibility& visibility)
    {
      std::string output;
      serialize<Key>(visibility.getInvisibilityKey(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setInvisibilityKey(Celeste::Input::KeyboardVisibility& visibility, const std::string& text)
    {
      Key key;
      if (!deserialize<Key>(text, key))
      {
        ASSERT_FAIL();
        return;
      }

      visibility.setInvisibilityKey(key.m_key);
    }

    //------------------------------------------------------------------------------------------------
    std::string getInputMode(Celeste::Input::KeyboardVisibility& visibility)
    {
      std::string output;
      serialize<InputMode>(visibility.getInputMode(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setInputMode(Celeste::Input::KeyboardVisibility& visibility, const std::string& text)
    {
      InputMode inputMode = InputMode::kToggle;
      if (!deserialize<InputMode>(text, inputMode))
      {
        ASSERT_FAIL();
        return;
      }

      visibility.setInputMode(inputMode);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using KeyboardVisibility = Celeste::Input::KeyboardVisibility;

    registerUserType<KeyboardVisibility>(
      state,
      "KeyboardVisibility",
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getVisibilityKey", &Internals::getVisibilityKey,
      "setVisibilityKey", &Internals::setVisibilityKey,
      "getInvisibilityKey", &Internals::getInvisibilityKey,
      "setInvisibilityKey", &Internals::setInvisibilityKey,
      "getInputMode", &Internals::getInputMode,
      "setInputMode", &Internals::setInputMode);
  }
}