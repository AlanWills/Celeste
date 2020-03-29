#include "Settings/WindowSettings.h"

#include "Lua/ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

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
  void initialize()
  {
    Celeste::Lua::registerScriptableObjectUserType<WindowSettings>(
      "WindowSettings",
      sol::base_classes, sol::bases<Celeste::ScriptableObject>(),
      "apply", &Internals::apply);
  }
}