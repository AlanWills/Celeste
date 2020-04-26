#include "ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"

#include "Settings/WindowSettings.h"

#include <memory>

using WindowSettings = Celeste::Settings::WindowSettings;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Settings::WindowSettings> : std::false_type {};
}

namespace Celeste::Lua::Settings::WindowSettingsScriptCommands
{
  namespace Internals
  {
    void apply(const std::string& playerSettingsPath)
    {
      std::unique_ptr<WindowSettings> settings(ScriptableObject::load<WindowSettings>(playerSettingsPath));
      ASSERT_NOT_NULL(settings.get());

      if (settings != nullptr)
      {
        settings->apply();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    Celeste::Lua::registerScriptableObjectUserType<WindowSettings>(
      state,
      "WindowSettings",
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "apply", &Internals::apply);
  }
}