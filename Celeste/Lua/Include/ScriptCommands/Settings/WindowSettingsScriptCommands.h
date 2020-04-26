#pragma once

#include <string>


namespace sol
{
  class state;
}

namespace Celeste::Lua::Settings::WindowSettingsScriptCommands
{
  void initialize(sol::state& state);
}