#include "Settings/WindowSettings.h"

#include "Lua/ScriptCommands/Settings/WindowSettingsScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include <memory>

using WindowSettings = Celeste::Settings::WindowSettings;


namespace Celeste
{
  namespace Lua
  {
    namespace Settings
    {
      namespace WindowSettingsScriptCommands
      {
        namespace Internals
        {
          void apply(const std::string& playerSettingsPath)
          {
            std::unique_ptr<WindowSettings> settings(ScriptableObject::load<WindowSettings>(playerSettingsPath));
            ASSERT(settings.get() != nullptr);

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
    }
  }
}